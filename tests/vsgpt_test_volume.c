/*
 * Library volume type test program
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
#include "vsgpt_test_rwlock.h"
#include "vsgpt_test_unused.h"

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )
#include "../libvsgpt/libvsgpt_io_handle.h"
#include "../libvsgpt/libvsgpt_partition_table_header.h"
#include "../libvsgpt/libvsgpt_volume.h"
#endif

#if !defined( LIBVSGPT_HAVE_BFIO )

LIBVSGPT_EXTERN \
int libvsgpt_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_open_file_io_handle(
     libvsgpt_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsgpt_error_t **error );

#endif /* !defined( LIBVSGPT_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vsgpt_test_volume generate verbose output
#define VSGPT_TEST_HANDLE_VERBOSE
 */

/* Creates and opens a source volume
 * Returns 1 if successful or -1 on error
 */
int vsgpt_test_volume_open_source(
     libvsgpt_volume_t **volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "vsgpt_test_volume_open_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libvsgpt_volume_initialize(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	result = libvsgpt_volume_open_file_io_handle(
	          *volume,
	          file_io_handle,
	          LIBVSGPT_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *volume != NULL )
	{
		libvsgpt_volume_free(
		 volume,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source volume
 * Returns 1 if successful or -1 on error
 */
int vsgpt_test_volume_close_source(
     libvsgpt_volume_t **volume,
     libcerror_error_t **error )
{
	static char *function = "vsgpt_test_volume_close_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( libvsgpt_volume_close(
	     *volume,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close volume.",
		 function );

		result = -1;
	}
	if( libvsgpt_volume_free(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free volume.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libvsgpt_volume_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvsgpt_volume_t *volume       = NULL;
	int result                      = 0;

#if defined( HAVE_VSGPT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 4;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_volume_initialize(
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

	volume = (libvsgpt_volume_t *) 0x12345678UL;

	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	volume = NULL;

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSGPT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvsgpt_volume_initialize with malloc failing
		 */
		vsgpt_test_malloc_attempts_before_fail = test_number;

		result = libvsgpt_volume_initialize(
		          &volume,
		          &error );

		if( vsgpt_test_malloc_attempts_before_fail != -1 )
		{
			vsgpt_test_malloc_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvsgpt_volume_free(
				 &volume,
				 NULL );
			}
		}
		else
		{
			VSGPT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSGPT_TEST_ASSERT_IS_NULL(
			 "volume",
			 volume );

			VSGPT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvsgpt_volume_initialize with memset failing
		 */
		vsgpt_test_memset_attempts_before_fail = test_number;

		result = libvsgpt_volume_initialize(
		          &volume,
		          &error );

		if( vsgpt_test_memset_attempts_before_fail != -1 )
		{
			vsgpt_test_memset_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvsgpt_volume_free(
				 &volume,
				 NULL );
			}
		}
		else
		{
			VSGPT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSGPT_TEST_ASSERT_IS_NULL(
			 "volume",
			 volume );

			VSGPT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSGPT_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_volume_free function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsgpt_volume_free(
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

/* Tests the libvsgpt_volume_open function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvsgpt_volume_t *volume = NULL;
	int result                = 0;

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

	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvsgpt_volume_open(
	          volume,
	          narrow_source,
	          LIBVSGPT_OPEN_READ,
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
	result = libvsgpt_volume_open(
	          NULL,
	          narrow_source,
	          LIBVSGPT_OPEN_READ,
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

	result = libvsgpt_volume_open(
	          volume,
	          NULL,
	          LIBVSGPT_OPEN_READ,
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

	result = libvsgpt_volume_open(
	          volume,
	          narrow_source,
	          0,
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

	result = libvsgpt_volume_open(
	          volume,
	          narrow_source,
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

	/* Test open when already opened
	 */
	result = libvsgpt_volume_open(
	          volume,
	          narrow_source,
	          LIBVSGPT_OPEN_READ,
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
	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libvsgpt_volume_open_wide function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvsgpt_volume_t *volume = NULL;
	int result                = 0;

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

	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvsgpt_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSGPT_OPEN_READ,
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
	result = libvsgpt_volume_open_wide(
	          NULL,
	          wide_source,
	          LIBVSGPT_OPEN_READ,
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

	result = libvsgpt_volume_open_wide(
	          volume,
	          NULL,
	          LIBVSGPT_OPEN_READ,
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

	result = libvsgpt_volume_open_wide(
	          volume,
	          wide_source,
	          0,
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

	result = libvsgpt_volume_open_wide(
	          volume,
	          wide_source,
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

	/* Test open when already opened
	 */
	result = libvsgpt_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSGPT_OPEN_READ,
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
	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libvsgpt_volume_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsgpt_volume_t *volume        = NULL;
	size_t string_length             = 0;
	int result                       = 0;

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

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSGPT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvsgpt_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSGPT_OPEN_READ,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open when already opened
	 */
	result = libvsgpt_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSGPT_OPEN_READ,
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
	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_volume_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBVSGPT_OPEN_READ,
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

	result = libvsgpt_volume_open_file_io_handle(
	          volume,
	          NULL,
	          LIBVSGPT_OPEN_READ,
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

	result = libvsgpt_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          0,
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

	result = libvsgpt_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
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

	/* Clean up
	 */
	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_volume_close function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsgpt_volume_close(
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

/* Tests the libvsgpt_volume_open and libvsgpt_volume_close functions
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error  = NULL;
	libvsgpt_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvsgpt_volume_open_wide(
	          volume,
	          source,
	          LIBVSGPT_OPEN_READ,
	          &error );
#else
	result = libvsgpt_volume_open(
	          volume,
	          source,
	          LIBVSGPT_OPEN_READ,
	          &error );
#endif

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_volume_close(
	          volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvsgpt_volume_open_wide(
	          volume,
	          source,
	          LIBVSGPT_OPEN_READ,
	          &error );
#else
	result = libvsgpt_volume_open(
	          volume,
	          source,
	          LIBVSGPT_OPEN_READ,
	          &error );
#endif

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_volume_close(
	          volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

/* Tests the libvsgpt_internal_volume_open_read function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_internal_volume_open_read(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsgpt_volume_t *volume        = NULL;
	size_t string_length             = 0;
	int result                       = 0;

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

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
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
	          LIBBFIO_ACCESS_FLAG_READ,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSGPT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_internal_volume_open_read(
	          (libvsgpt_internal_volume_t *) volume,
	          file_io_handle,
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
	result = libvsgpt_internal_volume_open_read(
	          NULL,
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

	result = libvsgpt_internal_volume_open_read(
	          (libvsgpt_internal_volume_t *) volume,
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
	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_internal_volume_read_partition_table_headers function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_internal_volume_read_partition_table_headers(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsgpt_volume_t *volume        = NULL;
	size_t string_length             = 0;
	int result                       = 0;

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

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
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
	          LIBBFIO_ACCESS_FLAG_READ,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSGPT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libvsgpt_volume_initialize(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_internal_volume_read_partition_table_headers(
	          (libvsgpt_internal_volume_t *) volume,
	          file_io_handle,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvsgpt_partition_table_header_free(
	          &( (libvsgpt_internal_volume_t *) volume )->partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume->partition_table_header",
	 ( (libvsgpt_internal_volume_t *) volume )->partition_table_header );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_internal_volume_read_partition_table_headers(
	          NULL,
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

	( (libvsgpt_internal_volume_t *) volume )->partition_table_header = (libvsgpt_partition_table_header_t *) 0x12345678UL;

	result = libvsgpt_internal_volume_read_partition_table_headers(
	          (libvsgpt_internal_volume_t *) volume,
	          file_io_handle,
	          &error );

	( (libvsgpt_internal_volume_t *) volume )->partition_table_header = NULL;

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsgpt_internal_volume_read_partition_table_headers(
	          (libvsgpt_internal_volume_t *) volume,
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
	result = libvsgpt_volume_free(
	          &volume,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

/* Tests the libvsgpt_volume_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_signal_abort(
     libvsgpt_volume_t *volume )
{
	libcerror_error_t *error        = NULL;
	int result                      = 0;

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )
	libvsgpt_io_handle_t *io_handle = NULL;
#endif

	/* Test regular cases
	 */
	result = libvsgpt_volume_signal_abort(
	          volume,
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
	result = libvsgpt_volume_signal_abort(
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

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

	io_handle = ( (libvsgpt_internal_volume_t *) volume )->io_handle;

	( (libvsgpt_internal_volume_t *) volume )->io_handle = NULL;

	result = libvsgpt_volume_signal_abort(
	          volume,
	          &error );

	( (libvsgpt_internal_volume_t *) volume )->io_handle = io_handle;

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsgpt_volume_get_bytes_per_sector function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_get_bytes_per_sector(
     libvsgpt_volume_t *volume )
{
	libcerror_error_t *error        = NULL;
	uint32_t bytes_per_sector       = 0;
	int result                      = 0;

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )
	libvsgpt_io_handle_t *io_handle = NULL;
#endif

	/* Test regular cases
	 */
	result = libvsgpt_volume_get_bytes_per_sector(
	          volume,
	          &bytes_per_sector,
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
	result = libvsgpt_volume_get_bytes_per_sector(
	          NULL,
	          &bytes_per_sector,
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

	result = libvsgpt_volume_get_bytes_per_sector(
	          volume,
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

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

	io_handle = ( (libvsgpt_internal_volume_t *) volume )->io_handle;

	( (libvsgpt_internal_volume_t *) volume )->io_handle = NULL;

	result = libvsgpt_volume_get_bytes_per_sector(
	          volume,
	          &bytes_per_sector,
	          &error );

	( (libvsgpt_internal_volume_t *) volume )->io_handle = io_handle;

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_volume_get_bytes_per_sector with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_bytes_per_sector(
	          volume,
	          &bytes_per_sector,
	          &error );

	if( vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
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
	/* Test libvsgpt_volume_get_bytes_per_sector with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_bytes_per_sector(
	          volume,
	          &bytes_per_sector,
	          &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsgpt_volume_get_number_of_partitions function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_get_number_of_partitions(
     libvsgpt_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int number_of_partitions = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsgpt_volume_get_number_of_partitions(
	          volume,
	          &number_of_partitions,
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
	result = libvsgpt_volume_get_number_of_partitions(
	          NULL,
	          &number_of_partitions,
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

	result = libvsgpt_volume_get_number_of_partitions(
	          volume,
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

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_volume_get_number_of_partitions with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_number_of_partitions(
	          volume,
	          &number_of_partitions,
	          &error );

	if( vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
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
	/* Test libvsgpt_volume_get_number_of_partitions with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_number_of_partitions(
	          volume,
	          &number_of_partitions,
	          &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsgpt_volume_get_partition_by_index function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_get_partition_by_index(
     libvsgpt_volume_t *volume )
{
	libcerror_error_t *error        = NULL;
	libvsgpt_partition_t *partition = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libvsgpt_volume_get_partition_by_index(
	          volume,
	          0,
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	result = libvsgpt_partition_free(
	          &partition,
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
	result = libvsgpt_volume_get_partition_by_index(
	          NULL,
	          0,
	          &partition,
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

	result = libvsgpt_volume_get_partition_by_index(
	          volume,
	          -1,
	          &partition,
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

	result = libvsgpt_volume_get_partition_by_index(
	          volume,
	          0,
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

	partition = (libvsgpt_partition_t *) 0x12345678UL;

	result = libvsgpt_volume_get_partition_by_index(
	          volume,
	          0,
	          &partition,
	          &error );

	partition = NULL;

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_volume_get_partition_by_index with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_partition_by_index(
	          volume,
	          0,
	          &partition,
	          &error );

	if( vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
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
	/* Test libvsgpt_volume_get_partition_by_index with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_partition_by_index(
	          volume,
	          0,
	          &partition,
	          &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsgpt_volume_has_partition_with_identifier function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_has_partition_with_identifier(
     libvsgpt_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsgpt_volume_has_partition_with_identifier(
	          volume,
	          0,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_volume_has_partition_with_identifier(
	          volume,
	          0xffffffffUL,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_volume_has_partition_with_identifier(
	          NULL,
	          0,
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

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_volume_has_partition_with_identifier with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_volume_has_partition_with_identifier(
	          volume,
	          0,
	          &error );

	if( vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
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
	/* Test libvsgpt_volume_has_partition_with_identifier with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_volume_has_partition_with_identifier(
	          volume,
	          0,
	          &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsgpt_volume_get_partition_by_identifier function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_volume_get_partition_by_identifier(
     libvsgpt_volume_t *volume )
{
	libcerror_error_t *error        = NULL;
	libvsgpt_partition_t *partition = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libvsgpt_volume_get_partition_by_identifier(
	          volume,
	          0,
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_volume_get_partition_by_identifier(
	          volume,
	          0xffffffffUL,
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_volume_get_partition_by_identifier(
	          NULL,
	          0,
	          &partition,
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

	result = libvsgpt_volume_get_partition_by_identifier(
	          volume,
	          0,
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

	partition = (libvsgpt_partition_t *) 0x12345678UL;

	result = libvsgpt_volume_get_partition_by_identifier(
	          volume,
	          0,
	          &partition,
	          &error );

	partition = NULL;

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_volume_get_partition_by_identifier with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_partition_by_identifier(
	          volume,
	          0,
	          &partition,
	          &error );

	if( vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
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
	/* Test libvsgpt_volume_get_partition_by_identifier with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_volume_get_partition_by_identifier(
	          volume,
	          0,
	          &partition,
	          &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsgpt_volume_t *volume        = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

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
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSGPT_TEST_HANDLE_VERBOSE )
	libvsgpt_notify_set_verbose(
	 1 );
	libvsgpt_notify_set_stream(
	 stderr,
	 NULL );
#endif

	VSGPT_TEST_RUN(
	 "libvsgpt_volume_initialize",
	 vsgpt_test_volume_initialize );

	VSGPT_TEST_RUN(
	 "libvsgpt_volume_free",
	 vsgpt_test_volume_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
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

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSGPT_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libvsgpt_check_volume_signature_file_io_handle(
		          file_io_handle,
		          &error );

		VSGPT_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_open",
		 vsgpt_test_volume_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_open_wide",
		 vsgpt_test_volume_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_open_file_io_handle",
		 vsgpt_test_volume_open_file_io_handle,
		 source );

		VSGPT_TEST_RUN(
		 "libvsgpt_volume_close",
		 vsgpt_test_volume_close );

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_open_close",
		 vsgpt_test_volume_open_close,
		 source );

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_internal_volume_open_read",
		 vsgpt_test_internal_volume_open_read,
		 source );

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_internal_volume_read_partition_table_headers",
		 vsgpt_test_internal_volume_read_partition_table_headers,
		 source );

		/* TODO add tests for libvsgpt_internal_volume_read_partition_entries */

		/* TODO add tests for libvsgpt_internal_volume_read_mbr_partition_entries */

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

		/* Initialize volume for tests
		 */
		result = vsgpt_test_volume_open_source(
		          &volume,
		          file_io_handle,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "volume",
		 volume );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_signal_abort",
		 vsgpt_test_volume_signal_abort,
		 volume );

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_get_bytes_per_sector",
		 vsgpt_test_volume_get_bytes_per_sector,
		 volume );

		/* TODO add tests for libvsgpt_volume_get_disk_identifier */

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_get_number_of_partitions",
		 vsgpt_test_volume_get_number_of_partitions,
		 volume );

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_get_partition_by_index",
		 vsgpt_test_volume_get_partition_by_index,
		 volume );

		/* TODO add tests for libvsgpt_internal_volume_get_partition_values_by_identifier */

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_has_partition_with_identifier",
		 vsgpt_test_volume_has_partition_with_identifier,
		 volume );

		VSGPT_TEST_RUN_WITH_ARGS(
		 "libvsgpt_volume_get_partition_by_identifier",
		 vsgpt_test_volume_get_partition_by_identifier,
		 volume );

		/* Clean up
		 */
		result = vsgpt_test_volume_close_source(
		          &volume,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "volume",
		 volume );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
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
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsgpt_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

