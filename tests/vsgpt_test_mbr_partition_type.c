/*
 * Library mbr_partition_type type test program
 *
 * Copyright (C) 2019-2023, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libvsgpt/libvsgpt_mbr_partition_type.h"

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )

#if defined( HAVE_DEBUG_OUTPUT )

/* Tests the libvsgpt_mbr_partition_type_get_description function
 * Returns 1 if successful or 0 if not
 */
int vsgpt_test_mbr_partition_type_get_description(
     void )
{
	const char *description = NULL;

	/* Test regular cases
	 */
	description = libvsgpt_mbr_partition_type_get_description(
	               0xaa );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "description",
	 description );

	description = libvsgpt_mbr_partition_type_get_description(
	               0x0f );

	VSGPT_TEST_ASSERT_IS_NOT_NULL(
	 "description",
	 description );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

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
#if defined( HAVE_DEBUG_OUTPUT )

	VSGPT_TEST_RUN(
	 "libvsgpt_mbr_partition_type_get_description",
	 vsgpt_test_mbr_partition_type_get_description );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */
#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT )
#if defined( HAVE_DEBUG_OUTPUT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */
#endif /* defined( __GNUC__ ) && !defined( LIBVSGPT_DLL_IMPORT ) */
}

