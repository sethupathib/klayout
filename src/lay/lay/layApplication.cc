
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2017 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#include "layApplication.h"
#include "laySignalHandler.h"
#include "laybasicConfig.h"
#include "layConfig.h"
#include "layMainWindow.h"
#include "layMacroEditorDialog.h"
#include "layNativePlugin.h"
#include "layVersion.h"
#include "laySignalHandler.h"
#include "layRuntimeErrorForm.h"
#include "layProgress.h"
#include "layTextProgress.h"
#include "layBackgroundAwareTreeStyle.h"
#include "layMacroController.h"
#include "layTechnologyController.h"
#include "laySaltController.h"
#include "lymMacro.h"
#include "gtf.h"
#include "gsiDecl.h"
#include "gsiInterpreter.h"
#include "rba.h"
#include "pya.h"
#include "rdb.h"
#include "dbStatic.h"
#include "dbLibrary.h"
#include "dbLibraryManager.h"
#include "tlExceptions.h"
#include "tlException.h"
#include "tlAssert.h"
#include "tlLog.h"
#include "tlString.h"
#include "tlSystemPaths.h"
#include "tlExpression.h"
#include "tlExceptions.h"
#include "tlInternational.h"
#include "tlArch.h"

#include <QIcon>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QAction>
#include <QMessageBox>

#include <iostream>
#include <memory>
#include <algorithm>

#ifdef _WIN32
#  include <windows.h>
#else
#  include <dlfcn.h>
#endif

