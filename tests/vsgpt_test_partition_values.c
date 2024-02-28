/*
 * Library partition_values type test program
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

#include "../libvsgpt/libvsgpt_partition_values.h"

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

/* Tests the libvsgpt_partition_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_initialize(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	int result                                    = 0;

#if defined( HAVE_VSGPT_TEST_MEMORY )
	int number_of_malloc_fail_tests               = 1;
	int number_of_memset_fail_tests               = 1;
	int test_number                               = 0;
#endif

	/* Test regular cases
	 */
	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_partition_values_free(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_partition_values_initialize(
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

	partition_values = (libvsgpt_partition_values_t *) 0x12345678UL;

	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	partition_values = NULL;

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
		/* Test libvsgpt_partition_values_initialize with malloc failing
		 */
		vsgpt_test_malloc_attempts_before_fail = test_number;

		result = libvsgpt_partition_values_initialize(
		          &partition_values,
		          &error );

		if( vsgpt_test_malloc_attempts_before_fail != -1 )
		{
			vsgpt_test_malloc_attempts_before_fail = -1;

			if( partition_values != NULL )
			{
				libvsgpt_partition_values_free(
				 &partition_values,
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
			 "partition_values",
			 partition_values );

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
		/* Test libvsgpt_partition_values_initialize with memset failing
		 */
		vsgpt_test_memset_attempts_before_fail = test_number;

		result = libvsgpt_partition_values_initialize(
		          &partition_values,
		          &error );

		if( vsgpt_test_memset_attempts_before_fail != -1 )
		{
			vsgpt_test_memset_attempts_before_fail = -1;

			if( partition_values != NULL )
			{
				libvsgpt_partition_values_free(
				 &partition_values,
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
			 "partition_values",
			 partition_values );

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
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_values_free function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsgpt_partition_values_free(
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

/* Tests the libvsgpt_partition_values_get_entry_index function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_get_entry_index(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	uint32_t entry_index                          = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_values_get_entry_index(
	          partition_values,
	          &entry_index,
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
	result = libvsgpt_partition_values_get_entry_index(
	          NULL,
	          &entry_index,
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

	result = libvsgpt_partition_values_get_entry_index(
	          partition_values,
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
	result = libvsgpt_partition_values_free(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_values_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_get_identifier(
     void )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_values_get_identifier(
	          partition_values,
	          guid_data,
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
	result = libvsgpt_partition_values_get_identifier(
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

	result = libvsgpt_partition_values_get_identifier(
	          partition_values,
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

	result = libvsgpt_partition_values_get_identifier(
	          partition_values,
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

	result = libvsgpt_partition_values_get_identifier(
	          partition_values,
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

	/* Test libvsgpt_partition_values_get_identifier with memcpy failing
	 */
	vsgpt_test_memcpy_attempts_before_fail = 0;

	result = libvsgpt_partition_values_get_identifier(
	          partition_values,
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

	/* Clean up
	 */
	result = libvsgpt_partition_values_free(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_values_get_type_identifier function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_get_type_identifier(
     void )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_values_get_type_identifier(
	          partition_values,
	          guid_data,
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
	result = libvsgpt_partition_values_get_type_identifier(
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

	result = libvsgpt_partition_values_get_type_identifier(
	          partition_values,
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

	result = libvsgpt_partition_values_get_type_identifier(
	          partition_values,
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

	result = libvsgpt_partition_values_get_type_identifier(
	          partition_values,
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

	/* Test libvsgpt_partition_values_get_type_identifier with memcpy failing
	 */
	vsgpt_test_memcpy_attempts_before_fail = 0;

	result = libvsgpt_partition_values_get_type_identifier(
	          partition_values,
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

	/* Clean up
	 */
	result = libvsgpt_partition_values_free(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_values_get_type function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_get_type(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	uint8_t type                                  = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_values_get_type(
	          partition_values,
	          &type,
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
	result = libvsgpt_partition_values_get_type(
	          NULL,
	          &type,
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

	result = libvsgpt_partition_values_get_type(
	          partition_values,
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
	result = libvsgpt_partition_values_free(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_values_get_offset function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_get_offset(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	off64_t offset                                = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_values_get_offset(
	          partition_values,
	          &offset,
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
	result = libvsgpt_partition_values_get_offset(
	          NULL,
	          &offset,
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

	result = libvsgpt_partition_values_get_offset(
	          partition_values,
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
	result = libvsgpt_partition_values_free(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_values_get_size function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_values_get_size(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	size64_t size                                 = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsgpt_partition_values_initialize(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_values_get_size(
	          partition_values,
	          &size,
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
	result = libvsgpt_partition_values_get_size(
	          NULL,
	          &size,
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

	result = libvsgpt_partition_values_get_size(
	          partition_values,
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
	result = libvsgpt_partition_values_free(
	          &partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
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
	 "libvsgpt_partition_values_initialize",
	 vsgpt_test_partition_values_initialize );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_values_free",
	 vsgpt_test_partition_values_free );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_values_get_entry_index",
	 vsgpt_test_partition_values_get_entry_index );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_values_get_identifier",
	 vsgpt_test_partition_values_get_identifier );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_values_get_type_identifier",
	 vsgpt_test_partition_values_get_type_identifier );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_values_get_type",
	 vsgpt_test_partition_values_get_type );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_values_get_offset",
	 vsgpt_test_partition_values_get_offset );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_values_get_size",
	 vsgpt_test_partition_values_get_size );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */
}

