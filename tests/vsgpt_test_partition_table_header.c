/*
 * Library partition_table_header type test program
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
#include <byte_stream.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vsgpt_test_functions.h"
#include "vsgpt_test_libcerror.h"
#include "vsgpt_test_libvsgpt.h"
#include "vsgpt_test_macros.h"
#include "vsgpt_test_memory.h"
#include "vsgpt_test_unused.h"

#include "../libvsgpt/libvsgpt_partition_table_header.h"

uint8_t vsgpt_test_partition_table_header_data1[ 512 ] = {
	0x45, 0x46, 0x49, 0x20, 0x50, 0x41, 0x52, 0x54, 0x00, 0x00, 0x01, 0x00, 0x5c, 0x00, 0x00, 0x00,
	0x9c, 0xe7, 0xd7, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xde, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3e, 0xcf, 0x2d, 0x74, 0x22, 0x7a, 0x46,
	0xbd, 0x48, 0xb6, 0xf3, 0x87, 0x6f, 0xde, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x4b, 0x1a, 0x63, 0x1a, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t vsgpt_test_partition_table_header_error_data1[ 512 ] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0x00, 0x5c, 0x00, 0x00, 0x00,
	0x9c, 0xe7, 0xd7, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xde, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3e, 0xcf, 0x2d, 0x74, 0x22, 0x7a, 0x46,
	0xbd, 0x48, 0xb6, 0xf3, 0x87, 0x6f, 0xde, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x4b, 0x1a, 0x63, 0x1a, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

/* Tests the libvsgpt_partition_table_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_table_header_initialize(
     void )
{
	libcerror_error_t *error                                  = NULL;
	libvsgpt_partition_table_header_t *partition_table_header = NULL;
	int result                                                = 0;

#if defined( HAVE_VSGPT_TEST_MEMORY )
	int number_of_malloc_fail_tests                           = 1;
	int number_of_memset_fail_tests                           = 1;
	int test_number                                           = 0;
#endif

	/* Test regular cases
	 */
	result = libvsgpt_partition_table_header_initialize(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_table_header",
	 partition_table_header );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_partition_table_header_free(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_table_header",
	 partition_table_header );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_partition_table_header_initialize(
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

	partition_table_header = (libvsgpt_partition_table_header_t *) 0x12345678UL;

	result = libvsgpt_partition_table_header_initialize(
	          &partition_table_header,
	          &error );

	partition_table_header = NULL;

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
		/* Test libvsgpt_partition_table_header_initialize with malloc failing
		 */
		vsgpt_test_malloc_attempts_before_fail = test_number;

		result = libvsgpt_partition_table_header_initialize(
		          &partition_table_header,
		          &error );

		if( vsgpt_test_malloc_attempts_before_fail != -1 )
		{
			vsgpt_test_malloc_attempts_before_fail = -1;

			if( partition_table_header != NULL )
			{
				libvsgpt_partition_table_header_free(
				 &partition_table_header,
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
			 "partition_table_header",
			 partition_table_header );

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
		/* Test libvsgpt_partition_table_header_initialize with memset failing
		 */
		vsgpt_test_memset_attempts_before_fail = test_number;

		result = libvsgpt_partition_table_header_initialize(
		          &partition_table_header,
		          &error );

		if( vsgpt_test_memset_attempts_before_fail != -1 )
		{
			vsgpt_test_memset_attempts_before_fail = -1;

			if( partition_table_header != NULL )
			{
				libvsgpt_partition_table_header_free(
				 &partition_table_header,
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
			 "partition_table_header",
			 partition_table_header );

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
	if( partition_table_header != NULL )
	{
		libvsgpt_partition_table_header_free(
		 &partition_table_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_table_header_free function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_table_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsgpt_partition_table_header_free(
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

/* Tests the libvsgpt_partition_table_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_table_header_read_data(
     void )
{
	libcerror_error_t *error                                  = NULL;
	libvsgpt_partition_table_header_t *partition_table_header = NULL;
	int result                                                = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_table_header_initialize(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_table_header",
	 partition_table_header );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
	          512,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular case where checksum is invalid
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( vsgpt_test_partition_table_header_data1[ 16 ] ),
	 0xffffffffUL );

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
	          512,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 &( vsgpt_test_partition_table_header_data1[ 16 ] ),
	 0x1cd7e79cUL );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_partition_table_header_read_data(
	          NULL,
	          vsgpt_test_partition_table_header_data1,
	          512,
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

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          NULL,
	          512,
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

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
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

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
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

#if defined( HAVE_VSGPT_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	/* Test libvsgpt_partition_table_header_initialize with memcpy failing
	 */
	vsgpt_test_memcpy_attempts_before_fail = 0;

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
	          512,
	          &error );

	if( vsgpt_test_memcpy_attempts_before_fail != -1 )
	{
		vsgpt_test_memcpy_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSGPT_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED ) */

	/* Test error case where header size is invalid
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( vsgpt_test_partition_table_header_data1[ 12 ] ),
	 0xffffffffUL );

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
	          512,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 &( vsgpt_test_partition_table_header_data1[ 12 ] ),
	 0x0000005cUL );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case where major and minor versions are invalid
	 */
/* TODO
	byte_stream_copy_from_uint32_little_endian(
	 &( vsgpt_test_partition_table_header_data1[ 8 ] ),
	 0xffffffffUL );

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
	          512,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 &( vsgpt_test_partition_table_header_data1[ 8 ] ),
	 0x00010000UL );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );
*/

	/* Clean up
	 */
	result = libvsgpt_partition_table_header_free(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_table_header",
	 partition_table_header );

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
	if( partition_table_header != NULL )
	{
		libvsgpt_partition_table_header_free(
		 &partition_table_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_table_header_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_table_header_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle                          = NULL;
	libcerror_error_t *error                                  = NULL;
	libvsgpt_partition_table_header_t *partition_table_header = NULL;
	int result                                                = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_table_header_initialize(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_table_header",
	 partition_table_header );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          vsgpt_test_partition_table_header_data1,
	          512,
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

	/* Test regular cases
	 */
	result = libvsgpt_partition_table_header_read_file_io_handle(
	          partition_table_header,
	          file_io_handle,
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
	result = libvsgpt_partition_table_header_read_file_io_handle(
	          NULL,
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

	result = libvsgpt_partition_table_header_read_file_io_handle(
	          partition_table_header,
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

	/* Clean up file IO handle
	 */
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

	/* Test data too small
	 */
	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          vsgpt_test_partition_table_header_data1,
	          8,
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

	result = libvsgpt_partition_table_header_read_file_io_handle(
	          partition_table_header,
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

	/* Test data invalid
	 */
	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          vsgpt_test_partition_table_header_error_data1,
	          512,
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

	result = libvsgpt_partition_table_header_read_file_io_handle(
	          partition_table_header,
	          file_io_handle,
	          0,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
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

	/* Clean up
	 */
	result = libvsgpt_partition_table_header_free(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_table_header",
	 partition_table_header );

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
	if( partition_table_header != NULL )
	{
		libvsgpt_partition_table_header_free(
		 &partition_table_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_table_header_get_disk_identifier function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_table_header_get_disk_identifier(
     libvsgpt_partition_table_header_t *partition_table_header )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsgpt_partition_table_header_get_disk_identifier(
	          partition_table_header,
	          guid_data,
	          16,
	          &error );

	VSGPT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_partition_table_header_get_disk_identifier(
	          NULL,
	          guid_data,
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

	result = libvsgpt_partition_table_header_get_disk_identifier(
	          partition_table_header,
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

	result = libvsgpt_partition_table_header_get_disk_identifier(
	          partition_table_header,
	          guid_data,
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

	result = libvsgpt_partition_table_header_get_disk_identifier(
	          partition_table_header,
	          guid_data,
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

#if defined( HAVE_VSGPT_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	/* Test libvsgpt_partition_table_header_get_disk_identifier with memcpy failing
	 */
	vsgpt_test_memcpy_attempts_before_fail = 0;

	result = libvsgpt_partition_table_header_get_disk_identifier(
	          partition_table_header,
	          guid_data,
	          16,
	          &error );

	if( vsgpt_test_memcpy_attempts_before_fail != -1 )
	{
		vsgpt_test_memcpy_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSGPT_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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
	libcerror_error_t *error                                  = NULL;
	int result                                                = 0;

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )
	libvsgpt_partition_table_header_t *partition_table_header = NULL;
#endif

	VSGPT_TEST_UNREFERENCED_PARAMETER( argc )
	VSGPT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_table_header_initialize",
	 vsgpt_test_partition_table_header_initialize );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_table_header_free",
	 vsgpt_test_partition_table_header_free );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_table_header_read_data",
	 vsgpt_test_partition_table_header_read_data );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_table_header_read_file_io_handle",
	 vsgpt_test_partition_table_header_read_file_io_handle );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize partition_table_header for tests
	 */
	result = libvsgpt_partition_table_header_initialize(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_table_header",
	 partition_table_header );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          vsgpt_test_partition_table_header_data1,
	          512,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_partition_table_header_get_disk_identifier",
	 vsgpt_test_partition_table_header_get_disk_identifier,
	 partition_table_header );

	/* Clean up
	 */
	result = libvsgpt_partition_table_header_free(
	          &partition_table_header,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_table_header",
	 partition_table_header );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )
	if( partition_table_header != NULL )
	{
		libvsgpt_partition_table_header_free(
		 &partition_table_header,
		 NULL );
	}
#endif
	return( EXIT_FAILURE );
}