namespace lay
{

// --------------------------------------------------------------------------------
//  Exception handlers

static void ui_exception_handler_tl (const tl::Exception &ex, QWidget *parent)
{
  //  Prevents severe side effects if there are pending deferred methods
  tl::NoDeferredMethods silent;

  //  if any transaction is pending (this may happen when an operation threw an exception)
  //  close transactions.
  if (lay::MainWindow::instance () && lay::MainWindow::instance ()->manager ().transacting ()) {
    lay::MainWindow::instance ()->manager ().commit ();
  }

  const tl::ExitException *gsi_exit = dynamic_cast <const tl::ExitException *> (&ex);
  const tl::BreakException *gsi_break = dynamic_cast <const tl::BreakException *> (&ex);
  const tl::ScriptError *gsi_excpt = dynamic_cast <const tl::ScriptError *> (&ex);

  if (gsi_exit || gsi_break) {
    //  exit and break exceptions are not shown - they are issued when a script is aborted or
    //  an operation is cancelled
  } else if (gsi_excpt) {

    //  show and GSI errors in the context of the macro editor if that is open
    if (! parent && lay::MacroEditorDialog::instance () && lay::MacroEditorDialog::instance ()->isVisible ()) {
      parent = lay::MacroEditorDialog::instance ();
    } 
    if (! parent) {
      parent = QApplication::activeWindow () ? QApplication::activeWindow () : lay::MainWindow::instance ();
    }

    if (gsi_excpt->line () > 0) {
      tl::error << gsi_excpt->sourcefile () << ":" << gsi_excpt->line () << ": " 
                << gsi_excpt->msg () << tl::to_string (QObject::tr (" (class ")) << gsi_excpt->cls () << ")";
    } else {
      tl::error << gsi_excpt->msg () << tl::to_string (QObject::tr (" (class ")) << gsi_excpt->cls () << ")";
    }

    lay::RuntimeErrorForm error_dialog (parent, "ruby_error_form", gsi_excpt);
    error_dialog.exec ();

  } else {
    tl::error << ex.msg (); 
    if (! parent) {
      parent = QApplication::activeWindow () ? QApplication::activeWindow () : lay::MainWindow::instance ();
    }
    QMessageBox::critical (parent, QObject::tr ("Error"), tl::to_qstring (ex.msg ())); 
  }
}

static void ui_exception_handler_std (const std::exception &ex, QWidget *parent)
{
  //  Prevents severe side effects if there are pending deferred methods
  tl::NoDeferredMethods silent;

  //  if any transaction is pending (this may happen when an operation threw an exception)
  //  close transactions.
  if (lay::MainWindow::instance () && lay::MainWindow::instance ()->manager ().transacting ()) {
    lay::MainWindow::instance ()->manager ().commit ();
  }

  tl::error << ex.what (); 
  if (! parent) {
    parent = QApplication::activeWindow () ? QApplication::activeWindow () : lay::MainWindow::instance ();
  }
  QMessageBox::critical (parent, QObject::tr ("Error"), tl::to_qstring (ex.what ())); 
}

static void ui_exception_handler_def (QWidget *parent)
{
  //  Prevents severe side effects if there are pending deferred methods
  tl::NoDeferredMethods silent;

  //  if any transaction is pending (this may happen when an operation threw an exception)
  //  close transactions.
  if (lay::MainWindow::instance () && lay::MainWindow::instance ()->manager ().transacting ()) {
    lay::MainWindow::instance ()->manager ().commit ();
  }

  if (! parent) {
    parent = QApplication::activeWindow () ? QApplication::activeWindow () : lay::MainWindow::instance ();
  }
  QMessageBox::critical (parent, QObject::tr ("Error"), QObject::tr ("An unspecific error occured")); 
}

// --------------------------------------------------------------------------------

static Application *ms_instance = 0;

static PluginDescriptor load_plugin (const std::string &pp)
{
  PluginDescriptor desc;
  desc.path = pp;

  klp_init_func_t init_func = 0;
  static const char *init_func_name = "klp_init";

  //  NOTE: since we are using a different suffix ("*.klp"), we can't use QLibrary.
#ifdef _WIN32
  //  there is no "dlopen" on mingw, so we need to emulate it.
  HINSTANCE handle = LoadLibraryW ((const wchar_t *) tl::to_qstring (pp).constData ());
  if (! handle) {
    throw tl::Exception (tl::to_string (QObject::tr ("Unable to load plugin: %s with error message: %s ")), pp, GetLastError ());
  }
  init_func = reinterpret_cast<klp_init_func_t> (GetProcAddress (handle, init_func_name));
#else
  void *handle;
  handle = dlopen (tl::string_to_system (pp).c_str (), RTLD_LAZY);
  if (! handle) {
    throw tl::Exception (tl::to_string (QObject::tr ("Unable to load plugin: %s")), pp);
  }
  init_func = reinterpret_cast<klp_init_func_t> (dlsym (handle, init_func_name));
#endif

  //  If present, call the initialization function to fetch some details from the plugin
  if (init_func) {
    const char *version = 0;
    const char *description = 0;
    (*init_func) (&desc.autorun, &desc.autorun_early, &version, &description);
    if (version) {
      desc.version = version;
    }
    if (description) {
      desc.description = description;
    }
  }

  tl::log << "Loaded plugin '" << pp << "'";

  return desc;
}

Application::Application (int &argc, char **argv, bool non_ui_mode)
  : QApplication (argc, argv, !non_ui_mode),
    m_lyp_map_all_cvs (true), 
    m_lyp_add_default (false),
    m_write_config_file (true),
    m_gtf_replay_rate (0),
    m_gtf_replay_stop (-1),
    m_no_macros (false),
    m_same_view (false),
    m_sync_mode (false),
    m_no_gui (false),
    m_vo_mode (false),
    m_editable (false),
    m_enable_undo (true),
    mp_qapp (0),
    mp_qapp_gui (0),
    mp_ruby_interpreter (0),
    mp_python_interpreter (0),
    mp_mw (0),
    mp_pr (0),
    mp_pb (0),
    mp_plugin_root (0),
    mp_recorder (0)
{
  // TODO: offer a strict mode for exception handling where this takes place:
  // lay::Application::instance ()->exit (1);
  if (! non_ui_mode) {
    tl::set_ui_exception_handlers (ui_exception_handler_tl, ui_exception_handler_std, ui_exception_handler_def);
  }

  mp_qapp = this;
  mp_qapp_gui = (non_ui_mode ? 0 : this);

  mp_dm_scheduler.reset (new tl::DeferredMethodScheduler ());

  //  install a special style proxy to overcome the issue of black-on-black tree expanders
  if (mp_qapp_gui) {
    mp_qapp_gui->setStyle (new lay::BackgroundAwareTreeStyle (0));
  }
  
  //  initialize the system codecs (Hint: this must be done after the QApplication is initialized because
  //  it will call setlocale)
  tl::initialize_codecs ();

  //  transscribe the arguments to UTF8
  std::vector<std::string> args;
  args.reserve (argc);
  for (int i = 0; i < argc; ++i) {
    args.push_back (argv [i]);
  }

#if defined(KLAYOUT_VIEWER_ONLY)
  //  viewer-only mode compiled in
  m_vo_mode = true;
#else
  //  determine viewer-only mode from executable name. "klayout_vo*" will enable
  //  viewer-only mode
  std::string vo_exe_name (std::string (lay::Version::exe_name ()) + "_vo");
  if (! args.empty () && std::string (tl::to_string (QFileInfo (tl::to_qstring (args.front ())).fileName ()), 0, vo_exe_name.size ()) == vo_exe_name) {
    m_vo_mode = true;
  }
#endif

  tl_assert (ms_instance == 0);
  ms_instance = this;

  std::string gtf_record;
  bool gtf_save_incremental = false;

  //  get and create the klayout appdata folder if required
  m_appdata_path = tl::get_appdata_path ();

  //  get the installation path
  m_inst_path = tl::get_inst_path ();

  //  get the KLayout path
  m_klayout_path = tl::get_klayout_path ();

  if (mp_qapp_gui) {

    //  create the configuration files paths and collect the initialization config files
    //  (the ones used for reset) into m_initial_config_files.
    {
      //  Fallback to ~/.layviewrc for backward compatibility
      QDir qd (QDir::home ());
      QString filename = QString::fromUtf8 (".layviewrc");
      if (qd.exists (filename) && QFileInfo (qd.absoluteFilePath (filename)).isReadable ()) {
        m_config_files.push_back (tl::to_string (qd.absoluteFilePath (filename)));
        m_config_file_to_delete = m_config_files.back ();
      }
    }

    m_config_file_to_write = tl::to_string (QDir (tl::to_qstring (m_appdata_path)).absoluteFilePath (QString::fromUtf8 ("klayoutrc")));

    //  Hint: the order is reverse in the sense that the first one wins ...
    for (std::vector <std::string>::const_iterator p = m_klayout_path.end (); p != m_klayout_path.begin (); ) {
      --p;
      QDir qd (tl::to_qstring (*p));
      QString filename = QString::fromUtf8 ("klayoutrc");
      if (qd.exists (filename) && QFileInfo (qd.absoluteFilePath (filename)).isReadable ()) {
        m_config_files.push_back (tl::to_string (qd.absoluteFilePath (filename)));
        if (m_config_files.back () != m_config_file_to_write) {
          m_initial_config_files.push_back (m_config_files.back ());
        }
      }
    }

  }

  //  Try to locate the native plugins:
  //  Native plugins are DLL's or SO's disguised as "*.klp" files.
  //  The are installed either
  //    - directly in one of the KLAYOUT_PATH directories
  //    - in a folder named by the architecture (i.e. "i686-win32-mingw" or "x86_64-linux-gcc") below
  //      one of these folders
  //    - in one of the Salt packages
  //    - in one of the Salt packages, in a folder named after the architecture

  std::string version = lay::Version::version ();
  std::vector<std::string> vv = tl::split (version, ".");

  std::string arch_string = tl::arch_string ();
  std::vector<std::string> as = tl::split (arch_string, "-");
  if (as.size () > 2) {
    as.resize (2);
  }
  std::string short_arch_string = tl::join (as, "-");

  for (std::vector <std::string>::const_iterator p = m_klayout_path.begin (); p != m_klayout_path.end (); ++p) {

    std::set<std::string> modules;

    std::vector<QString> klp_paths;
    klp_paths.push_back (tl::to_qstring (*p));
    klp_paths.push_back (QDir (klp_paths.back ()).filePath (tl::to_qstring (tl::arch_string ())));

    lay::Salt salt;
    salt.add_location (tl::to_string (QDir (tl::to_qstring (*p)).filePath (QString::fromUtf8 ("salt"))));

    //  Build the search path for the *.klp files. The search priority is for example:
    //    salt/mypackage/x86_64-linux-gcc-0.25.1
    //    salt/mypackage/x86_64-linux-gcc-0.25
    //    salt/mypackage/x86_64-linux-gcc-0
    //    salt/mypackage/x86_64-linux-gcc
    //    salt/mypackage/x86_64-linux
    //    salt/mypackage

    for (lay::Salt::flat_iterator g = salt.begin_flat (); g != salt.end_flat (); ++g) {
      QDir dir = QDir (tl::to_qstring ((*g)->path ()));
      klp_paths.push_back (dir.filePath (tl::to_qstring (arch_string + "-" + lay::Version::version())));
      if (vv.size () >= 2) {
        klp_paths.push_back (dir.filePath (tl::to_qstring (arch_string + "-" + vv[0] + "." + vv[1])));
      }
      if (vv.size () >= 1) {
        klp_paths.push_back (dir.filePath (tl::to_qstring (arch_string + "-" + vv[0])));
      }
      klp_paths.push_back (dir.filePath (tl::to_qstring (arch_string + "-" + tl::to_string (lay::Version::version ()))));
      klp_paths.push_back (dir.filePath (tl::to_qstring (arch_string)));
      klp_paths.push_back (dir.filePath (tl::to_qstring (short_arch_string)));
      klp_paths.push_back (tl::to_qstring ((*g)->path ()));
    }

    QStringList name_filters;
    name_filters << QString::fromUtf8 ("*.klp");

    for (std::vector<QString>::const_iterator p = klp_paths.begin (); p != klp_paths.end (); ++p) {

      QStringList inst_modules = QDir (*p).entryList (name_filters);
      inst_modules.sort ();

      for (QStringList::const_iterator im = inst_modules.begin (); im != inst_modules.end (); ++im) {
        QFileInfo klp_file (*p, *im);
        if (klp_file.exists () && klp_file.isReadable ()) {
          std::string m = tl::to_string (klp_file.absoluteFilePath ());
          std::string mn = tl::to_string (klp_file.fileName ());
          if (modules.find (mn) == modules.end ()) {
            m_native_plugins.push_back (load_plugin (m));
            modules.insert (mn);
          }
        }
      }

    }

  }

  std::vector <std::pair<std::string, std::string> > custom_macro_paths;
  m_no_macros = false;

  // currently: technology is always set to make "default" technology the default
  bool tech_set = true; 
  std::string tech;
  std::string tech_file;

  bool editable_set = false;

  for (int i = 1; i < argc; ++i) {

    const std::string &a = args [i];

    if (a == "-d" && (i + 1) < argc) {

      int v = 0;
      tl::from_string (args [++i], v);
      v = std::max (0, v);
      tl::verbosity (v);

    } else if (a == "-l" && (i + 1) < argc) {

      m_layer_props_file = args [++i];

    } else if (a == "-lx") {

      m_lyp_add_default = true;

    } else if (a == "-lf") {

      m_lyp_map_all_cvs = false;

    } else if (a == "-u" && (i + 1) < argc) {

      m_session_file = args [++i];

    } else if (a == "-wd" && (i + 1) < argc) {

      std::string v;
      const char *p = args [++i].c_str ();
      const char *n0 = p;
      while (*p && *p != '=') {
        ++p;
      }
      std::string n (n0, p - n0);
      if (*p == '=') {
        tl::Eval::set_global_var (n, tl::Variant (v));
      } else {
        tl::Eval::set_global_var (n, tl::Variant (true));
      }

    } else if (a == "-rd" && (i + 1) < argc) {

      std::string v;
      const char *p = args [++i].c_str ();
      const char *n0 = p;
      while (*p && *p != '=') {
        ++p;
      }
      std::string n (n0, p - n0);
      m_variables.push_back (std::make_pair (n, v));
      if (*p == '=') {
        m_variables.back ().second = ++p;
      }

    } else if (a == "-rm" && (i + 1) < argc) {

      m_load_macros.push_back (args [++i]);

    } else if (a == "-r" && (i + 1) < argc) {

      m_run_macro = args [++i];

    } else if (a == "-rx") {

      m_no_macros = true;

    } else if (a == "-gr" && (i + 1) < argc) {

      gtf_record = args [++i];

    } else if (a == "-gi") {

      gtf_save_incremental = true;

    } else if (a == "-gp" && (i + 1) < argc) {

      m_gtf_replay = args [++i];
      //  test mode replay forces sync mode to true
      m_sync_mode = true;

    } else if (a == "-gx" && (i + 1) < argc) {

      int r = 0;
      tl::from_string (args [++i], r);
      m_gtf_replay_rate = std::max (0, r);

    } else if (a == "-gb" && (i + 1) < argc) {

      int s = 0;
      tl::from_string (args [++i], s);
      m_gtf_replay_stop = std::max (0, s);

    } else if (a == "-c" && (i + 1) < argc) {

      m_config_files.clear ();
      m_config_files.push_back (args [++i]);
      m_initial_config_files = m_config_files;
      m_config_file_to_write = m_config_files.back ();

    } else if (a == "-nc") {

      m_config_files.clear ();
      m_initial_config_files = m_config_files;
      m_config_file_to_write.clear ();

    } else if (a == "-n" && (i + 1) < argc) {

      tech = args [++i];
      tech_file.clear ();
      tech_set = true;

    } else if (a == "-nn" && (i + 1) < argc) {

      tech_file = args [++i];
      tech.clear ();
      tech_set = true;

    } else if (a == "-p" && (i + 1) < argc) {

      m_native_plugins.push_back (load_plugin (args [++i]));

    } else if (a == "-s") {

      m_same_view = true;
      
    } else if (a == "-e") {

      m_editable = ! m_vo_mode;
      editable_set = true;
      
    } else if (a == "-ne") {

      m_editable = false;
      editable_set = true;
      
    } else if (a == "-i") {

      m_enable_undo = false;
      
    } else if (a == "-ni") {

      m_enable_undo = true;
      
    } else if (a == "-j" && (i + 1) < argc) {

      custom_macro_paths.push_back (std::pair<std::string, std::string> (args [++i], "macros"));
      
    } else if (a == "-nt") {

      m_write_config_file = true;
      
    } else if (a == "-t") {

      m_write_config_file = false;
      
    } else if (a == "-z") {

      m_no_gui = true;
      
    } else if (a == "-zz") {

      m_no_gui = true;
      //  other consequences have been dealt with before
      
    } else if (a == "-b") {

      //  -nc:
      m_config_files.clear ();
      m_initial_config_files = m_config_files;
      m_config_file_to_write.clear ();

      //  -rx:
      m_no_macros = true;

      //  -zz:
      m_no_gui = true;
      //  other consequences have been dealt with before

    } else if (a == "-x") {

      m_sync_mode = true;
      
    } else if (a == "-v") {

      tl::info << lay::Version::name () << " " << lay::Version::version ();
      exit (0);
      
    } else if (a == "-h") {

      tl::info << usage () << tl::noendl;
      exit (0);

    } else if (a == "-m" && (i + 1) < argc) {

      m_files.push_back (std::make_pair (rdb_file, std::make_pair (std::string (args [++i]), std::string ())));

    } else if (a[0] == '-') {

      throw tl::Exception (tl::to_string (QObject::tr ("Unknown option: ")) + a);

    } else if (tech_set) {

      if (! tech.empty ()) {
        m_files.push_back (std::make_pair (layout_file_with_tech, std::make_pair (a, tech)));
      } else if (! tech_file.empty ()) {
        m_files.push_back (std::make_pair (layout_file_with_tech_file, std::make_pair (a, tech_file)));
      } else {
        m_files.push_back (std::make_pair (layout_file, std::make_pair (a, std::string ())));
      }

    } else {

      m_files.push_back (std::make_pair (layout_file, std::make_pair (a, std::string ())));

    }

  }

  //  initialize the GSI class system (Variant binding, Expression support)
  //  We have to do this now since plugins may register GSI classes and before the
  //  ruby interpreter, because it depends on a proper class system.
  gsi::initialize ();

  //  initialize the tl::Expression subsystem with GSI-bound classes
  gsi::initialize_expressions ();

  //  create the ruby and python interpreter instances now.
  //  Hint: we do this after load_plugin, because that way the plugins can register GSI classes and methods.
  //  TODO: do this through some auto-registration
  mp_ruby_interpreter = new rba::RubyInterpreter ();
  mp_python_interpreter = new pya::PythonInterpreter ();

  //  Read some configuration values that we need early
  bool editable_from_config = false;

  {
    lay::PluginRoot cfg;

    for (std::vector <std::string>::const_iterator c = m_config_files.begin (); c != m_config_files.end (); ++c) {
      try {
        cfg.read_config (*c);
      } catch (...) { }
    }

    try {
      cfg.config_get (cfg_edit_mode, editable_from_config);
    } catch (...) { }

    try {
      std::string mp;
      cfg.config_get (cfg_custom_macro_paths, mp);
      tl::Extractor ex (mp.c_str ());
      while (! ex.at_end ()) {
        std::string p;
        ex.read_word_or_quoted (p);
        custom_macro_paths.push_back (std::pair<std::string, std::string> (p, "macros"));
        if (ex.test (":")) {
          ex.read_word (custom_macro_paths.back ().second);
        }
        ex.test (";");
      }
    } catch (...) { }

  }

  //  Install the signal handlers after the interpreters, so we can be sure we
  //  installed our handler.
  install_signal_handlers ();

  lay::SaltController *sc = lay::SaltController::instance ();
  lay::TechnologyController *tc = lay::TechnologyController::instance ();
  lay::MacroController *mc = lay::MacroController::instance ();

  if (sc) {

    //  auto-import salt grains
    for (std::vector <std::string>::const_iterator p = m_klayout_path.begin (); p != m_klayout_path.end (); ++p) {
      sc->add_path (*p);
    }

    sc->set_salt_mine_url (tl::salt_mine_url ());

  }

  if (tc) {

    //  auto-import technologies
    for (std::vector <std::string>::const_iterator p = m_klayout_path.begin (); p != m_klayout_path.end (); ++p) {
      tc->add_path (*p);
    }

    //  import technologies from the command line
    for (std::vector <std::pair<file_type, std::pair<std::string, std::string> > >::iterator f = m_files.begin (); f != m_files.end (); ++f) {

      if (f->first == layout_file_with_tech_file) {

        if (tl::verbosity () >= 20) {
          tl::info << "Importing technology from " << f->second.second;
        }

        lay::Technology t;
        t.load (f->second.second);

        tc->add_temp_tech (t);

        f->first = layout_file_with_tech;
        f->second.second = t.name ();

      }

    }

    tc->load ();

  }

  if (mc) {

    mc->enable_implicit_macros (! m_no_macros);

    if (! m_no_macros) {

      //  Add the global ruby modules as the first ones.
      //  TODO: this is a deprecated feature.
      std::vector<std::string> global_modules = scan_global_modules ();
      m_load_macros.insert (m_load_macros.begin (), global_modules.begin (), global_modules.end ());

      for (std::vector <std::string>::const_iterator p = m_klayout_path.begin (); p != m_klayout_path.end (); ++p) {
        if (p == m_klayout_path.begin ()) {
          mc->add_path (*p, tl::to_string (QObject::tr ("Local")), std::string (), false);
        } else if (m_klayout_path.size () == 2) {
          mc->add_path (*p, tl::to_string (QObject::tr ("Global")), std::string (), true);
        } else {
          mc->add_path (*p, tl::to_string (QObject::tr ("Global")) + " - " + *p, std::string (), true);
        }
      }

      //  Install the custom folders
      for (std::vector <std::pair<std::string, std::string> >::const_iterator p = custom_macro_paths.begin (); p != custom_macro_paths.end (); ++p) {
        mc->add_path (p->first, tl::to_string (QObject::tr ("Project")) + " - " + p->first, p->second, false);
      }

    }

    //  Actually load the macros
    mc->load ();

  }

  //  If the editable flag was not set, use it from the 
  //  configuration. Since it is too early now, we cannot use the
  //  configuration once it is read
  if (! editable_set && ! m_vo_mode) {
    m_editable = editable_from_config;
  }

  db::set_default_editable_mode (m_editable);
  db::enable_transactions (m_enable_undo);

  if (mp_qapp_gui) {
    mp_qapp_gui->setWindowIcon (QIcon (QString::fromUtf8 (":/logo.png")));
#if QT_VERSION >= 0x040500
    mp_qapp_gui->setAttribute (Qt::AA_DontShowIconsInMenus, false);
#endif
  }

  if (mp_qapp_gui && ! gtf_record.empty ()) {
    //  since the recorder tracks QAction connections etc., it must be instantiated before every other 
    //  object performing a gtf::action_connect for example
    mp_recorder = new gtf::Recorder (mp_qapp_gui, gtf_record);
    mp_recorder->save_incremental (gtf_save_incremental);
  }

  tl::Eval::set_global_var ("appdata_path", tl::Variant (m_appdata_path));
  tl::Eval::set_global_var ("inst_path", tl::Variant (m_inst_path));

  tl::Variant kp (m_klayout_path.begin (), m_klayout_path.end ());
  tl::Eval::set_global_var ("klayout_path", kp);

  //  call "autorun_early" on all plugins that wish so
  for (std::vector <lay::PluginDescriptor>::const_iterator p = m_native_plugins.begin (); p != m_native_plugins.end (); ++p) {
    if (p->autorun_early) {
      (*p->autorun_early) ();
    }
  }

  //  run all early autorun macros
  lym::MacroCollection::root ().autorun_early ();

  //  rescan the folders because early autorun macros might have added 
  //  suffixes through the MacroInterpreter interface.
  lym::MacroCollection::root ().rescan ();

  if (mp_qapp_gui) {
    mp_mw = new lay::MainWindow (mp_qapp_gui, "main_window");
    QObject::connect (mp_mw, SIGNAL (closed ()), mp_qapp_gui, SLOT (quit ()));
    mp_plugin_root = mp_mw;
  } else {
    mp_pr = new lay::ProgressReporter ();
    mp_pb = new TextProgress (10 /*verbosity level*/);
    mp_pr->set_progress_bar (mp_pb);
    mp_plugin_root = new lay::PluginRoot ();
  }

  //  initialize the plugins for the first time
  if (tl::verbosity () >= 20) {
    tl::info << "Initializing plugins:";
  }
  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    lay::PluginDeclaration *pd = const_cast<lay::PluginDeclaration *> (&*cls);
    if (tl::verbosity () >= 20) {
      tl::info << "  " << cls.current_name () << " [" << cls.current_position () << "]";
    }
    pd->initialize (mp_plugin_root);
  }

