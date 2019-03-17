
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
*  @file gsiDeclQNetworkProxyQuery.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QNetworkProxyQuery>
#include <QUrl>
#include "gsiQt.h"
#include "gsiQtNetworkCommon.h"
#include "gsiDeclQtNetworkTypeTraits.h"
#include <memory>

// -----------------------------------------------------------------------
// class QNetworkProxyQuery

//  Constructor QNetworkProxyQuery::QNetworkProxyQuery()


static void _init_ctor_QNetworkProxyQuery_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QNetworkProxyQuery> ();
}

static void _call_ctor_QNetworkProxyQuery_0 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QNetworkProxyQuery *> (new QNetworkProxyQuery ());
}


//  Constructor QNetworkProxyQuery::QNetworkProxyQuery(const QUrl &requestUrl, QNetworkProxyQuery::QueryType queryType)


static void _init_ctor_QNetworkProxyQuery_5004 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("requestUrl");
  decl->add_arg<const QUrl & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("queryType", true, "QNetworkProxyQuery::UrlRequest");
  decl->add_arg<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & > (argspec_1);
  decl->set_return_new<QNetworkProxyQuery> ();
}

static void _call_ctor_QNetworkProxyQuery_5004 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QUrl &arg1 = gsi::arg_reader<const QUrl & >() (args, heap);
  const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & arg2 = args ? gsi::arg_reader<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & >() (args, heap) : gsi::arg_maker<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & >() (qt_gsi::CppToQtReadAdaptor<QNetworkProxyQuery::QueryType>(heap, QNetworkProxyQuery::UrlRequest), heap);
  ret.write<QNetworkProxyQuery *> (new QNetworkProxyQuery (arg1, qt_gsi::QtToCppAdaptor<QNetworkProxyQuery::QueryType>(arg2).cref()));
}


//  Constructor QNetworkProxyQuery::QNetworkProxyQuery(const QString &hostname, int port, const QString &protocolTag, QNetworkProxyQuery::QueryType queryType)


static void _init_ctor_QNetworkProxyQuery_7904 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("hostname");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("port");
  decl->add_arg<int > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("protocolTag", true, "QString()");
  decl->add_arg<const QString & > (argspec_2);
  static gsi::ArgSpecBase argspec_3 ("queryType", true, "QNetworkProxyQuery::TcpSocket");
  decl->add_arg<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & > (argspec_3);
  decl->set_return_new<QNetworkProxyQuery> ();
}

static void _call_ctor_QNetworkProxyQuery_7904 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QString &arg1 = gsi::arg_reader<const QString & >() (args, heap);
  int arg2 = gsi::arg_reader<int >() (args, heap);
  const QString &arg3 = args ? gsi::arg_reader<const QString & >() (args, heap) : gsi::arg_maker<const QString & >() (QString(), heap);
  const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & arg4 = args ? gsi::arg_reader<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & >() (args, heap) : gsi::arg_maker<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & >() (qt_gsi::CppToQtReadAdaptor<QNetworkProxyQuery::QueryType>(heap, QNetworkProxyQuery::TcpSocket), heap);
  ret.write<QNetworkProxyQuery *> (new QNetworkProxyQuery (arg1, arg2, arg3, qt_gsi::QtToCppAdaptor<QNetworkProxyQuery::QueryType>(arg4).cref()));
}


//  Constructor QNetworkProxyQuery::QNetworkProxyQuery(quint16 bindPort, const QString &protocolTag, QNetworkProxyQuery::QueryType queryType)


static void _init_ctor_QNetworkProxyQuery_6320 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("bindPort");
  decl->add_arg<quint16 > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("protocolTag", true, "QString()");
  decl->add_arg<const QString & > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("queryType", true, "QNetworkProxyQuery::TcpServer");
  decl->add_arg<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & > (argspec_2);
  decl->set_return_new<QNetworkProxyQuery> ();
}

static void _call_ctor_QNetworkProxyQuery_6320 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  quint16 arg1 = gsi::arg_reader<quint16 >() (args, heap);
  const QString &arg2 = args ? gsi::arg_reader<const QString & >() (args, heap) : gsi::arg_maker<const QString & >() (QString(), heap);
  const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & arg3 = args ? gsi::arg_reader<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & >() (args, heap) : gsi::arg_maker<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & >() (qt_gsi::CppToQtReadAdaptor<QNetworkProxyQuery::QueryType>(heap, QNetworkProxyQuery::TcpServer), heap);
  ret.write<QNetworkProxyQuery *> (new QNetworkProxyQuery (arg1, arg2, qt_gsi::QtToCppAdaptor<QNetworkProxyQuery::QueryType>(arg3).cref()));
}


