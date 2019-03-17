
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2019 Matthias Koefferlein

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

/**
*  @file gsiDeclQNetworkCookie.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QNetworkCookie>
#include <QDateTime>
#include "gsiQt.h"
#include "gsiQtNetworkCommon.h"
#include "gsiDeclQtNetworkTypeTraits.h"
#include <memory>

// -----------------------------------------------------------------------
// class QNetworkCookie

//  Constructor QNetworkCookie::QNetworkCookie(const QByteArray &name, const QByteArray &value)


static void _init_ctor_QNetworkCookie_4510 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name", true, "QByteArray()");
  decl->add_arg<const QByteArray & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("value", true, "QByteArray()");
  decl->add_arg<const QByteArray & > (argspec_1);
  decl->set_return_new<QNetworkCookie> ();
}

static void _call_ctor_QNetworkCookie_4510 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QByteArray &arg1 = args ? gsi::arg_reader<const QByteArray & >() (args, heap) : gsi::arg_maker<const QByteArray & >() (QByteArray(), heap);
  const QByteArray &arg2 = args ? gsi::arg_reader<const QByteArray & >() (args, heap) : gsi::arg_maker<const QByteArray & >() (QByteArray(), heap);
  ret.write<QNetworkCookie *> (new QNetworkCookie (arg1, arg2));
}


//  Constructor QNetworkCookie::QNetworkCookie(const QNetworkCookie &other)


static void _init_ctor_QNetworkCookie_2742 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkCookie & > (argspec_0);
  decl->set_return_new<QNetworkCookie> ();
}

static void _call_ctor_QNetworkCookie_2742 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkCookie &arg1 = gsi::arg_reader<const QNetworkCookie & >() (args, heap);
  ret.write<QNetworkCookie *> (new QNetworkCookie (arg1));
}


// QString QNetworkCookie::domain()


static void _init_f_domain_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_domain_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QNetworkCookie *)cls)->domain ());
}


// QDateTime QNetworkCookie::expirationDate()


static void _init_f_expirationDate_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QDateTime > ();
}

static void _call_f_expirationDate_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QDateTime > ((QDateTime)((QNetworkCookie *)cls)->expirationDate ());
}


// bool QNetworkCookie::isHttpOnly()


static void _init_f_isHttpOnly_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isHttpOnly_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QNetworkCookie *)cls)->isHttpOnly ());
}


// bool QNetworkCookie::isSecure()


static void _init_f_isSecure_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isSecure_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QNetworkCookie *)cls)->isSecure ());
}


// bool QNetworkCookie::isSessionCookie()


static void _init_f_isSessionCookie_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isSessionCookie_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QNetworkCookie *)cls)->isSessionCookie ());
}


// QByteArray QNetworkCookie::name()


static void _init_f_name_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QByteArray > ();
}

static void _call_f_name_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QByteArray > ((QByteArray)((QNetworkCookie *)cls)->name ());
}


// bool QNetworkCookie::operator!=(const QNetworkCookie &other)


static void _init_f_operator_excl__eq__c2742 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkCookie & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c2742 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkCookie &arg1 = gsi::arg_reader<const QNetworkCookie & >() (args, heap);
  ret.write<bool > ((bool)((QNetworkCookie *)cls)->operator!= (arg1));
}


// QNetworkCookie &QNetworkCookie::operator=(const QNetworkCookie &other)


static void _init_f_operator_eq__2742 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkCookie & > (argspec_0);
  decl->set_return<QNetworkCookie & > ();
}

static void _call_f_operator_eq__2742 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkCookie &arg1 = gsi::arg_reader<const QNetworkCookie & >() (args, heap);
  ret.write<QNetworkCookie & > ((QNetworkCookie &)((QNetworkCookie *)cls)->operator= (arg1));
}


// bool QNetworkCookie::operator==(const QNetworkCookie &other)


static void _init_f_operator_eq__eq__c2742 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkCookie & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c2742 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkCookie &arg1 = gsi::arg_reader<const QNetworkCookie & >() (args, heap);
  ret.write<bool > ((bool)((QNetworkCookie *)cls)->operator== (arg1));
}


// QString QNetworkCookie::path()


static void _init_f_path_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_path_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QNetworkCookie *)cls)->path ());
}


// void QNetworkCookie::setDomain(const QString &domain)


static void _init_f_setDomain_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("domain");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDomain_2025 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QString &arg1 = gsi::arg_reader<const QString & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkCookie *)cls)->setDomain (arg1);
}


// void QNetworkCookie::setExpirationDate(const QDateTime &date)


static void _init_f_setExpirationDate_2175 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("date");
  decl->add_arg<const QDateTime & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setExpirationDate_2175 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QDateTime &arg1 = gsi::arg_reader<const QDateTime & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkCookie *)cls)->setExpirationDate (arg1);
}


// void QNetworkCookie::setHttpOnly(bool enable)


static void _init_f_setHttpOnly_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("enable");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setHttpOnly_864 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  bool arg1 = gsi::arg_reader<bool >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkCookie *)cls)->setHttpOnly (arg1);
}


// void QNetworkCookie::setName(const QByteArray &cookieName)


static void _init_f_setName_2309 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("cookieName");
  decl->add_arg<const QByteArray & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setName_2309 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QByteArray &arg1 = gsi::arg_reader<const QByteArray & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkCookie *)cls)->setName (arg1);
}


// void QNetworkCookie::setPath(const QString &path)


static void _init_f_setPath_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("path");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPath_2025 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QString &arg1 = gsi::arg_reader<const QString & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkCookie *)cls)->setPath (arg1);
}


// void QNetworkCookie::setSecure(bool enable)


static void _init_f_setSecure_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("enable");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setSecure_864 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  bool arg1 = gsi::arg_reader<bool >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkCookie *)cls)->setSecure (arg1);
}


// void QNetworkCookie::setValue(const QByteArray &value)


static void _init_f_setValue_2309 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("value");
  decl->add_arg<const QByteArray & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setValue_2309 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QByteArray &arg1 = gsi::arg_reader<const QByteArray & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkCookie *)cls)->setValue (arg1);
}


// QByteArray QNetworkCookie::toRawForm(QNetworkCookie::RawForm form)


static void _init_f_toRawForm_c2683 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("form", true, "QNetworkCookie::Full");
  decl->add_arg<const qt_gsi::Converter<QNetworkCookie::RawForm>::target_type & > (argspec_0);
  decl->set_return<QByteArray > ();
}

static void _call_f_toRawForm_c2683 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const qt_gsi::Converter<QNetworkCookie::RawForm>::target_type & arg1 = args ? gsi::arg_reader<const qt_gsi::Converter<QNetworkCookie::RawForm>::target_type & >() (args, heap) : gsi::arg_maker<const qt_gsi::Converter<QNetworkCookie::RawForm>::target_type & >() (qt_gsi::CppToQtReadAdaptor<QNetworkCookie::RawForm>(heap, QNetworkCookie::Full), heap);
  ret.write<QByteArray > ((QByteArray)((QNetworkCookie *)cls)->toRawForm (qt_gsi::QtToCppAdaptor<QNetworkCookie::RawForm>(arg1).cref()));
}


// QByteArray QNetworkCookie::value()


static void _init_f_value_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QByteArray > ();
}

static void _call_f_value_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QByteArray > ((QByteArray)((QNetworkCookie *)cls)->value ());
}


// static QList<QNetworkCookie> QNetworkCookie::parseCookies(const QByteArray &cookieString)


static void _init_f_parseCookies_2309 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("cookieString");
  decl->add_arg<const QByteArray & > (argspec_0);
  decl->set_return<QList<QNetworkCookie> > ();
}

static void _call_f_parseCookies_2309 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QByteArray &arg1 = gsi::arg_reader<const QByteArray & >() (args, heap);
  ret.write<QList<QNetworkCookie> > ((QList<QNetworkCookie>)QNetworkCookie::parseCookies (arg1));
}



namespace gsi
{

static gsi::Methods methods_QNetworkCookie () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QNetworkCookie::QNetworkCookie(const QByteArray &name, const QByteArray &value)\nThis method creates an object of class QNetworkCookie.", &_init_ctor_QNetworkCookie_4510, &_call_ctor_QNetworkCookie_4510);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QNetworkCookie::QNetworkCookie(const QNetworkCookie &other)\nThis method creates an object of class QNetworkCookie.", &_init_ctor_QNetworkCookie_2742, &_call_ctor_QNetworkCookie_2742);
  methods += new qt_gsi::GenericMethod (":domain", "@brief Method QString QNetworkCookie::domain()\n", true, &_init_f_domain_c0, &_call_f_domain_c0);
  methods += new qt_gsi::GenericMethod (":expirationDate", "@brief Method QDateTime QNetworkCookie::expirationDate()\n", true, &_init_f_expirationDate_c0, &_call_f_expirationDate_c0);
  methods += new qt_gsi::GenericMethod ("isHttpOnly?|:httpOnly", "@brief Method bool QNetworkCookie::isHttpOnly()\n", true, &_init_f_isHttpOnly_c0, &_call_f_isHttpOnly_c0);
  methods += new qt_gsi::GenericMethod ("isSecure?|:secure", "@brief Method bool QNetworkCookie::isSecure()\n", true, &_init_f_isSecure_c0, &_call_f_isSecure_c0);
  methods += new qt_gsi::GenericMethod ("isSessionCookie?", "@brief Method bool QNetworkCookie::isSessionCookie()\n", true, &_init_f_isSessionCookie_c0, &_call_f_isSessionCookie_c0);
  methods += new qt_gsi::GenericMethod (":name", "@brief Method QByteArray QNetworkCookie::name()\n", true, &_init_f_name_c0, &_call_f_name_c0);
  methods += new qt_gsi::GenericMethod ("!=", "@brief Method bool QNetworkCookie::operator!=(const QNetworkCookie &other)\n", true, &_init_f_operator_excl__eq__c2742, &_call_f_operator_excl__eq__c2742);
  methods += new qt_gsi::GenericMethod ("assign", "@brief Method QNetworkCookie &QNetworkCookie::operator=(const QNetworkCookie &other)\n", false, &_init_f_operator_eq__2742, &_call_f_operator_eq__2742);
  methods += new qt_gsi::GenericMethod ("==", "@brief Method bool QNetworkCookie::operator==(const QNetworkCookie &other)\n", true, &_init_f_operator_eq__eq__c2742, &_call_f_operator_eq__eq__c2742);
  methods += new qt_gsi::GenericMethod (":path", "@brief Method QString QNetworkCookie::path()\n", true, &_init_f_path_c0, &_call_f_path_c0);
  methods += new qt_gsi::GenericMethod ("setDomain|domain=", "@brief Method void QNetworkCookie::setDomain(const QString &domain)\n", false, &_init_f_setDomain_2025, &_call_f_setDomain_2025);
  methods += new qt_gsi::GenericMethod ("setExpirationDate|expirationDate=", "@brief Method void QNetworkCookie::setExpirationDate(const QDateTime &date)\n", false, &_init_f_setExpirationDate_2175, &_call_f_setExpirationDate_2175);
  methods += new qt_gsi::GenericMethod ("setHttpOnly|httpOnly=", "@brief Method void QNetworkCookie::setHttpOnly(bool enable)\n", false, &_init_f_setHttpOnly_864, &_call_f_setHttpOnly_864);
  methods += new qt_gsi::GenericMethod ("setName|name=", "@brief Method void QNetworkCookie::setName(const QByteArray &cookieName)\n", false, &_init_f_setName_2309, &_call_f_setName_2309);
  methods += new qt_gsi::GenericMethod ("setPath|path=", "@brief Method void QNetworkCookie::setPath(const QString &path)\n", false, &_init_f_setPath_2025, &_call_f_setPath_2025);
  methods += new qt_gsi::GenericMethod ("setSecure|secure=", "@brief Method void QNetworkCookie::setSecure(bool enable)\n", false, &_init_f_setSecure_864, &_call_f_setSecure_864);
  methods += new qt_gsi::GenericMethod ("setValue|value=", "@brief Method void QNetworkCookie::setValue(const QByteArray &value)\n", false, &_init_f_setValue_2309, &_call_f_setValue_2309);
  methods += new qt_gsi::GenericMethod ("toRawForm", "@brief Method QByteArray QNetworkCookie::toRawForm(QNetworkCookie::RawForm form)\n", true, &_init_f_toRawForm_c2683, &_call_f_toRawForm_c2683);
  methods += new qt_gsi::GenericMethod (":value", "@brief Method QByteArray QNetworkCookie::value()\n", true, &_init_f_value_c0, &_call_f_value_c0);
  methods += new qt_gsi::GenericStaticMethod ("parseCookies", "@brief Static method QList<QNetworkCookie> QNetworkCookie::parseCookies(const QByteArray &cookieString)\nThis method is static and can be called without an instance.", &_init_f_parseCookies_2309, &_call_f_parseCookies_2309);
  return methods;
}

gsi::Class<QNetworkCookie> decl_QNetworkCookie ("QtNetwork", "QNetworkCookie",
  methods_QNetworkCookie (),
  "@qt\n@brief Binding of QNetworkCookie");


GSI_QTNETWORK_PUBLIC gsi::Class<QNetworkCookie> &qtdecl_QNetworkCookie () { return decl_QNetworkCookie; }

}


//  Implementation of the enum wrapper class for QNetworkCookie::RawForm
namespace qt_gsi
{

static gsi::Enum<QNetworkCookie::RawForm> decl_QNetworkCookie_RawForm_Enum ("QtNetwork", "QNetworkCookie_RawForm",
    gsi::enum_const ("NameAndValueOnly", QNetworkCookie::NameAndValueOnly, "@brief Enum constant QNetworkCookie::NameAndValueOnly") +
    gsi::enum_const ("Full", QNetworkCookie::Full, "@brief Enum constant QNetworkCookie::Full"),
  "@qt\n@brief This class represents the QNetworkCookie::RawForm enum");

static gsi::QFlagsClass<QNetworkCookie::RawForm > decl_QNetworkCookie_RawForm_Enums ("QtNetwork", "QNetworkCookie_QFlags_RawForm",
  "@qt\n@brief This class represents the QFlags<QNetworkCookie::RawForm> flag set");

//  Inject the declarations into the parent
static gsi::ClassExt<QNetworkCookie> inject_QNetworkCookie_RawForm_Enum_in_parent (decl_QNetworkCookie_RawForm_Enum.defs ());
static gsi::ClassExt<QNetworkCookie> decl_QNetworkCookie_RawForm_Enum_as_child (decl_QNetworkCookie_RawForm_Enum, "RawForm");
static gsi::ClassExt<QNetworkCookie> decl_QNetworkCookie_RawForm_Enums_as_child (decl_QNetworkCookie_RawForm_Enums, "QFlags_RawForm");

}

