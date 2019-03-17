
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
*  @file gsiDeclQSwipeGesture.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QSwipeGesture>
#include <QChildEvent>
#include <QEvent>
#include <QObject>
#include <QPointF>
#include <QThread>
#include <QTimerEvent>
#include "gsiQt.h"
#include "gsiQtGuiCommon.h"
#include "gsiDeclQtGuiTypeTraits.h"
#include <memory>

// -----------------------------------------------------------------------
// class QSwipeGesture

//  get static meta object

static void _init_smo (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<const QMetaObject &> ();
}

static void _call_smo (const qt_gsi::GenericStaticMethod *, gsi::SerialArgs &, gsi::SerialArgs &ret) 
{
  ret.write<const QMetaObject &> (QSwipeGesture::staticMetaObject);
}


// QSwipeGesture::SwipeDirection QSwipeGesture::horizontalDirection()


static void _init_f_horizontalDirection_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QSwipeGesture::SwipeDirection>::target_type > ();
}

static void _call_f_horizontalDirection_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<qt_gsi::Converter<QSwipeGesture::SwipeDirection>::target_type > ((qt_gsi::Converter<QSwipeGesture::SwipeDirection>::target_type)qt_gsi::CppToQtAdaptor<QSwipeGesture::SwipeDirection>(((QSwipeGesture *)cls)->horizontalDirection ()));
}


// void QSwipeGesture::setSwipeAngle(double value)


static void _init_f_setSwipeAngle_1071 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("value");
  decl->add_arg<double > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setSwipeAngle_1071 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  double arg1 = gsi::arg_reader<double >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QSwipeGesture *)cls)->setSwipeAngle (arg1);
}


// double QSwipeGesture::swipeAngle()


static void _init_f_swipeAngle_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<double > ();
}

static void _call_f_swipeAngle_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<double > ((double)((QSwipeGesture *)cls)->swipeAngle ());
}


// QSwipeGesture::SwipeDirection QSwipeGesture::verticalDirection()


static void _init_f_verticalDirection_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QSwipeGesture::SwipeDirection>::target_type > ();
}

static void _call_f_verticalDirection_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<qt_gsi::Converter<QSwipeGesture::SwipeDirection>::target_type > ((qt_gsi::Converter<QSwipeGesture::SwipeDirection>::target_type)qt_gsi::CppToQtAdaptor<QSwipeGesture::SwipeDirection>(((QSwipeGesture *)cls)->verticalDirection ()));
}


// static QString QSwipeGesture::tr(const char *s, const char *c)


static void _init_f_tr_3354 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<QString > ();
}

static void _call_f_tr_3354 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const char *arg1 = gsi::arg_reader<const char * >() (args, heap);
  const char *arg2 = args ? gsi::arg_reader<const char * >() (args, heap) : gsi::arg_maker<const char * >() (0, heap);
  ret.write<QString > ((QString)QSwipeGesture::tr (arg1, arg2));
}


// static QString QSwipeGesture::tr(const char *s, const char *c, int n)


static void _init_f_tr_4013 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c");
  decl->add_arg<const char * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("n");
  decl->add_arg<int > (argspec_2);
  decl->set_return<QString > ();
}

static void _call_f_tr_4013 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const char *arg1 = gsi::arg_reader<const char * >() (args, heap);
  const char *arg2 = gsi::arg_reader<const char * >() (args, heap);
  int arg3 = gsi::arg_reader<int >() (args, heap);
  ret.write<QString > ((QString)QSwipeGesture::tr (arg1, arg2, arg3));
}


// static QString QSwipeGesture::trUtf8(const char *s, const char *c)


static void _init_f_trUtf8_3354 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<QString > ();
}

static void _call_f_trUtf8_3354 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const char *arg1 = gsi::arg_reader<const char * >() (args, heap);
  const char *arg2 = args ? gsi::arg_reader<const char * >() (args, heap) : gsi::arg_maker<const char * >() (0, heap);
  ret.write<QString > ((QString)QSwipeGesture::trUtf8 (arg1, arg2));
}


// static QString QSwipeGesture::trUtf8(const char *s, const char *c, int n)


static void _init_f_trUtf8_4013 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c");
  decl->add_arg<const char * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("n");
  decl->add_arg<int > (argspec_2);
  decl->set_return<QString > ();
}

static void _call_f_trUtf8_4013 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const char *arg1 = gsi::arg_reader<const char * >() (args, heap);
  const char *arg2 = gsi::arg_reader<const char * >() (args, heap);
  int arg3 = gsi::arg_reader<int >() (args, heap);
  ret.write<QString > ((QString)QSwipeGesture::trUtf8 (arg1, arg2, arg3));
}