//  Constructor QNetworkProxyQuery::QNetworkProxyQuery(const QNetworkProxyQuery &other)


static void _init_ctor_QNetworkProxyQuery_3220 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkProxyQuery & > (argspec_0);
  decl->set_return_new<QNetworkProxyQuery> ();
}

static void _call_ctor_QNetworkProxyQuery_3220 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkProxyQuery &arg1 = gsi::arg_reader<const QNetworkProxyQuery & >() (args, heap);
  ret.write<QNetworkProxyQuery *> (new QNetworkProxyQuery (arg1));
}


// int QNetworkProxyQuery::localPort()


static void _init_f_localPort_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_localPort_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QNetworkProxyQuery *)cls)->localPort ());
}


// bool QNetworkProxyQuery::operator!=(const QNetworkProxyQuery &other)


static void _init_f_operator_excl__eq__c3220 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkProxyQuery & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c3220 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkProxyQuery &arg1 = gsi::arg_reader<const QNetworkProxyQuery & >() (args, heap);
  ret.write<bool > ((bool)((QNetworkProxyQuery *)cls)->operator!= (arg1));
}


// QNetworkProxyQuery &QNetworkProxyQuery::operator=(const QNetworkProxyQuery &other)


static void _init_f_operator_eq__3220 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkProxyQuery & > (argspec_0);
  decl->set_return<QNetworkProxyQuery & > ();
}

static void _call_f_operator_eq__3220 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkProxyQuery &arg1 = gsi::arg_reader<const QNetworkProxyQuery & >() (args, heap);
  ret.write<QNetworkProxyQuery & > ((QNetworkProxyQuery &)((QNetworkProxyQuery *)cls)->operator= (arg1));
}


// bool QNetworkProxyQuery::operator==(const QNetworkProxyQuery &other)


static void _init_f_operator_eq__eq__c3220 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QNetworkProxyQuery & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c3220 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QNetworkProxyQuery &arg1 = gsi::arg_reader<const QNetworkProxyQuery & >() (args, heap);
  ret.write<bool > ((bool)((QNetworkProxyQuery *)cls)->operator== (arg1));
}


// QString QNetworkProxyQuery::peerHostName()


static void _init_f_peerHostName_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_peerHostName_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QNetworkProxyQuery *)cls)->peerHostName ());
}


// int QNetworkProxyQuery::peerPort()


static void _init_f_peerPort_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_peerPort_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QNetworkProxyQuery *)cls)->peerPort ());
}


// QString QNetworkProxyQuery::protocolTag()


static void _init_f_protocolTag_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_protocolTag_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QNetworkProxyQuery *)cls)->protocolTag ());
}


// QNetworkProxyQuery::QueryType QNetworkProxyQuery::queryType()


static void _init_f_queryType_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type > ();
}

static void _call_f_queryType_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type > ((qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type)qt_gsi::CppToQtAdaptor<QNetworkProxyQuery::QueryType>(((QNetworkProxyQuery *)cls)->queryType ()));
}


// void QNetworkProxyQuery::setLocalPort(int port)


static void _init_f_setLocalPort_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("port");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setLocalPort_767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkProxyQuery *)cls)->setLocalPort (arg1);
}


// void QNetworkProxyQuery::setPeerHostName(const QString &hostname)


static void _init_f_setPeerHostName_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("hostname");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPeerHostName_2025 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QString &arg1 = gsi::arg_reader<const QString & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkProxyQuery *)cls)->setPeerHostName (arg1);
}


// void QNetworkProxyQuery::setPeerPort(int port)


static void _init_f_setPeerPort_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("port");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPeerPort_767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkProxyQuery *)cls)->setPeerPort (arg1);
}


// void QNetworkProxyQuery::setProtocolTag(const QString &protocolTag)


static void _init_f_setProtocolTag_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("protocolTag");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setProtocolTag_2025 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QString &arg1 = gsi::arg_reader<const QString & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkProxyQuery *)cls)->setProtocolTag (arg1);
}


// void QNetworkProxyQuery::setQueryType(QNetworkProxyQuery::QueryType type)


