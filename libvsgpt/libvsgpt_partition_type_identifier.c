/*
 * Partition type identifier functions
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
#include <memory.h>
#include <types.h>

#include "libvsgpt_libcerror.h"
#include "libvsgpt_partition_type_identifier.h"

uint8_t libvsgpt_partition_type_identifier_linux_filesystem_data[ 16 ] = {
	0xaf, 0x3d, 0xc6, 0x0f, 0x83, 0x84, 0x72, 0x47, 0x8e, 0x79, 0x3d, 0x69, 0xd8, 0x47, 0x7d, 0xe4 };

uint8_t libvsgpt_partition_type_identifier_unknown[ 16 ] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

/* The partition type identifiers
 */
libvsgpt_partition_type_identifier_definition_t libvsgpt_partition_type_identifier_definitions[ ] = {
	{ libvsgpt_partition_type_identifier_linux_filesystem_data,	"Linux filesystem data" },

	{ libvsgpt_partition_type_identifier_unknown,			"Unknown" } };

/* Retrieves a string containing the description of the folder identifier
 */
const char *libvsgpt_partition_type_identifier_get_description(
             const uint8_t *partition_type_identifier )
{
	int iterator = 0;

	if( partition_type_identifier == NULL )
	{
		return( "Invalid partition type identifier" );
	}
	while( memory_compare(
	        ( libvsgpt_partition_type_identifier_definitions[ iterator ] ).identifier,
	        libvsgpt_partition_type_identifier_unknown,
	        16 ) != 0 )
	{
		if( memory_compare(
		     ( libvsgpt_partition_type_identifier_definitions[ iterator ] ).identifier,
		     partition_type_identifier,
		     16 ) == 0 )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libvsgpt_partition_type_identifier_definitions[ iterator ] ).description );
}

