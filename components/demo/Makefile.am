## Process this file with automake to produce Makefile.in

pkglib_LTLIBRARIES =  \
	demo.la

demo_la_SOURCES =  \
	democomponent.cpp \
	democomponent.h \
	i2-demo.h

demo_la_CXXFLAGS = -I${top_srcdir}/base \
	-I${top_srcdir}/jsonrpc \
	-I${top_srcdir}/cJSON \
	-I${top_srcdir}/icinga

demo_la_LDFLAGS = -module -version-info 0:0:0 -no-undefined -pthread
demo_la_LIBADD = ${top_builddir}/base/libbase.la \
	${top_builddir}/jsonrpc/libjsonrpc.la \
	${top_builddir}/cJSON/libcJSON.la \
	${top_builddir}/icinga/libicinga.la