## Process this file with automake to produce Makefile.in


pkglib_LTLIBRARIES = \
	libconfig.la

BUILT_SOURCES = config_parser.h

AM_YFLAGS = -d

libconfig_la_SOURCES = \
	configcompiler.cpp \
	configcompiler.h \
	config_lexer.ll \
	config_parser.yy \
	i2-config.h \
	configitem.cpp \
	configitem.h \
	configitembuilder.cpp \
	configitembuilder.h \
	debuginfo.h \
	expression.cpp \
	expression.h \
	expressionlist.cpp \
	expressionlist.h

libconfig_la_CPPFLAGS = \
	-DI2_CONFIG_BUILD \
	$(BOOST_CPPFLAGS) \
	-I${top_srcdir}/lib/base

libconfig_la_LDFLAGS = \
	$(BOOST_LDFLAGS) \
	-no-undefined \
	@RELEASE_INFO@ \
	@VERSION_INFO@

libconfig_la_LIBADD = \
	${top_builddir}/lib/base/libbase.la