namespace gsi
{

static gsi::Methods methods_QSwipeGesture () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("staticMetaObject", "@brief Obtains the static MetaObject for this class.", &_init_smo, &_call_smo);
  methods += new qt_gsi::GenericMethod (":horizontalDirection", "@brief Method QSwipeGesture::SwipeDirection QSwipeGesture::horizontalDirection()\n", true, &_init_f_horizontalDirection_c0, &_call_f_horizontalDirection_c0);
  methods += new qt_gsi::GenericMethod ("setSwipeAngle|swipeAngle=", "@brief Method void QSwipeGesture::setSwipeAngle(double value)\n", false, &_init_f_setSwipeAngle_1071, &_call_f_setSwipeAngle_1071);
  methods += new qt_gsi::GenericMethod (":swipeAngle", "@brief Method double QSwipeGesture::swipeAngle()\n", true, &_init_f_swipeAngle_c0, &_call_f_swipeAngle_c0);
  methods += new qt_gsi::GenericMethod (":verticalDirection", "@brief Method QSwipeGesture::SwipeDirection QSwipeGesture::verticalDirection()\n", true, &_init_f_verticalDirection_c0, &_call_f_verticalDirection_c0);
  methods += gsi::qt_signal<QObject * > ("destroyed(QObject *)", "destroyed", gsi::arg("arg1"), "@brief Signal declaration for QSwipeGesture::destroyed(QObject *)\nYou can bind a procedure to this signal.");
  methods += new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QSwipeGesture::tr(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_tr_3354, &_call_f_tr_3354);
  methods += new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QSwipeGesture::tr(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_tr_4013, &_call_f_tr_4013);
  methods += new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QSwipeGesture::trUtf8(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_3354, &_call_f_trUtf8_3354);
  methods += new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QSwipeGesture::trUtf8(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_4013, &_call_f_trUtf8_4013);
  return methods;
}

gsi::Class<QGesture> &qtdecl_QGesture ();

qt_gsi::QtNativeClass<QSwipeGesture> decl_QSwipeGesture (qtdecl_QGesture (), "QtGui", "QSwipeGesture_Native",
  methods_QSwipeGesture (),
  "@hide\n@alias QSwipeGesture");

GSI_QTGUI_PUBLIC gsi::Class<QSwipeGesture> &qtdecl_QSwipeGesture () { return decl_QSwipeGesture; }

}


class QSwipeGesture_Adaptor : public QSwipeGesture, public qt_gsi::QtObjectBase
{
public:

  virtual ~QSwipeGesture_Adaptor();

  //  [adaptor ctor] QSwipeGesture::QSwipeGesture(QObject *parent)
  QSwipeGesture_Adaptor() : QSwipeGesture()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QSwipeGesture::QSwipeGesture(QObject *parent)
  QSwipeGesture_Adaptor(QObject *parent) : QSwipeGesture(parent)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [expose] int QSwipeGesture::receivers(const char *signal)
  int fp_QSwipeGesture_receivers_c1731 (const char *signal) const {
    return QSwipeGesture::receivers(signal);
  }

  //  [expose] QObject *QSwipeGesture::sender()
  QObject * fp_QSwipeGesture_sender_c0 () const {
    return QSwipeGesture::sender();
  }

  //  [adaptor impl] bool QSwipeGesture::event(QEvent *)
  bool cbs_event_1217_0(QEvent *arg1)
  {
    return QSwipeGesture::event(arg1);
  }

  virtual bool event(QEvent *arg1)
  {
    if (cb_event_1217_0.can_issue()) {
      return cb_event_1217_0.issue<QSwipeGesture_Adaptor, bool, QEvent *>(&QSwipeGesture_Adaptor::cbs_event_1217_0, arg1);
    } else {
      return QSwipeGesture::event(arg1);
    }
  }

  //  [adaptor impl] bool QSwipeGesture::eventFilter(QObject *, QEvent *)
  bool cbs_eventFilter_2411_0(QObject *arg1, QEvent *arg2)
  {
    return QSwipeGesture::eventFilter(arg1, arg2);
  }

  virtual bool eventFilter(QObject *arg1, QEvent *arg2)
  {
    if (cb_eventFilter_2411_0.can_issue()) {
      return cb_eventFilter_2411_0.issue<QSwipeGesture_Adaptor, bool, QObject *, QEvent *>(&QSwipeGesture_Adaptor::cbs_eventFilter_2411_0, arg1, arg2);
    } else {
      return QSwipeGesture::eventFilter(arg1, arg2);
    }
  }

