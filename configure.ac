AC_INIT(netcf, 0.1.7)
AC_CONFIG_SRCDIR([src/netcf.c])
AC_CONFIG_AUX_DIR([build/aux])
AC_CONFIG_MACRO_DIR([gnulib/m4])
AM_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([-Wno-portability 1.11 color-tests parallel-tests])
AM_SILENT_RULES([yes]) # make --enable-silent-rules the default.

AC_SUBST([LIBNETCF_VERSION_INFO], [4:3:3])

AC_GNU_SOURCE

AC_PROG_CC
gl_EARLY

AC_PROG_LIBTOOL

dnl The backend driver. Right now hardcoded to initscripts, but
dnl eventually needs to be configurable at buildtime
dnl temporary, if win32 then dont build this.
AC_CANONICAL_HOST

dnl WIN32
AC_MSG_CHECKING([for win32 platform])
PLATFORM_WIN32="no"
case "$host" in
	*-*-mingw*)
		PLATFORM_WIN32="yes"
	;;
	*)
	;;
esac
AC_MSG_RESULT([$PLATFORM_WIN32])
AM_CONDITIONAL(PLATFORM_WIN32, test "${PLATFORM_WIN32}" = "yes")
AC_SUBST([PLATFORM_WIN32])
AC_SUBST(MINGW_EXTRA_LDFLAGS)

dnl Compiler flags to be used everywhere
AC_SUBST([NETCF_CFLAGS], ['--std=gnu99 -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fasynchronous-unwind-tables'])

gl_INIT

NETCF_COMPILE_WARNINGS

dnl Need to test if pkg-config exists
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LIBAUGEAS], [augeas >= 0.5.0], [], [AC_DEFINE([HAVE_LIBAUGEAS], [], [Use augeas])])
PKG_CHECK_MODULES([LIBXML], [libxml-2.0])
PKG_CHECK_MODULES([LIBXSLT], [libxslt])
PKG_CHECK_MODULES([LIBEXSLT], [libexslt])
PKG_CHECK_MODULES([LIBNL], [libnl-1], [], [AC_DEFINE([HAVE_LIBNL], [], [Use netlink])])

NETCF_CHECK_READLINE

NETCF_LIBDEPS=$(echo $LIBAUGEAS_LIBS $LIBEXSLT_LIBS $LIBXSLT_LIBS $LIBXML_LIBS $LIBNL_LIBS)
AC_SUBST([NETCF_LIBDEPS])

AC_CHECK_HEADER([pthread.h],
	[AC_CHECK_LIB([pthread],[pthread_join],[
		AC_DEFINE([HAVE_LIBPTHREAD],[],[Define if pthread (-lpthread)])
		AC_DEFINE([HAVE_PTHREAD_H],[],[Define if <pthread.h>])
		LIBS="-lpthread $LIBS"
	])])

AC_OUTPUT(Makefile                                          \
          gnulib/lib/Makefile                               \
          gnulib/tests/Makefile                             \
          src/Makefile                                      \
          tests/Makefile                                    \
          doc/Makefile                                      \
          netcf.pc netcf.spec mingw32-netcf.spec)
