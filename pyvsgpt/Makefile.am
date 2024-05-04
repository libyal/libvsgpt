if HAVE_PYTHON
AM_CFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBVSGPT_DLL_IMPORT@

pyexec_LTLIBRARIES = pyvsgpt.la

pyvsgpt_la_SOURCES = \
	pyvsgpt.c pyvsgpt.h \
	pyvsgpt_error.c pyvsgpt_error.h \
	pyvsgpt_file_object_io_handle.c pyvsgpt_file_object_io_handle.h \
	pyvsgpt_guid.c pyvsgpt_guid.h \
	pyvsgpt_integer.c pyvsgpt_integer.h \
	pyvsgpt_libbfio.h \
	pyvsgpt_libcerror.h \
	pyvsgpt_libclocale.h \
	pyvsgpt_libfguid.h \
	pyvsgpt_libvsgpt.h \
	pyvsgpt_partition.c pyvsgpt_partition.h \
	pyvsgpt_partitions.c pyvsgpt_partitions.h \
	pyvsgpt_python.h \
	pyvsgpt_unused.h \
	pyvsgpt_volume.c pyvsgpt_volume.h

pyvsgpt_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pyvsgpt_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyvsgpt_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

DISTCLEANFILES = \
	Makefile \
	Makefile.in