  //  [adaptor impl] void QSwipeGesture::childEvent(QChildEvent *)
  void cbs_childEvent_1701_0(QChildEvent *arg1)
  {
    QSwipeGesture::childEvent(arg1);
  }

  virtual void childEvent(QChildEvent *arg1)
  {
    if (cb_childEvent_1701_0.can_issue()) {
      cb_childEvent_1701_0.issue<QSwipeGesture_Adaptor, QChildEvent *>(&QSwipeGesture_Adaptor::cbs_childEvent_1701_0, arg1);
    } else {
      QSwipeGesture::childEvent(arg1);
    }
  }

  //  [adaptor impl] void QSwipeGesture::customEvent(QEvent *)
  void cbs_customEvent_1217_0(QEvent *arg1)
  {
    QSwipeGesture::customEvent(arg1);
  }

  virtual void customEvent(QEvent *arg1)
  {
    if (cb_customEvent_1217_0.can_issue()) {
      cb_customEvent_1217_0.issue<QSwipeGesture_Adaptor, QEvent *>(&QSwipeGesture_Adaptor::cbs_customEvent_1217_0, arg1);
    } else {
      QSwipeGesture::customEvent(arg1);
    }
  }

  //  [emitter impl] void QSwipeGesture::destroyed(QObject *)
  void emitter_QSwipeGesture_destroyed_1302(QObject *arg1)
  {
    emit QSwipeGesture::destroyed(arg1);
  }

  //  [adaptor impl] void QSwipeGesture::disconnectNotify(const char *signal)
  void cbs_disconnectNotify_1731_0(const char *signal)
  {
    QSwipeGesture::disconnectNotify(signal);
  }

  virtual void disconnectNotify(const char *signal)
  {
    if (cb_disconnectNotify_1731_0.can_issue()) {
      cb_disconnectNotify_1731_0.issue<QSwipeGesture_Adaptor, const char *>(&QSwipeGesture_Adaptor::cbs_disconnectNotify_1731_0, signal);
    } else {
      QSwipeGesture::disconnectNotify(signal);
    }
  }

  //  [adaptor impl] void QSwipeGesture::timerEvent(QTimerEvent *)
  void cbs_timerEvent_1730_0(QTimerEvent *arg1)
  {
    QSwipeGesture::timerEvent(arg1);
  }

  virtual void timerEvent(QTimerEvent *arg1)
  {
    if (cb_timerEvent_1730_0.can_issue()) {
      cb_timerEvent_1730_0.issue<QSwipeGesture_Adaptor, QTimerEvent *>(&QSwipeGesture_Adaptor::cbs_timerEvent_1730_0, arg1);
    } else {
      QSwipeGesture::timerEvent(arg1);
    }
  }

  gsi::Callback cb_event_1217_0;
  gsi::Callback cb_eventFilter_2411_0;
  gsi::Callback cb_childEvent_1701_0;
  gsi::Callback cb_customEvent_1217_0;
  gsi::Callback cb_disconnectNotify_1731_0;
  gsi::Callback cb_timerEvent_1730_0;
};

QSwipeGesture_Adaptor::~QSwipeGesture_Adaptor() { }

//  Constructor QSwipeGesture::QSwipeGesture(QObject *parent) (adaptor class)

static void _init_ctor_QSwipeGesture_Adaptor_1302 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "0");
  decl->add_arg<QObject * > (argspec_0);
  decl->set_return_new<QSwipeGesture_Adaptor> ();
}

static void _call_ctor_QSwipeGesture_Adaptor_1302 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QObject *arg1 = args ? gsi::arg_reader<QObject * >() (args, heap) : gsi::arg_maker<QObject * >() (0, heap);
  ret.write<QSwipeGesture_Adaptor *> (new QSwipeGesture_Adaptor (arg1));
}


// void QSwipeGesture::childEvent(QChildEvent *)

static void _init_cbs_childEvent_1701_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QChildEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_childEvent_1701_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QChildEvent *arg1 = args.read<QChildEvent * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QSwipeGesture_Adaptor *)cls)->cbs_childEvent_1701_0 (arg1);
}

static void _set_callback_cbs_childEvent_1701_0 (void *cls, const gsi::Callback &cb)
{
  ((QSwipeGesture_Adaptor *)cls)->cb_childEvent_1701_0 = cb;
}