  //  establish the configuration
  mp_plugin_root->config_setup ();

  //  Some info output 
  if (tl::verbosity () >= 20) {

    tl::info << "KLayout path:";
    for (std::vector <std::string>::const_iterator c = m_klayout_path.begin (); c != m_klayout_path.end (); ++c) {
      tl::info << "  " << *c;
    }
    tl::info << "Config file to write: " << m_config_file_to_write;
    tl::info << "Config files to read:";
    for (std::vector <std::string>::const_iterator c = m_config_files.begin (); c != m_config_files.end (); ++c) {
      tl::info << "  " << *c;
    }

  }
}

Application::~Application () 
{
  tl::set_ui_exception_handlers (0, 0, 0);

  if (! ms_instance) {
    return;
  }

  shutdown ();
}

std::vector<std::string>
Application::scan_global_modules ()
{
  //  NOTE:
  //  this is deprecated functionality - for backward compatibility, global "*.rbm" and "*.pym" modules
  //  are still considered. The desired solution is autorun macros.

  //  try to locate a global rbainit file and rbm modules
  std::vector<std::string> global_modules;
  std::set<std::string> modules;

  //  try to locate a global plugins
  for (std::vector <std::string>::const_iterator p = m_klayout_path.begin (); p != m_klayout_path.end (); ++p) {

#if 0
    //  deprecated functionality
    QFileInfo rbainit_file (tl::to_qstring (*p), QString::fromUtf8 ("rbainit"));
    if (rbainit_file.exists () && rbainit_file.isReadable ()) {
      std::string m = tl::to_string (rbainit_file.absoluteFilePath ());
      if (modules.find (m) == modules.end ()) {
        global_modules.push_back (m);
        modules.insert (m);
      }
    }
#endif

    QDir inst_path_dir (tl::to_qstring (*p));

    QStringList name_filters;
    name_filters << QString::fromUtf8 ("*.rbm");
    name_filters << QString::fromUtf8 ("*.pym");

    QStringList inst_modules = inst_path_dir.entryList (name_filters);
    inst_modules.sort ();

    for (QStringList::const_iterator im = inst_modules.begin (); im != inst_modules.end (); ++im) {
      QFileInfo rbm_file (tl::to_qstring (*p), *im);
      if (rbm_file.exists () && rbm_file.isReadable ()) {
        std::string m = tl::to_string (rbm_file.absoluteFilePath ());
        if (modules.find (m) == modules.end ()) {
          tl::warn << tl::to_string (tr ("Global modules are deprecated. Turn '%1'' into an autorun macro instead and put it into 'macros' or 'pymacros'.").arg (tl::to_qstring (m)));
          global_modules.push_back (m);
          modules.insert (m);
        }
      }
    }

  }

  return global_modules;
}

