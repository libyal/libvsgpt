/*
 * Library mbr_partition_entry type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vsgpt_test_libcerror.h"
#include "vsgpt_test_libvsgpt.h"
#include "vsgpt_test_macros.h"
#include "vsgpt_test_memory.h"
#include "vsgpt_test_unused.h"

#include "../libvsgpt/libvsgpt_mbr_partition_entry.h"

uint8_t vsgpt_test_mbr_partition_entry_data1[ 16 ] = {
	0x80, 0x20, 0x21, 0x00, 0x07, 0xdf, 0x13, 0x0c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x03, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

/* Tests the libvsgpt_mbr_partition_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_mbr_partition_entry_initialize(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvsgpt_mbr_partition_entry_t *mbr_partition_entry = NULL;
	int result                                  = 0;

#if defined( HAVE_VSGPT_TEST_MEMORY )
	int number_of_malloc_fail_tests             = 1;
	int number_of_memset_fail_tests             = 1;
	int test_number                             = 0;
#endif

	/* Test regular cases
	 */
	result = libvsgpt_mbr_partition_entry_initialize(
	          &mbr_partition_entry,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "mbr_partition_entry",
	 mbr_partition_entry );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_mbr_partition_entry_free(
	          &mbr_partition_entry,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "mbr_partition_entry",
	 mbr_partition_entry );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_mbr_partition_entry_initialize(
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

	mbr_partition_entry = (libvsgpt_mbr_partition_entry_t *) 0x12345678UL;

	result = libvsgpt_mbr_partition_entry_initialize(
	          &mbr_partition_entry,
	          &error );

	mbr_partition_entry = NULL;

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
		/* Test libvsgpt_mbr_partition_entry_initialize with malloc failing
		 */
		vsgpt_test_malloc_attempts_before_fail = test_number;

		result = libvsgpt_mbr_partition_entry_initialize(
		          &mbr_partition_entry,
		          &error );

		if( vsgpt_test_malloc_attempts_before_fail != -1 )
		{
			vsgpt_test_malloc_attempts_before_fail = -1;

			if( mbr_partition_entry != NULL )
			{
				libvsgpt_mbr_partition_entry_free(
				 &mbr_partition_entry,
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
			 "mbr_partition_entry",
			 mbr_partition_entry );

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
		/* Test libvsgpt_mbr_partition_entry_initialize with memset failing
		 */
		vsgpt_test_memset_attempts_before_fail = test_number;

		result = libvsgpt_mbr_partition_entry_initialize(
		          &mbr_partition_entry,
		          &error );

		if( vsgpt_test_memset_attempts_before_fail != -1 )
		{
			vsgpt_test_memset_attempts_before_fail = -1;

			if( mbr_partition_entry != NULL )
			{
				libvsgpt_mbr_partition_entry_free(
				 &mbr_partition_entry,
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
			 "mbr_partition_entry",
			 mbr_partition_entry );

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
	if( mbr_partition_entry != NULL )
	{
		libvsgpt_mbr_partition_entry_free(
		 &mbr_partition_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_mbr_partition_entry_free function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_mbr_partition_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsgpt_mbr_partition_entry_free(
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

/* Tests the libvsgpt_mbr_partition_entry_read_data function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_mbr_partition_entry_read_data(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvsgpt_mbr_partition_entry_t *mbr_partition_entry = NULL;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libvsgpt_mbr_partition_entry_initialize(
	          &mbr_partition_entry,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "mbr_partition_entry",
	 mbr_partition_entry );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_mbr_partition_entry_read_data(
	          mbr_partition_entry,
	          vsgpt_test_mbr_partition_entry_data1,
	          16,
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
	result = libvsgpt_mbr_partition_entry_read_data(
	          NULL,
	          vsgpt_test_mbr_partition_entry_data1,
	          16,
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

	result = libvsgpt_mbr_partition_entry_read_data(
	          mbr_partition_entry,
	          NULL,
	          16,
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

	result = libvsgpt_mbr_partition_entry_read_data(
	          mbr_partition_entry,
	          vsgpt_test_mbr_partition_entry_data1,
	          (size_t) SSIZE_MAX + 1,
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

	result = libvsgpt_mbr_partition_entry_read_data(
	          mbr_partition_entry,
	          vsgpt_test_mbr_partition_entry_data1,
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

	/* Clean up
	 */
	result = libvsgpt_mbr_partition_entry_free(
	          &mbr_partition_entry,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "mbr_partition_entry",
	 mbr_partition_entry );

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
	if( mbr_partition_entry != NULL )
	{
		libvsgpt_mbr_partition_entry_free(
		 &mbr_partition_entry,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc VSGPT_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] VSGPT_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc VSGPT_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] VSGPT_TEST_ATTRIBUTE_UNUSED )
#endif
{
	VSGPT_TEST_UNREFERENCED_PARAMETER( argc )
	VSGPT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

	VSGPT_TEST_RUN(
	 "libvsgpt_mbr_partition_entry_initialize",
	 vsgpt_test_mbr_partition_entry_initialize );

	VSGPT_TEST_RUN(
	 "libvsgpt_mbr_partition_entry_free",
	 vsgpt_test_mbr_partition_entry_free );

	VSGPT_TEST_RUN(
	 "libvsgpt_mbr_partition_entry_read_data",
	 vsgpt_test_mbr_partition_entry_read_data );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