// void QSwipeGesture::customEvent(QEvent *)

static void _init_cbs_customEvent_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_customEvent_1217_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QEvent *arg1 = args.read<QEvent * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QSwipeGesture_Adaptor *)cls)->cbs_customEvent_1217_0 (arg1);
}

static void _set_callback_cbs_customEvent_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QSwipeGesture_Adaptor *)cls)->cb_customEvent_1217_0 = cb;
}


// emitter void QSwipeGesture::destroyed(QObject *)

static void _init_emitter_destroyed_1302 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1", true, "0");
  decl->add_arg<QObject * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_emitter_destroyed_1302 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs & /*ret*/) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QObject *arg1 = args ? gsi::arg_reader<QObject * >() (args, heap) : gsi::arg_maker<QObject * >() (0, heap);
  ((QSwipeGesture_Adaptor *)cls)->emitter_QSwipeGesture_destroyed_1302 (arg1);
}


// void QSwipeGesture::disconnectNotify(const char *signal)

static void _init_cbs_disconnectNotify_1731_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_disconnectNotify_1731_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const char *arg1 = args.read<const char * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QSwipeGesture_Adaptor *)cls)->cbs_disconnectNotify_1731_0 (arg1);
}

static void _set_callback_cbs_disconnectNotify_1731_0 (void *cls, const gsi::Callback &cb)
{
  ((QSwipeGesture_Adaptor *)cls)->cb_disconnectNotify_1731_0 = cb;
}


// bool QSwipeGesture::event(QEvent *)

static void _init_cbs_event_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_cbs_event_1217_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QEvent *arg1 = args.read<QEvent * > (heap);
  ret.write<bool > ((bool)((QSwipeGesture_Adaptor *)cls)->cbs_event_1217_0 (arg1));
}

static void _set_callback_cbs_event_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QSwipeGesture_Adaptor *)cls)->cb_event_1217_0 = cb;
}


// bool QSwipeGesture::eventFilter(QObject *, QEvent *)

static void _init_cbs_eventFilter_2411_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QObject * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("arg2");
  decl->add_arg<QEvent * > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_cbs_eventFilter_2411_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QObject *arg1 = args.read<QObject * > (heap);
  QEvent *arg2 = args.read<QEvent * > (heap);
  ret.write<bool > ((bool)((QSwipeGesture_Adaptor *)cls)->cbs_eventFilter_2411_0 (arg1, arg2));
}

static void _set_callback_cbs_eventFilter_2411_0 (void *cls, const gsi::Callback &cb)
{
  ((QSwipeGesture_Adaptor *)cls)->cb_eventFilter_2411_0 = cb;
}


// exposed int QSwipeGesture::receivers(const char *signal)

static void _init_fp_receivers_c1731 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<int > ();
}

static void _call_fp_receivers_c1731 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const char *arg1 = gsi::arg_reader<const char * >() (args, heap);
  ret.write<int > ((int)((QSwipeGesture_Adaptor *)cls)->fp_QSwipeGesture_receivers_c1731 (arg1));
}


// exposed QObject *QSwipeGesture::sender()

static void _init_fp_sender_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QObject * > ();
}

static void _call_fp_sender_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QObject * > ((QObject *)((QSwipeGesture_Adaptor *)cls)->fp_QSwipeGesture_sender_c0 ());
}


// void QSwipeGesture::timerEvent(QTimerEvent *)

static void _init_cbs_timerEvent_1730_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QTimerEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_timerEvent_1730_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QTimerEvent *arg1 = args.read<QTimerEvent * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QSwipeGesture_Adaptor *)cls)->cbs_timerEvent_1730_0 (arg1);
}

static void _set_callback_cbs_timerEvent_1730_0 (void *cls, const gsi::Callback &cb)
{
  ((QSwipeGesture_Adaptor *)cls)->cb_timerEvent_1730_0 = cb;
}