bool 
Application::notify (QObject *receiver, QEvent *e)
{
  //  Note: due to a bug in some Qt versions (i.e. 4.8.3) throwing exceptions across 
  //  signals may not be safe. Hence the local BEGIN_PROTECTED .. END_PROTECTED approach
  //  is still preferred over the global solution through "notify"
  
  bool ret = true;
  BEGIN_PROTECTED
    ret = QApplication::notify (receiver, e);
  END_PROTECTED
  return ret;
}

void
Application::exit (int result)
{
  if (! result) {
    finish ();
  }
  shutdown ();
  ::exit (result);
}

void 
Application::finish ()
{
  //  save the recorded test events
  if (mp_mw && mp_recorder && mp_recorder->recording ()) {
    mp_recorder->stop ();
    mp_recorder->save ();
  }

  if (mp_plugin_root && m_write_config_file) {

    if (! m_config_file_to_write.empty ()) {
      if (tl::verbosity () >= 20) {
        tl::info << tl::to_string (QObject::tr ("Updating configuration file ")) << m_config_file_to_write;
      }
      mp_plugin_root->write_config (m_config_file_to_write);
    }
    if (! m_config_file_to_delete.empty () && m_config_file_to_delete != m_config_file_to_write) {
      if (tl::verbosity () >= 20) {
        tl::info << tl::to_string (QObject::tr ("Deleting configuration file ")) << m_config_file_to_delete;
      }
      QFile::remove (tl::to_qstring (m_config_file_to_delete));
    }

  }
}

