# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSGPT_DLL_IMPORT@

am_pyvsgpt_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
	pyvsgpt.c pyvsgpt.h \
	pyvsgpt_error.c pyvsgpt_error.h \
	pyvsgpt_file_object_io_handle.c pyvsgpt_file_object_io_handle.h \
	pyvsgpt_integer.c pyvsgpt_integer.h \
	pyvsgpt_libbfio.h \
	pyvsgpt_libcerror.h \
	pyvsgpt_libclocale.h \
	pyvsgpt_libvsgpt.h \
	pyvsgpt_partition.c pyvsgpt_partition.h \
	pyvsgpt_partitions.c pyvsgpt_partitions.h \
	pyvsgpt_python.h \
	pyvsgpt_unused.h \
	pyvsgpt_volume.c pyvsgpt_volume.h

pyexec_LTLIBRARIES = pyvsgpt.la

nodist_pyvsgpt_la_SOURCES = $(BUILT_SOURCES)

pyvsgpt_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyvsgpt_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pyvsgpt_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyvsgpt/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyvsgpt*.[ch]

distclean: clean
	/bin/rm -f Makefile

