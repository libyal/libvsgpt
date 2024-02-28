/*
 * Library partition type test program
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

#include "vsgpt_test_functions.h"
#include "vsgpt_test_libbfio.h"
#include "vsgpt_test_libcerror.h"
#include "vsgpt_test_libvsgpt.h"
#include "vsgpt_test_macros.h"
#include "vsgpt_test_memory.h"
#include "vsgpt_test_rwlock.h"
#include "vsgpt_test_unused.h"

#include "../libvsgpt/libvsgpt_partition.h"
#include "../libvsgpt/libvsgpt_partition_values.h"

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

/* Tests the libvsgpt_partition_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_initialize(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	int result                                    = 0;

#if defined( HAVE_VSGPT_TEST_MEMORY )
	int number_of_malloc_fail_tests               = 8;
	int number_of_memset_fail_tests               = 1;
	int test_number                               = 0;
#endif

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
	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsgpt_partition_initialize(
	          NULL,
	          NULL,
	          partition_values,
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
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

/* TODO test libvsgpt_partition_values_get_size failing */

#if defined( HAVE_VSGPT_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 * 2 fail in libcthreads_read_write_lock_initialize
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvsgpt_partition_initialize with malloc failing
		 */
		vsgpt_test_malloc_attempts_before_fail = test_number;

		result = libvsgpt_partition_initialize(
		          &partition,
		          NULL,
		          partition_values,
		          &error );

		if( vsgpt_test_malloc_attempts_before_fail != -1 )
		{
			vsgpt_test_malloc_attempts_before_fail = -1;

			if( partition != NULL )
			{
				libvsgpt_partition_free(
				 &partition,
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
			 "partition",
			 partition );

			VSGPT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	/* 1 fail in memset after memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvsgpt_partition_initialize with memset failing
		 */
		vsgpt_test_memset_attempts_before_fail = test_number;

		result = libvsgpt_partition_initialize(
		          &partition,
		          NULL,
		          partition_values,
		          &error );

		if( vsgpt_test_memset_attempts_before_fail != -1 )
		{
			vsgpt_test_memset_attempts_before_fail = -1;

			if( partition != NULL )
			{
				libvsgpt_partition_free(
				 &partition,
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
			 "partition",
			 partition );

			VSGPT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSGPT_TEST_MEMORY ) */

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
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_free function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_free(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	int result                                    = 0;

	/* Test error cases
	 */
	result = libvsgpt_partition_free(
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libvsgpt_partition_free with pthread_rwlock_destroy failing in libcthreads_read_write_lock_free
	 */
	vsgpt_test_pthread_rwlock_destroy_attempts_before_fail = 0;

	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	if( vsgpt_test_pthread_rwlock_destroy_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_destroy_attempts_before_fail = -1;

		/* Clean up
		 */
		result = libvsgpt_partition_free(
		          &partition,
		          &error );

		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "partition",
		 partition );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSGPT_TEST_ASSERT_IS_NULL(
		 "partition",
		 partition );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
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

#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_get_entry_index function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_get_entry_index(
     libvsgpt_partition_t *partition )
{
	libcerror_error_t *error = NULL;
	uint32_t entry_index     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsgpt_partition_get_entry_index(
	          partition,
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
	result = libvsgpt_partition_get_entry_index(
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

	result = libvsgpt_partition_get_entry_index(
	          partition,
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

	/* Test libvsgpt_partition_get_entry_index with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_entry_index(
	          partition,
	          &entry_index,
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
	/* Test libvsgpt_partition_get_entry_index with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_entry_index(
	          partition,
	          &entry_index,
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

/* Tests the libvsgpt_partition_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_get_identifier(
     libvsgpt_partition_t *partition )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsgpt_partition_get_identifier(
	          partition,
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
	result = libvsgpt_partition_get_identifier(
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

	result = libvsgpt_partition_get_identifier(
	          partition,
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

	result = libvsgpt_partition_get_identifier(
	          partition,
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

	result = libvsgpt_partition_get_identifier(
	          partition,
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

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_partition_get_identifier with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_identifier(
	          partition,
	          guid_data,
	          16,
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
	/* Test libvsgpt_partition_get_identifier with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_identifier(
	          partition,
	          guid_data,
	          16,
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

/* Tests the libvsgpt_partition_get_type_identifier function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_get_type_identifier(
     libvsgpt_partition_t *partition )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsgpt_partition_get_type_identifier(
	          partition,
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
	result = libvsgpt_partition_get_type_identifier(
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

	result = libvsgpt_partition_get_type_identifier(
	          partition,
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

	result = libvsgpt_partition_get_type_identifier(
	          partition,
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

	result = libvsgpt_partition_get_type_identifier(
	          partition,
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

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_partition_get_type_identifier with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_type_identifier(
	          partition,
	          guid_data,
	          16,
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
	/* Test libvsgpt_partition_get_type_identifier with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_type_identifier(
	          partition,
	          guid_data,
	          16,
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

/* Tests the libvsgpt_partition_get_type function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_get_type(
     libvsgpt_partition_t *partition )
{
	libcerror_error_t *error = NULL;
	int result               = 0;
	uint8_t partition_type   = 0;

	/* Test regular cases
	 */
	result = libvsgpt_partition_get_type(
	          partition,
	          &partition_type,
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
	result = libvsgpt_partition_get_type(
	          NULL,
	          &partition_type,
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

	result = libvsgpt_partition_get_type(
	          partition,
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

	/* Test libvsgpt_partition_get_type with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_type(
	          partition,
	          &partition_type,
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
	/* Test libvsgpt_partition_get_type with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_type(
	          partition,
	          &partition_type,
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

/* Tests the libvsgpt_partition_get_volume_offset function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_get_volume_offset(
     libvsgpt_partition_t *partition )
{
	libcerror_error_t *error = NULL;
	off64_t volume_offset    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsgpt_partition_get_volume_offset(
	          partition,
	          &volume_offset,
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
	result = libvsgpt_partition_get_volume_offset(
	          NULL,
	          &volume_offset,
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

	result = libvsgpt_partition_get_volume_offset(
	          partition,
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

	/* Test libvsgpt_partition_get_volume_offset with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_volume_offset(
	          partition,
	          &volume_offset,
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
	/* Test libvsgpt_partition_get_volume_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_volume_offset(
	          partition,
	          &volume_offset,
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

/* Tests the libvsgpt_internal_partition_read_buffer_from_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_internal_partition_read_buffer_from_file_io_handle(
     void )
{
	uint8_t buffer[ 2048 ];
	uint8_t test_data[ 2048 ];

	libbfio_handle_t *file_io_handle              = NULL;
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	ssize_t read_count                            = 0;
	off64_t current_offset                        = 0;
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

	partition_values->size = 2048;

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          test_data,
	          2048,
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
	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              (libvsgpt_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              512,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              (libvsgpt_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              0,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              (libvsgpt_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              2048,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 1536 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              NULL,
	              file_io_handle,
	              buffer,
	              512,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	current_offset = ( (libvsgpt_internal_partition_t *) partition )->current_offset;

	( (libvsgpt_internal_partition_t *) partition )->current_offset = -1;

	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              (libvsgpt_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              512,
	              &error );

	( (libvsgpt_internal_partition_t *) partition )->current_offset = current_offset;

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              (libvsgpt_internal_partition_t *) partition,
	              file_io_handle,
	              NULL,
	              512,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              (libvsgpt_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSGPT_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	/* Test libvsgpt_internal_partition_read_buffer_from_file_io_handle with memcpy failing
	 */
	vsgpt_test_memcpy_attempts_before_fail = 0;

	read_count = libvsgpt_internal_partition_read_buffer_from_file_io_handle(
	              (libvsgpt_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              512,
	              &error );

	if( vsgpt_test_memcpy_attempts_before_fail != -1 )
	{
		vsgpt_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSGPT_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED ) */

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

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_read_buffer(
     void )
{
	uint8_t buffer[ 2048 ];
	uint8_t test_data[ 2048 ];

	libbfio_handle_t *file_io_handle              = NULL;

	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	ssize_t read_count                            = 0;
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

	partition_values->size = 2048;

	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          test_data,
	          2048,
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          file_io_handle,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libvsgpt_partition_read_buffer(
	              partition,
	              buffer,
	              512,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libvsgpt_partition_read_buffer(
	              partition,
	              buffer,
	              2048,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 1536 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsgpt_partition_read_buffer(
	              NULL,
	              buffer,
	              512,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsgpt_partition_read_buffer with libvsgpt_internal_partition_read_buffer_from_file_io_handle failing
	 */
	read_count = libvsgpt_partition_read_buffer(
	              partition,
	              NULL,
	              512,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_partition_read_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libvsgpt_partition_read_buffer(
	              partition,
	              buffer,
	              512,
	              &error );

	if( vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsgpt_partition_read_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libvsgpt_partition_read_buffer(
	              partition,
	              buffer,
	              512,
	              &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_read_buffer_at_offset(
     void )
{
	uint8_t buffer[ 2048 ];
	uint8_t test_data[ 2048 ];

	libbfio_handle_t *file_io_handle              = NULL;

	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	ssize_t read_count                            = 0;
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

	partition_values->size = 2048;

	result = vsgpt_test_open_file_io_handle(
	          &file_io_handle,
	          test_data,
	          2048,
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          file_io_handle,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libvsgpt_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              0,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libvsgpt_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              2048,
	              512,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 1536 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsgpt_partition_read_buffer_at_offset(
	              NULL,
	              buffer,
	              512,
	              0,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsgpt_partition_read_buffer_at_offset with libvsgpt_internal_partition_seek_offset failing
	 */
	read_count = libvsgpt_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              -1,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsgpt_partition_read_buffer_at_offset with libvsgpt_internal_partition_read_buffer_from_file_io_handle failing
	 */
	read_count = libvsgpt_partition_read_buffer_at_offset(
	              partition,
	              NULL,
	              512,
	              0,
	              &error );

	VSGPT_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_partition_read_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libvsgpt_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              0,
	              &error );

	if( vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsgpt_partition_read_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libvsgpt_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              0,
	              &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_internal_partition_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_internal_partition_seek_offset(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
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

	partition_values->size = 2048;

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	offset = libvsgpt_internal_partition_seek_offset(
	          (libvsgpt_internal_partition_t *) partition,
	          512,
	          SEEK_CUR,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 512 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsgpt_internal_partition_seek_offset(
	          (libvsgpt_internal_partition_t *) partition,
	          512,
	          SEEK_CUR,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 1024 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsgpt_internal_partition_seek_offset(
	          (libvsgpt_internal_partition_t *) partition,
	          0,
	          SEEK_END,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 2048 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsgpt_internal_partition_seek_offset(
	          (libvsgpt_internal_partition_t *) partition,
	          0,
	          SEEK_SET,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvsgpt_internal_partition_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsgpt_internal_partition_seek_offset(
	          (libvsgpt_internal_partition_t *) partition,
	          -1,
	          SEEK_SET,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsgpt_internal_partition_seek_offset(
	          (libvsgpt_internal_partition_t *) partition,
	          0,
	          -1,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_seek_offset(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	offset = libvsgpt_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 0 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvsgpt_partition_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsgpt_partition_seek_offset with libvsgpt_internal_partition_seek_offset failing
	 */
	offset = libvsgpt_partition_seek_offset(
	          partition,
	          -1,
	          SEEK_SET,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSGPT_TEST_RWLOCK )

	/* Test libvsgpt_partition_seek_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	offset = libvsgpt_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	if( vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsgpt_partition_seek_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	offset = libvsgpt_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	if( vsgpt_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSGPT_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		VSGPT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSGPT_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_get_offset function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_get_offset(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_get_offset(
	          partition,
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
	result = libvsgpt_partition_get_offset(
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

	result = libvsgpt_partition_get_offset(
	          partition,
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

	/* Test libvsgpt_partition_get_offset with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_offset(
	          partition,
	          &offset,
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
	/* Test libvsgpt_partition_get_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_offset(
	          partition,
	          &offset,
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

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsgpt_partition_get_size function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_get_size(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
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

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsgpt_partition_get_size(
	          partition,
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
	result = libvsgpt_partition_get_size(
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

	result = libvsgpt_partition_get_size(
	          partition,
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

	/* Test libvsgpt_partition_get_size with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsgpt_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_size(
	          partition,
	          &size,
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
	/* Test libvsgpt_partition_get_size with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsgpt_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsgpt_partition_get_size(
	          partition,
	          &size,
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

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
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
#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )
	libcerror_error_t *error                      = NULL;
	libvsgpt_partition_t *partition               = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	int result                                    = 0;
#endif

	VSGPT_TEST_UNREFERENCED_PARAMETER( argc )
	VSGPT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_initialize",
	 vsgpt_test_partition_initialize );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_free",
	 vsgpt_test_partition_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

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

	result = libvsgpt_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_partition_get_entry_index",
	 vsgpt_test_partition_get_entry_index,
	 partition );

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_partition_get_identifier",
	 vsgpt_test_partition_get_identifier,
	 partition );

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_partition_get_type_identifier",
	 vsgpt_test_partition_get_type_identifier,
	 partition );

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_partition_get_type",
	 vsgpt_test_partition_get_type,
	 partition );

	VSGPT_TEST_RUN_WITH_ARGS(
	 "libvsgpt_partition_get_volume_offset",
	 vsgpt_test_partition_get_volume_offset,
	 partition );

	VSGPT_TEST_RUN(
	 "libvsgpt_internal_partition_read_buffer_from_file_io_handle",
	 vsgpt_test_internal_partition_read_buffer_from_file_io_handle );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_read_buffer",
	 vsgpt_test_partition_read_buffer );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_read_buffer_at_offset",
	 vsgpt_test_partition_read_buffer_at_offset );

	VSGPT_TEST_RUN(
	 "libvsgpt_internal_partition_seek_offset",
	 vsgpt_test_internal_partition_seek_offset );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_seek_offset",
	 vsgpt_test_partition_seek_offset );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_get_offset",
	 vsgpt_test_partition_get_offset );

	VSGPT_TEST_RUN(
	 "libvsgpt_partition_get_size",
	 vsgpt_test_partition_get_size );

	/* Clean up
	 */
	result = libvsgpt_partition_free(
	          &partition,
	          &error );

	VSGPT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSGPT_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

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

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */
}