void
Application::shutdown ()
{
  //  uninitialize the plugins
  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    lay::PluginDeclaration *pd = const_cast<lay::PluginDeclaration *> (&*cls);
    pd->uninitialize (mp_plugin_root);
  }

  if (mp_mw) {
    delete mp_mw;
    mp_mw = 0;
    mp_plugin_root = 0;
  } else if (mp_plugin_root) {
    delete mp_plugin_root;
    mp_plugin_root = 0;
  }

  //  delete all other top level widgets for safety - we don't want Ruby clean them up for us
  QWidgetList tl_widgets = topLevelWidgets ();
  for (QWidgetList::iterator w = tl_widgets.begin (); w != tl_widgets.end (); ++w) {
    delete *w;
  }

  if (mp_pr) {
    delete mp_pr;
    mp_pr = 0;
  }

  if (mp_pb) {
    delete mp_pb;
    mp_pb = 0;
  }

  if (mp_recorder) {
    delete mp_recorder;
    mp_recorder = 0;
  }

  if (mp_ruby_interpreter) {
    delete mp_ruby_interpreter;
    mp_ruby_interpreter = 0;
  }

  if (mp_python_interpreter) {
    delete mp_python_interpreter;
    mp_python_interpreter = 0;
  }

  mp_qapp = 0;
  mp_qapp_gui = 0;
  ms_instance = 0;
}

