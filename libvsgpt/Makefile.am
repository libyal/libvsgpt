AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBVSGPT_DLL_EXPORT@

lib_LTLIBRARIES = libvsgpt.la

libvsgpt_la_SOURCES = \
	libvsgpt.c \
	libvsgpt_boot_record.c libvsgpt_boot_record.h \
	libvsgpt_checksum.c libvsgpt_checksum.h \
	libvsgpt_chs_address.c libvsgpt_chs_address.h \
	libvsgpt_debug.c libvsgpt_debug.h \
	libvsgpt_definitions.h \
	libvsgpt_error.c libvsgpt_error.h \
	libvsgpt_extern.h \
	libvsgpt_io_handle.c libvsgpt_io_handle.h \
	libvsgpt_libbfio.h \
	libvsgpt_libcdata.h \
	libvsgpt_libcerror.h \
	libvsgpt_libclocale.h \
	libvsgpt_libcnotify.h \
	libvsgpt_libcthreads.h \
	libvsgpt_libfcache.h \
	libvsgpt_libfdata.h \
	libvsgpt_libfguid.h \
	libvsgpt_libuna.h \
	libvsgpt_mbr_partition_entry.c libvsgpt_mbr_partition_entry.h \
	libvsgpt_mbr_partition_type.c libvsgpt_mbr_partition_type.h \
	libvsgpt_notify.c libvsgpt_notify.h \
	libvsgpt_partition.c libvsgpt_partition.h \
	libvsgpt_partition_entry.c libvsgpt_partition_entry.h \
	libvsgpt_partition_table_header.c libvsgpt_partition_table_header.h \
	libvsgpt_partition_type_identifier.c libvsgpt_partition_type_identifier.h \
	libvsgpt_partition_values.c libvsgpt_partition_values.h \
	libvsgpt_section_values.c libvsgpt_section_values.h \
	libvsgpt_sector_data.c libvsgpt_sector_data.h \
	libvsgpt_support.c libvsgpt_support.h \
	libvsgpt_types.h \
	libvsgpt_unused.h \
	libvsgpt_volume.c libvsgpt_volume.h \
	vsgpt_boot_record.h \
	vsgpt_mbr_partition_entry.h \
	vsgpt_partition_entry.h \
	vsgpt_partition_table.h

libvsgpt_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@PTHREAD_LIBADD@

libvsgpt_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libvsgpt_definitions.h.in \
	libvsgpt.rc \
	libvsgpt.rc.in

DISTCLEANFILES = \
	libvsgpt_definitions.h \
	libvsgpt.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libvsgpt ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libvsgpt_la_SOURCES)