namespace gsi
{

gsi::Class<QSwipeGesture> &qtdecl_QSwipeGesture ();

static gsi::Methods methods_QSwipeGesture_Adaptor () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSwipeGesture::QSwipeGesture(QObject *parent)\nThis method creates an object of class QSwipeGesture.", &_init_ctor_QSwipeGesture_Adaptor_1302, &_call_ctor_QSwipeGesture_Adaptor_1302);
  methods += new qt_gsi::GenericMethod ("*childEvent", "@hide", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0);
  methods += new qt_gsi::GenericMethod ("*childEvent", "@brief Virtual method void QSwipeGesture::childEvent(QChildEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0, &_set_callback_cbs_childEvent_1701_0);
  methods += new qt_gsi::GenericMethod ("*customEvent", "@hide", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0);
  methods += new qt_gsi::GenericMethod ("*customEvent", "@brief Virtual method void QSwipeGesture::customEvent(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0, &_set_callback_cbs_customEvent_1217_0);
  methods += new qt_gsi::GenericMethod ("emit_destroyed", "@brief Emitter for signal void QSwipeGesture::destroyed(QObject *)\nCall this method to emit this signal.", false, &_init_emitter_destroyed_1302, &_call_emitter_destroyed_1302);
  methods += new qt_gsi::GenericMethod ("*disconnectNotify", "@hide", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0);
  methods += new qt_gsi::GenericMethod ("*disconnectNotify", "@brief Virtual method void QSwipeGesture::disconnectNotify(const char *signal)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0, &_set_callback_cbs_disconnectNotify_1731_0);
  methods += new qt_gsi::GenericMethod ("event", "@hide", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0);
  methods += new qt_gsi::GenericMethod ("event", "@brief Virtual method bool QSwipeGesture::event(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0, &_set_callback_cbs_event_1217_0);
  methods += new qt_gsi::GenericMethod ("eventFilter", "@hide", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0);
  methods += new qt_gsi::GenericMethod ("eventFilter", "@brief Virtual method bool QSwipeGesture::eventFilter(QObject *, QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0, &_set_callback_cbs_eventFilter_2411_0);
  methods += new qt_gsi::GenericMethod ("*receivers", "@brief Method int QSwipeGesture::receivers(const char *signal)\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_receivers_c1731, &_call_fp_receivers_c1731);
  methods += new qt_gsi::GenericMethod ("*sender", "@brief Method QObject *QSwipeGesture::sender()\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_sender_c0, &_call_fp_sender_c0);
  methods += new qt_gsi::GenericMethod ("*timerEvent", "@hide", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0);
  methods += new qt_gsi::GenericMethod ("*timerEvent", "@brief Virtual method void QSwipeGesture::timerEvent(QTimerEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0, &_set_callback_cbs_timerEvent_1730_0);
  return methods;
}

gsi::Class<QSwipeGesture_Adaptor> decl_QSwipeGesture_Adaptor (qtdecl_QSwipeGesture (), "QtGui", "QSwipeGesture",
  methods_QSwipeGesture_Adaptor (),
  "@qt\n@brief Binding of QSwipeGesture");

}


//  Implementation of the enum wrapper class for QSwipeGesture::SwipeDirection
namespace qt_gsi
{

static gsi::Enum<QSwipeGesture::SwipeDirection> decl_QSwipeGesture_SwipeDirection_Enum ("QtGui", "QSwipeGesture_SwipeDirection",
    gsi::enum_const ("NoDirection", QSwipeGesture::NoDirection, "@brief Enum constant QSwipeGesture::NoDirection") +
    gsi::enum_const ("Left", QSwipeGesture::Left, "@brief Enum constant QSwipeGesture::Left") +
    gsi::enum_const ("Right", QSwipeGesture::Right, "@brief Enum constant QSwipeGesture::Right") +
    gsi::enum_const ("Up", QSwipeGesture::Up, "@brief Enum constant QSwipeGesture::Up") +
    gsi::enum_const ("Down", QSwipeGesture::Down, "@brief Enum constant QSwipeGesture::Down"),
  "@qt\n@brief This class represents the QSwipeGesture::SwipeDirection enum");

static gsi::QFlagsClass<QSwipeGesture::SwipeDirection > decl_QSwipeGesture_SwipeDirection_Enums ("QtGui", "QSwipeGesture_QFlags_SwipeDirection",
  "@qt\n@brief This class represents the QFlags<QSwipeGesture::SwipeDirection> flag set");

//  Inject the declarations into the parent
static gsi::ClassExt<QSwipeGesture> inject_QSwipeGesture_SwipeDirection_Enum_in_parent (decl_QSwipeGesture_SwipeDirection_Enum.defs ());
static gsi::ClassExt<QSwipeGesture> decl_QSwipeGesture_SwipeDirection_Enum_as_child (decl_QSwipeGesture_SwipeDirection_Enum, "SwipeDirection");
static gsi::ClassExt<QSwipeGesture> decl_QSwipeGesture_SwipeDirection_Enums_as_child (decl_QSwipeGesture_SwipeDirection_Enums, "QFlags_SwipeDirection");

}