static void _init_f_setQueryType_3411 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("type");
  decl->add_arg<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setQueryType_3411 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & arg1 = gsi::arg_reader<const qt_gsi::Converter<QNetworkProxyQuery::QueryType>::target_type & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkProxyQuery *)cls)->setQueryType (qt_gsi::QtToCppAdaptor<QNetworkProxyQuery::QueryType>(arg1).cref());
}


// void QNetworkProxyQuery::setUrl(const QUrl &url)


static void _init_f_setUrl_1701 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("url");
  decl->add_arg<const QUrl & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setUrl_1701 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QUrl &arg1 = gsi::arg_reader<const QUrl & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QNetworkProxyQuery *)cls)->setUrl (arg1);
}


// QUrl QNetworkProxyQuery::url()


static void _init_f_url_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QUrl > ();
}

static void _call_f_url_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QUrl > ((QUrl)((QNetworkProxyQuery *)cls)->url ());
}



namespace gsi
{

static gsi::Methods methods_QNetworkProxyQuery () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QNetworkProxyQuery::QNetworkProxyQuery()\nThis method creates an object of class QNetworkProxyQuery.", &_init_ctor_QNetworkProxyQuery_0, &_call_ctor_QNetworkProxyQuery_0);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QNetworkProxyQuery::QNetworkProxyQuery(const QUrl &requestUrl, QNetworkProxyQuery::QueryType queryType)\nThis method creates an object of class QNetworkProxyQuery.", &_init_ctor_QNetworkProxyQuery_5004, &_call_ctor_QNetworkProxyQuery_5004);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QNetworkProxyQuery::QNetworkProxyQuery(const QString &hostname, int port, const QString &protocolTag, QNetworkProxyQuery::QueryType queryType)\nThis method creates an object of class QNetworkProxyQuery.", &_init_ctor_QNetworkProxyQuery_7904, &_call_ctor_QNetworkProxyQuery_7904);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QNetworkProxyQuery::QNetworkProxyQuery(quint16 bindPort, const QString &protocolTag, QNetworkProxyQuery::QueryType queryType)\nThis method creates an object of class QNetworkProxyQuery.", &_init_ctor_QNetworkProxyQuery_6320, &_call_ctor_QNetworkProxyQuery_6320);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QNetworkProxyQuery::QNetworkProxyQuery(const QNetworkProxyQuery &other)\nThis method creates an object of class QNetworkProxyQuery.", &_init_ctor_QNetworkProxyQuery_3220, &_call_ctor_QNetworkProxyQuery_3220);
  methods += new qt_gsi::GenericMethod (":localPort", "@brief Method int QNetworkProxyQuery::localPort()\n", true, &_init_f_localPort_c0, &_call_f_localPort_c0);
  methods += new qt_gsi::GenericMethod ("!=", "@brief Method bool QNetworkProxyQuery::operator!=(const QNetworkProxyQuery &other)\n", true, &_init_f_operator_excl__eq__c3220, &_call_f_operator_excl__eq__c3220);
  methods += new qt_gsi::GenericMethod ("assign", "@brief Method QNetworkProxyQuery &QNetworkProxyQuery::operator=(const QNetworkProxyQuery &other)\n", false, &_init_f_operator_eq__3220, &_call_f_operator_eq__3220);
  methods += new qt_gsi::GenericMethod ("==", "@brief Method bool QNetworkProxyQuery::operator==(const QNetworkProxyQuery &other)\n", true, &_init_f_operator_eq__eq__c3220, &_call_f_operator_eq__eq__c3220);
  methods += new qt_gsi::GenericMethod (":peerHostName", "@brief Method QString QNetworkProxyQuery::peerHostName()\n", true, &_init_f_peerHostName_c0, &_call_f_peerHostName_c0);
  methods += new qt_gsi::GenericMethod (":peerPort", "@brief Method int QNetworkProxyQuery::peerPort()\n", true, &_init_f_peerPort_c0, &_call_f_peerPort_c0);
  methods += new qt_gsi::GenericMethod (":protocolTag", "@brief Method QString QNetworkProxyQuery::protocolTag()\n", true, &_init_f_protocolTag_c0, &_call_f_protocolTag_c0);
  methods += new qt_gsi::GenericMethod (":queryType", "@brief Method QNetworkProxyQuery::QueryType QNetworkProxyQuery::queryType()\n", true, &_init_f_queryType_c0, &_call_f_queryType_c0);
  methods += new qt_gsi::GenericMethod ("setLocalPort|localPort=", "@brief Method void QNetworkProxyQuery::setLocalPort(int port)\n", false, &_init_f_setLocalPort_767, &_call_f_setLocalPort_767);
  methods += new qt_gsi::GenericMethod ("setPeerHostName|peerHostName=", "@brief Method void QNetworkProxyQuery::setPeerHostName(const QString &hostname)\n", false, &_init_f_setPeerHostName_2025, &_call_f_setPeerHostName_2025);
  methods += new qt_gsi::GenericMethod ("setPeerPort|peerPort=", "@brief Method void QNetworkProxyQuery::setPeerPort(int port)\n", false, &_init_f_setPeerPort_767, &_call_f_setPeerPort_767);
  methods += new qt_gsi::GenericMethod ("setProtocolTag|protocolTag=", "@brief Method void QNetworkProxyQuery::setProtocolTag(const QString &protocolTag)\n", false, &_init_f_setProtocolTag_2025, &_call_f_setProtocolTag_2025);
  methods += new qt_gsi::GenericMethod ("setQueryType|queryType=", "@brief Method void QNetworkProxyQuery::setQueryType(QNetworkProxyQuery::QueryType type)\n", false, &_init_f_setQueryType_3411, &_call_f_setQueryType_3411);
  methods += new qt_gsi::GenericMethod ("setUrl|url=", "@brief Method void QNetworkProxyQuery::setUrl(const QUrl &url)\n", false, &_init_f_setUrl_1701, &_call_f_setUrl_1701);
  methods += new qt_gsi::GenericMethod (":url", "@brief Method QUrl QNetworkProxyQuery::url()\n", true, &_init_f_url_c0, &_call_f_url_c0);
  return methods;
}

