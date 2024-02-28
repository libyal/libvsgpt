/*
 * Library support functions test program
 *
 * Copyright (C) 2019-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vsgpt_test_functions.h"
#include "vsgpt_test_getopt.h"
#include "vsgpt_test_libbfio.h"
#include "vsgpt_test_libcerror.h"
#include "vsgpt_test_libvsgpt.h"
#include "vsgpt_test_macros.h"
#include "vsgpt_test_memory.h"
#include "vsgpt_test_unused.h"

#if !defined( LIBVSGPT_HAVE_BFIO )

LIBVSGPT_EXTERN \
int libvsgpt_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#endif /* !defined( LIBVSGPT_HAVE_BFIO ) */

/* Tests the libvsgpt_get_version function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libvsgpt_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBVSGPT_VERSION_STRING,
	          9 );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libvsgpt_get_access_flags_read function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_get_access_flags_read(
     void )
{
	int access_flags = 0;

	access_flags = libvsgpt_get_access_flags_read();

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "access_flags",
	 access_flags,
	 LIBVSGPT_ACCESS_FLAG_READ );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libvsgpt_get_access_flags_read_write function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_get_access_flags_read_write(
     void )
{
	int access_flags = 0;

	access_flags = libvsgpt_get_access_flags_read_write();

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "access_flags",
	 access_flags,
	 ( LIBVSGPT_ACCESS_FLAG_READ | LIBVSGPT_ACCESS_FLAG_WRITE ) );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libvsgpt_get_access_flags_write function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_get_access_flags_write(
     void )
{
	int access_flags = 0;

	access_flags = libvsgpt_get_access_flags_write();

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "access_flags",
	 access_flags,
	 LIBVSGPT_ACCESS_FLAG_WRITE );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libvsgpt_get_codepage function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_get_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = libvsgpt_get_codepage(
	          &codepage,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_get_codepage(
	          NULL,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsgpt_set_codepage function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_set_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libvsgpt_set_codepage(
	          0,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_set_codepage(
	          -1,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsgpt_check_volume_signature function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_check_volume_signature(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	if( source != NULL )
	{
		/* Initialize test
		 */
		result = vsgpt_test_get_narrow_source(
		          source,
		          narrow_source,
		          256,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test check volume signature
		 */
		result = libvsgpt_check_volume_signature(
		          narrow_source,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libvsgpt_check_volume_signature(
	          NULL,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsgpt_check_volume_signature(
	          "",
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( source != NULL )
	{
#if defined( HAVE_VSGPT_TEST_MEMORY )

		/* Test libvsgpt_check_volume_signature with malloc failing in libbfio_file_initialize
		 */
		vsgpt_test_malloc_attempts_before_fail = 0;

		result = libvsgpt_check_volume_signature(
		          narrow_source,
		          &error );

		if( vsgpt_test_malloc_attempts_before_fail != -1 )
		{
			vsgpt_test_malloc_attempts_before_fail = -1;
		}
		else
		{
			VSGPT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSGPT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
#endif /* defined( HAVE_VSGPT_TEST_MEMORY ) */
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libvsgpt_check_volume_signature_wide function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_check_volume_signature_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	if( source != NULL )
	{
		/* Initialize test
		 */
		result = vsgpt_test_get_wide_source(
		          source,
		          wide_source,
		          256,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test check volume signature
		 */
		result = libvsgpt_check_volume_signature_wide(
		          wide_source,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libvsgpt_check_volume_signature_wide(
	          NULL,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsgpt_check_volume_signature_wide(
	          L"",
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( source != NULL )
	{
#if defined( HAVE_VSGPT_TEST_MEMORY )

		/* Test libvsgpt_check_volume_signature_wide with malloc failing in libbfio_file_initialize
		 */
		vsgpt_test_malloc_attempts_before_fail = 0;

		result = libvsgpt_check_volume_signature_wide(
		          wide_source,
		          &error );

		if( vsgpt_test_malloc_attempts_before_fail != -1 )
		{
			vsgpt_test_malloc_attempts_before_fail = -1;
		}
		else
		{
			VSGPT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSGPT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
#endif /* defined( HAVE_VSGPT_TEST_MEMORY ) */
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libvsgpt_check_volume_signature_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_check_volume_signature_file_io_handle(
     const system_character_t *source )
{
	uint8_t empty_block[ 8192 ];

	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	void *memset_result              = NULL;
	size_t source_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	memset_result = memory_set(
	                 empty_block,
	                 0,
	                 sizeof( uint8_t ) * 8192 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "memset_result",
	 memset_result );

	if( source != NULL )
	{
		/* Initialize test
		 */
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "file_io_handle",
		 file_io_handle );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		source_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          source_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          source_length,
		          &error );
#endif
		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_open(
		          file_io_handle,
		          LIBBFIO_OPEN_READ,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test check volume signature
		 */
		result = libvsgpt_check_volume_signature_file_io_handle(
		          file_io_handle,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libvsgpt_check_volume_signature_file_io_handle(
	          NULL,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	if( source != NULL )
	{
		result = libbfio_handle_close(
		          file_io_handle,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "file_io_handle",
		 file_io_handle );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test check volume signature with data too small
	 */
	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          empty_block,
	          sizeof( uint8_t ) * 1,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_check_volume_signature_file_io_handle(
	          file_io_handle,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = vsgpt_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test check volume signature with empty block
	 */
	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          empty_block,
	          sizeof( uint8_t ) * 8192,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_check_volume_signature_file_io_handle(
	          file_io_handle,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = vsgpt_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	system_character_t *source = NULL;
	system_integer_t option    = 0;

	while( ( option = vsgpt_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
	VSGPT_TEST_RUN(
	 "libvsgpt_get_version",
	 vsgpt_test_get_version );

	VSGPT_TEST_RUN(
	 "libvsgpt_get_access_flags_read",
	 vsgpt_test_get_access_flags_read );

	VSGPT_TEST_RUN(
	 "libvsgpt_get_access_flags_read_write",
	 vsgpt_test_get_access_flags_read_write );

	VSGPT_TEST_RUN(
	 "libvsgpt_get_access_flags_write",
	 vsgpt_test_get_access_flags_write );

	VSGPT_TEST_RUN(
	 "libvsgpt_get_codepage",
	 vsgpt_test_get_codepage );

	VSGPT_TEST_RUN(
	 "libvsgpt_set_codepage",
	 vsgpt_test_set_codepage );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_check_volume_signature",
	 vsgpt_test_check_volume_signature,
	 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_check_volume_signature_wide",
	 vsgpt_test_check_volume_signature_wide,
	 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_check_volume_signature_file_io_handle",
	 vsgpt_test_check_volume_signature_file_io_handle,
	 source );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

