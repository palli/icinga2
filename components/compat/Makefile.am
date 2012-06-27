## Process this file with automake to produce Makefile.in

pkglib_LTLIBRARIES = \
	compat.la

compat_la_SOURCES = \
	compatcomponent.cpp \
	compatcomponent.h \
	i2-compat.h

compat_la_CPPFLAGS = \
	$(BOOST_CPPFLAGS) \
	-I${top_srcdir}/base \
	-I${top_srcdir}/jsonrpc \
	-I${top_srcdir}/icinga

compat_la_LDFLAGS = \
	$(BOOST_LDFLAGS) \
	-module \
	-no-undefined \
	@RELEASE_INFO@ \
	@VERSION_INFO@

compat_la_LIBADD = \
	${top_builddir}/base/libbase.la \
	${top_builddir}/jsonrpc/libjsonrpc.la \
	${top_builddir}/icinga/libicinga.la