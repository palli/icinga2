## Process this file with automake to produce Makefile.in


pkglib_LTLIBRARIES =  \
	libicinga.la

libicinga_la_SOURCES =  \
	cib.cpp \
	cib.h \
	host.cpp \
	hostgroup.cpp \
	hostgroup.h \
	host.h \
	i2-icinga.h \
	icingaapplication.cpp \
	icingaapplication.h \
	macroprocessor.cpp \
	macroprocessor.h \
	nagioschecktask.cpp \
	nagioschecktask.h \
	nullchecktask.cpp \
	nullchecktask.h \
	service.cpp \
	servicegroup.cpp \
	servicegroup.h \
	service.h \
	servicestatechangemessage.cpp \
	servicestatechangemessage.h

libicinga_la_CPPFLAGS = \
	-DI2_ICINGA_BUILD \
	$(BOOST_CPPFLAGS) \
	-I${top_srcdir}/lib/base \
	-I${top_srcdir}/lib/config \
	-I${top_srcdir}/lib/remoting \
	-I${top_srcdir}

libicinga_la_LDFLAGS = \
	$(BOOST_LDFLAGS) \
	-no-undefined \
	@RELEASE_INFO@ \
	@VERSION_INFO@

libicinga_la_LIBADD = \
	$(BOOST_THREAD_LIB) \
	${top_builddir}/lib/base/libbase.la \
	${top_builddir}/lib/config/libconfig.la \
	${top_builddir}/lib/remoting/libremoting.la