Application *
Application::instance () 
{
  return ms_instance;
}

std::string
Application::version () const
{
  return std::string (lay::Version::name ()) + " " + lay::Version::version ();
}
      
std::string 
Application::usage () 
{
  std::string r;
  r = std::string (lay::Version::exe_name ()) + " [<options>] [<file>] ..\n";
  r += tl::to_string (QObject::tr ("options")) + "\n";
  r += tl::to_string (QObject::tr ("  -b                  Batch mode (same as -zz -nc -rx)")) + "\n";
  r += tl::to_string (QObject::tr ("  -c <config file>    Use this configuration file")) + "\n";
  r += tl::to_string (QObject::tr ("  -nc                 Don't use a configuration file (implies -t)")) + "\n";
  r += tl::to_string (QObject::tr ("  -d <debug level>    Set debug level")) + "\n";
  r += tl::to_string (QObject::tr ("  -e                  Editable mode (allow editing of files)")) + "\n";
  r += tl::to_string (QObject::tr ("  -ne                 Readonly mode (editing of files is disabled)")) + "\n";
  r += tl::to_string (QObject::tr ("  -gr <file name>     Record GUI test file")) + "\n";
  r += tl::to_string (QObject::tr ("  -gp <file name>     Replay GUI test file")) + "\n";
  r += tl::to_string (QObject::tr ("  -gb <line number>   Replay GUI test file up to (including) line")) + "\n";
  r += tl::to_string (QObject::tr ("  -gx <millisec>      Replay rate for GUI test file")) + "\n";
  r += tl::to_string (QObject::tr ("  -gi                 Incremental logs for GUI test file")) + "\n";
  r += tl::to_string (QObject::tr ("  -i                  Disable undo buffering (less memory requirements)")) + "\n";
  r += tl::to_string (QObject::tr ("  -ni                 Enable undo buffering (default, overrides previous -i option)")) + "\n";
  r += tl::to_string (QObject::tr ("  -j <path>           Add the given path to the macro project paths")) + "\n"; 
  r += tl::to_string (QObject::tr ("  -l <lyp file>       Use layer properties file")) + "\n";
  r += tl::to_string (QObject::tr ("  -lx                 With -l: add other layers as well")) + "\n";
  r += tl::to_string (QObject::tr ("  -lf                 With -l: use the lyp file as it is (no expansion to multiple layouts)")) + "\n";
  r += tl::to_string (QObject::tr ("  -m <database file>  Load RDB (report database) file (into previous layout view)")) + "\n";
  r += tl::to_string (QObject::tr ("  -n <technology>     Technology to use for next layout(s) on command line")) + "\n";
  r += tl::to_string (QObject::tr ("  -nn <tech file>     Technology file (.lyt) to use for next layout(s) on command line")) + "\n";
  r += tl::to_string (QObject::tr ("  -p <plugin>         Load the plugin (can be used multiple times)")) + "\n";
  r += tl::to_string (QObject::tr ("  -r <script>         Execute main script on startup (after having loaded files etc.)")) + "\n";
  r += tl::to_string (QObject::tr ("  -rm <script>        Execute module on startup (can be used multiple times)")) + "\n";
  r += tl::to_string (QObject::tr ("  -rd <name>=<value>  Specify skript variable")) + "\n";
  r += tl::to_string (QObject::tr ("  -rx                 Ignore all implicit macros (*.rbm, rbainit, *.lym)")) + "\n";
  r += tl::to_string (QObject::tr ("  -s                  Load files into same view")) + "\n";
  r += tl::to_string (QObject::tr ("  -t                  Don't update the configuration file on exit")) + "\n";
  r += tl::to_string (QObject::tr ("  -nt                 Update the configuration file on exit (default, overrides previous -t option)")) + "\n";
  r += tl::to_string (QObject::tr ("  -u <file name>      Restore session from given file")) + "\n";
  r += tl::to_string (QObject::tr ("  -v                  Print program version and exit")) + "\n";
  r += tl::to_string (QObject::tr ("  -wd <name>=<value>  Define a variable within expressions")) + "\n";
  r += tl::to_string (QObject::tr ("  -x                  Synchronous drawing mode")) + "\n";
  r += tl::to_string (QObject::tr ("  -zz                 Non-GUI mode (database only, implies -nc)")) + "\n";
  r += tl::to_string (QObject::tr ("  -z                  Non-GUI mode (hidden views)")) + "\n";
  return r;
}

