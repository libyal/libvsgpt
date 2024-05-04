AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBVSGPT_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSGPT = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_vsgptinfo.sh \
	$(TESTS_PYVSGPT)

check_SCRIPTS = \
	pyvsgpt_test_partition.py \
	pyvsgpt_test_support.py \
	pyvsgpt_test_volume.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh \
	test_vsgptinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vsgpt_test_boot_record \
	vsgpt_test_checksum \
	vsgpt_test_chs_address \
	vsgpt_test_error \
	vsgpt_test_io_handle \
	vsgpt_test_mbr_partition_entry \
	vsgpt_test_mbr_partition_type \
	vsgpt_test_notify \
	vsgpt_test_partition \
	vsgpt_test_partition_entry \
	vsgpt_test_partition_table_header \
	vsgpt_test_partition_type_identifier \
	vsgpt_test_partition_values \
	vsgpt_test_section_values \
	vsgpt_test_sector_data \
	vsgpt_test_support \
	vsgpt_test_tools_info_handle \
	vsgpt_test_tools_output \
	vsgpt_test_tools_signal \
	vsgpt_test_volume

vsgpt_test_boot_record_SOURCES = \
	vsgpt_test_boot_record.c \
	vsgpt_test_functions.c vsgpt_test_functions.h \
	vsgpt_test_libbfio.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_unused.h

vsgpt_test_boot_record_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_checksum_SOURCES = \
	vsgpt_test_checksum.c \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_unused.h

vsgpt_test_checksum_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_chs_address_SOURCES = \
	vsgpt_test_chs_address.c \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_unused.h

vsgpt_test_chs_address_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_error_SOURCES = \
	vsgpt_test_error.c \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_unused.h

vsgpt_test_error_LDADD = \
	../libvsgpt/libvsgpt.la

vsgpt_test_io_handle_SOURCES = \
	vsgpt_test_io_handle.c \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_unused.h

vsgpt_test_io_handle_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_mbr_partition_entry_SOURCES = \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_mbr_partition_entry.c \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_unused.h

vsgpt_test_mbr_partition_entry_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_mbr_partition_type_SOURCES = \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_mbr_partition_type.c \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_unused.h

vsgpt_test_mbr_partition_type_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_notify_SOURCES = \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_notify.c \
	vsgpt_test_unused.h

vsgpt_test_notify_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_partition_SOURCES = \
	vsgpt_test_functions.c vsgpt_test_functions.h \
	vsgpt_test_libbfio.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_partition.c \
	vsgpt_test_rwlock.c vsgpt_test_rwlock.h \
	vsgpt_test_unused.h

vsgpt_test_partition_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

vsgpt_test_partition_entry_SOURCES = \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_partition_entry.c \
	vsgpt_test_unused.h

vsgpt_test_partition_entry_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_partition_table_header_SOURCES = \
	vsgpt_test_functions.c vsgpt_test_functions.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_partition_table_header.c \
	vsgpt_test_unused.h

vsgpt_test_partition_table_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_partition_type_identifier_SOURCES = \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_partition_type_identifier.c \
	vsgpt_test_unused.h

vsgpt_test_partition_type_identifier_LDADD = \
	../libvsgpt/libvsgpt.la

vsgpt_test_partition_values_SOURCES = \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_partition_values.c \
	vsgpt_test_unused.h

vsgpt_test_partition_values_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_section_values_SOURCES = \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_section_values.c \
	vsgpt_test_unused.h

vsgpt_test_section_values_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_sector_data_SOURCES = \
	vsgpt_test_functions.c vsgpt_test_functions.h \
	vsgpt_test_libbfio.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_sector_data.c \
	vsgpt_test_unused.h

vsgpt_test_sector_data_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_support_SOURCES = \
	vsgpt_test_functions.c vsgpt_test_functions.h \
	vsgpt_test_getopt.c vsgpt_test_getopt.h \
	vsgpt_test_libbfio.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_libclocale.h \
	vsgpt_test_libcnotify.h \
	vsgpt_test_libuna.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_support.c \
	vsgpt_test_unused.h

vsgpt_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_tools_info_handle_SOURCES = \
	../vsgpttools/info_handle.c ../vsgpttools/info_handle.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_tools_info_handle.c \
	vsgpt_test_unused.h

vsgpt_test_tools_info_handle_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_tools_output_SOURCES = \
	../vsgpttools/vsgpttools_output.c ../vsgpttools/vsgpttools_output.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_macros.h \
	vsgpt_test_tools_output.c \
	vsgpt_test_unused.h

vsgpt_test_tools_output_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_tools_signal_SOURCES = \
	../vsgpttools/vsgpttools_signal.c ../vsgpttools/vsgpttools_signal.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_macros.h \
	vsgpt_test_tools_signal.c \
	vsgpt_test_unused.h

vsgpt_test_tools_signal_LDADD = \
	../libvsgpt/libvsgpt.la \
	@LIBCERROR_LIBADD@

vsgpt_test_volume_SOURCES = \
	vsgpt_test_functions.c vsgpt_test_functions.h \
	vsgpt_test_getopt.c vsgpt_test_getopt.h \
	vsgpt_test_libbfio.h \
	vsgpt_test_libcerror.h \
	vsgpt_test_libclocale.h \
	vsgpt_test_libcnotify.h \
	vsgpt_test_libuna.h \
	vsgpt_test_libvsgpt.h \
	vsgpt_test_macros.h \
	vsgpt_test_memory.c vsgpt_test_memory.h \
	vsgpt_test_rwlock.c vsgpt_test_rwlock.h \
	vsgpt_test_unused.h \
	vsgpt_test_volume.c

vsgpt_test_volume_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsgpt/libvsgpt.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

DISTCLEANFILES = \
	Makefile \
	Makefile.in \
	notify_stream.log

