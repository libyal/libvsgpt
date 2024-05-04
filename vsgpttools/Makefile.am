AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBVSGPT_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vsgptinfo

vsgptinfo_SOURCES = \
	info_handle.c info_handle.h \
	vsgpttools_getopt.c vsgpttools_getopt.h \
	vsgpttools_i18n.h \
	vsgptinfo.c \
	vsgpttools_libbfio.h \
	vsgpttools_libcerror.h \
	vsgpttools_libclocale.h \
	vsgpttools_libcnotify.h \
	vsgpttools_libfguid.h \
	vsgpttools_libuna.h \
	vsgpttools_libvsgpt.h \
	vsgpttools_output.c vsgpttools_output.h \
	vsgpttools_signal.c vsgpttools_signal.h \
	vsgpttools_unused.h

vsgptinfo_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on vsgptinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vsgptinfo_SOURCES)