int
Application::run ()
{
  gtf::Player player (0);

  if (mp_mw) {

    mp_mw->set_synchronous (m_sync_mode);

    if (! m_no_gui) {
      mp_mw->setWindowTitle (tl::to_qstring (version ()));
      mp_mw->resize (800, 600);
      mp_mw->show ();
    }

    if (! m_gtf_replay.empty ()) {
      player.load (m_gtf_replay);
    }

    if (mp_recorder) {
      mp_recorder->start ();
    }

  }

  int result = 0;

  bool config_failed = false;

  for (std::vector <std::string>::const_iterator c = m_config_files.begin (); c != m_config_files.end (); ++c) {
    BEGIN_PROTECTED_CLEANUP
      mp_plugin_root->read_config (*c);
      //  if the last config was read successfully no reset will happen:
      config_failed = false;
    END_PROTECTED_CLEANUP {
      config_failed = true;
    }
  }

  if (config_failed) {
    reset_config ();
  }

  for (std::vector< std::pair<std::string, std::string> >::const_iterator v = m_variables.begin (); v != m_variables.end (); ++v) {
    ruby_interpreter ().define_variable (v->first, v->second);
    python_interpreter ().define_variable (v->first, v->second);
    tl::log << "Variable definition: " << v->first << "='" << v->second << "'";
  }

  for (std::vector<std::string>::const_iterator m = m_load_macros.begin (); m != m_load_macros.end (); ++m) {

    BEGIN_PROTECTED 

      std::auto_ptr<lym::Macro> macro (new lym::Macro ());
      macro->load_from (*m);
      macro->set_file_path (*m);
      if (macro->show_in_menu ()) {
        //  menu-based macros are just registered so they are shown in the menu
        lay::MacroController *mc = lay::MacroController::instance ();
        if (mc) {
          tl::log << "Registering macro '" << *m << "'";
          mc->add_temp_macro (macro.release ());
        }
      } else {
        //  other macros given with -rm are run
        tl::log << "Run macro '" << *m << "'";
        macro->run ();
      }

    END_PROTECTED

  }

  //  Run plugin and macro specific initializations
  autorun ();

  if (mp_mw) {

    for (std::vector <std::pair<file_type, std::pair<std::string, std::string> > >::const_iterator f = m_files.begin (); f != m_files.end (); ++f) {

      if (f->first == layout_file || f->first == layout_file_with_tech) {

        std::string filename = f->second.first;

        if (f->first != layout_file_with_tech) {
          mp_mw->add_mru (f->second.first);
          mp_mw->load_layout (f->second.first, m_same_view ? 2 /*same view*/ : 1 /*new view*/);
        } else {
          mp_mw->add_mru (f->second.first, f->second.second);
          mp_mw->load_layout (f->second.first, f->second.second, m_same_view ? 2 /*same view*/ : 1 /*new view*/);
        }

        //  Make the first one loaded the active one.
        if (mp_mw->current_view ()) {
          mp_mw->current_view ()->set_active_cellview_index (0);
        }

      } else {

        if (mp_mw->current_view () == 0) {
          mp_mw->create_view ();
        }

        if (mp_mw->current_view () != 0) {
          std::auto_ptr <rdb::Database> db (new rdb::Database ());
          db->load (f->second.first);
          int rdb_index = mp_mw->current_view ()->add_rdb (db.release ());
          mp_mw->current_view ()->open_rdb_browser (rdb_index, mp_mw->current_view ()->active_cellview_index ());
        }

      }
    }

    if (! m_layer_props_file.empty ()) {

      if (m_lyp_map_all_cvs && mp_mw->is_single_cv_layer_properties_file (m_layer_props_file)) {
        mp_mw->load_layer_properties (m_layer_props_file, -1, true /*all views*/, m_lyp_add_default);
      } else {
        mp_mw->load_layer_properties (m_layer_props_file, true /*all views*/, m_lyp_add_default);
      }

      tl::log << "Layer properties loaded '" << m_layer_props_file << "'";

      //  because the layer may carry transformations, we need to refit the cellviews.
      for (unsigned int v = 0; v != mp_mw->views (); ++v) {
        mp_mw->view (v)->zoom_fit ();
      }

    }

    if (! m_session_file.empty ()) {
      mp_mw->restore_session (m_session_file);
      tl::log << "Session restored '" << m_session_file << "'";
    }

    if (! m_gtf_replay.empty ()) {
      player.replay (m_gtf_replay_rate, m_gtf_replay_stop);
    }

    //  Give the plugins a change to do some last-minute initialisation and checks
    for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
      lay::PluginDeclaration *pd = const_cast<lay::PluginDeclaration *> (&*cls);
      pd->initialized (mp_mw);
    }

    if (! m_no_gui && m_gtf_replay.empty () && ! mp_recorder) {
      //  Show initial tip window if required
      mp_mw->about_to_exec ();
    }

  } else if (mp_plugin_root) {

    //  Give the plugins a change to do some last-minute initialisation and checks
    for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
      lay::PluginDeclaration *pd = const_cast<lay::PluginDeclaration *> (&*cls);
      pd->initialized (mp_plugin_root);
    }

  }

  if (! m_run_macro.empty ()) {

    tl::log << "Run macro '" << m_run_macro << "'";
    lym::Macro macro;
    macro.load_from (m_run_macro);
    macro.set_file_path (m_run_macro);
    result = macro.run ();

  } else {
    result = exec ();
  }

  finish ();

  return result;
}