gsi::Class<QNetworkProxyQuery> decl_QNetworkProxyQuery ("QtNetwork", "QNetworkProxyQuery",
  methods_QNetworkProxyQuery (),
  "@qt\n@brief Binding of QNetworkProxyQuery");


GSI_QTNETWORK_PUBLIC gsi::Class<QNetworkProxyQuery> &qtdecl_QNetworkProxyQuery () { return decl_QNetworkProxyQuery; }

}


//  Implementation of the enum wrapper class for QNetworkProxyQuery::QueryType
namespace qt_gsi
{

static gsi::Enum<QNetworkProxyQuery::QueryType> decl_QNetworkProxyQuery_QueryType_Enum ("QtNetwork", "QNetworkProxyQuery_QueryType",
    gsi::enum_const ("TcpSocket", QNetworkProxyQuery::TcpSocket, "@brief Enum constant QNetworkProxyQuery::TcpSocket") +
    gsi::enum_const ("UdpSocket", QNetworkProxyQuery::UdpSocket, "@brief Enum constant QNetworkProxyQuery::UdpSocket") +
    gsi::enum_const ("TcpServer", QNetworkProxyQuery::TcpServer, "@brief Enum constant QNetworkProxyQuery::TcpServer") +
    gsi::enum_const ("UrlRequest", QNetworkProxyQuery::UrlRequest, "@brief Enum constant QNetworkProxyQuery::UrlRequest"),
  "@qt\n@brief This class represents the QNetworkProxyQuery::QueryType enum");

static gsi::QFlagsClass<QNetworkProxyQuery::QueryType > decl_QNetworkProxyQuery_QueryType_Enums ("QtNetwork", "QNetworkProxyQuery_QFlags_QueryType",
  "@qt\n@brief This class represents the QFlags<QNetworkProxyQuery::QueryType> flag set");

//  Inject the declarations into the parent
static gsi::ClassExt<QNetworkProxyQuery> inject_QNetworkProxyQuery_QueryType_Enum_in_parent (decl_QNetworkProxyQuery_QueryType_Enum.defs ());
static gsi::ClassExt<QNetworkProxyQuery> decl_QNetworkProxyQuery_QueryType_Enum_as_child (decl_QNetworkProxyQuery_QueryType_Enum, "QueryType");
static gsi::ClassExt<QNetworkProxyQuery> decl_QNetworkProxyQuery_QueryType_Enums_as_child (decl_QNetworkProxyQuery_QueryType_Enums, "QFlags_QueryType");

}

