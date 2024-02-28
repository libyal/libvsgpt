/*
 * Library partition_type_identifier type test program
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

#include "vsgpt_test_libvsgpt.h"
#include "vsgpt_test_macros.h"
#include "vsgpt_test_unused.h"

#include "../libvsgpt/libvsgpt_partition_type_identifier.h"

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

/* Tests the libvsgpt_partition_type_identifier_get_description function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_partition_type_identifier_get_description(
     void )
{
	uint8_t guid_data[ 16 ];

	const char *description = NULL;

	/* Test regular cases
	 */
	description = libvsgpt_partition_type_identifier_get_description(
	               NULL );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "description",
	 description );

	description = libvsgpt_partition_type_identifier_get_description(
	               guid_data );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "description",
	 description );

	return( 1 );

on_error:
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
	 "libvsgpt_partition_type_identifier_get_description",
	 vsgpt_test_partition_type_identifier_get_description );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */
}

