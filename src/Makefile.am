
GNULIB= ../gnulib/lib/libgnu.la
GNULIB_CFLAGS= -I $(top_srcdir)/gnulib/lib

AM_CFLAGS = $(NETCF_CFLAGS) $(GNULIB_CFLAGS) $(WARN_CFLAGS)

include_HEADERS = netcf.h

lib_LTLIBRARIES = libnetcf.la

if NETCF_DRIVER_INITSCRIPTS
DRIVER_SOURCES = drv_initscripts.c
endif

libnetcf_la_SOURCES = netcf.h netcf.c internal.h \
     $(DRIVER_SOURCES)
libnetcf_la_LIBADD = $(GNULIB)