void
Application::autorun ()
{
  //  call "autorun" on all plugins that wish so
  for (std::vector <lay::PluginDescriptor>::const_iterator p = m_native_plugins.begin (); p != m_native_plugins.end (); ++p) {
    if (p->autorun) {
      (*p->autorun) ();
    }
  }

  //  run all autorun macros
  lym::MacroCollection::root ().autorun ();
}

void
Application::set_editable (bool e)
{
  if (m_editable != e) {
    m_editable = e;
    db::set_default_editable_mode (m_editable);
  }
}

static void 
dump_children (QObject *obj, int level = 0)
{
  QObjectList children = obj->children ();
  if (! children.isEmpty () || ! obj->objectName ().isEmpty ()) {
    std::string info;
    for (int i = 0; i < level; ++i) {
      info += "  ";
    }
    if (obj->objectName ().isEmpty ()) {
      info += "<unnamed>";
    } else {
      info += tl::to_string (obj->objectName ());
    }
    tl::info << info;
    for (QObjectList::const_iterator child = children.begin (); child != children.end (); ++child) {
      dump_children (*child, level + 1);
    }
  }
}

int 
Application::exec ()
{
  if (m_no_gui) {
    return 0;
  } else {

    //  if requested, dump the widgets
    if (tl::verbosity () >= 40) {

      QWidgetList tl_widgets = QApplication::topLevelWidgets (); 

      tl::info << tl::to_string (QObject::tr ("Widget tree:"));
      for (QWidgetList::const_iterator tl = tl_widgets.begin (); tl != tl_widgets.end (); ++tl) { 
        if (! (*tl)->objectName ().isEmpty ()) {
          dump_children (*tl); 
        }
      }
      tl::info << "";

      tl::info << tl::to_string (QObject::tr ("Actions list:"));
      for (QWidgetList::const_iterator tl = tl_widgets.begin (); tl != tl_widgets.end (); ++tl) { 
        if (! (*tl)->objectName ().isEmpty ()) {
          QList<QAction *> actions = (*tl)->findChildren<QAction *> ();
          if (! actions.isEmpty ()) {
            tl::info << tl::to_string ((*tl)->objectName ()) << ":";
            for (QList<QAction *>::const_iterator a = actions.begin (); a != actions.end (); ++a) {
              if (! (*a)->objectName ().isEmpty ()) {
                tl::info << "  " << tl::to_string ((*a)->objectName ());
              }
            }
          }
        }
      }
      tl::info << "";

    }

    return mp_qapp_gui->exec ();

  }
}

void
Application::process_events (QEventLoop::ProcessEventsFlags flags, bool silent)
{
  if (mp_mw) {

    if (silent) {
      mp_dm_scheduler->enable (false);
    }

#if QT_VERSION < 0x050000
    QApplication::syncX ();
#endif

    mp_mw->enter_busy_mode (true);
    QApplication::processEvents (flags);
    mp_mw->enter_busy_mode (false);

    if (silent) {
      mp_dm_scheduler->enable (true);
    }

  }
}

bool 
Application::write_config (const std::string &config_file)
{
  return mp_plugin_root ? mp_plugin_root->write_config (config_file) : 0;
}

void 
Application::reset_config ()
{
  clear_config ();
  for (std::vector <std::string>::const_iterator c = m_initial_config_files.begin (); c != m_initial_config_files.end (); ++c) {
    try {
      read_config (*c);
    } catch (...) { }
  }
}

void 
Application::clear_config ()
{
  if (mp_plugin_root) {
    mp_plugin_root->clear_config ();
  }
}

bool 
Application::read_config (const std::string &config_file)
{
  return mp_plugin_root ? mp_plugin_root->read_config (config_file) : true;
}

void 
Application::set_config (const std::string &name, const std::string &value)
{
  if (mp_plugin_root) {
    mp_plugin_root->config_set (name, value);
  }
}

void 
Application::config_end ()
{
  if (mp_plugin_root) {
    mp_plugin_root->config_end ();
  }
}

std::string 
Application::get_config (const std::string &name) const
{
  if (mp_plugin_root) {
    return mp_plugin_root->config_get (name);
  } else {
    return std::string ();
  }
}

std::vector<std::string> 
Application::get_config_names () const
{
  std::vector<std::string> names;
  if (mp_plugin_root) {
    mp_plugin_root->get_config_names (names);
  }
  return names;
}

bool
Application::special_app_flag (const std::string &name)
{
  // TODO: some more elaborate scheme?
  const char *env = getenv (("KLAYOUT_" + name).c_str ());
  return (env && *env);
}

}

