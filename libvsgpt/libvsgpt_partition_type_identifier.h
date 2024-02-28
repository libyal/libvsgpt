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

#if !defined( _LIBVSGPT_PARTITION_TYPE_IDENTIFIER_H )
#define _LIBVSGPT_PARTITION_TYPE_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "libvsgpt_extern.h"
#include "libvsgpt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_partition_type_identifier_definition libvsgpt_partition_type_identifier_definition_t;

struct libvsgpt_partition_type_identifier_definition
{
	/* The partition type identifier stored as a little endian GUID
	 */
	uint8_t *identifier;

	/* The partition type description
	 */
	const char *description;
};

extern uint8_t libvsgpt_partition_type_identifier_linux_filesystem_data[ 16 ];

LIBVSGPT_EXTERN \
const char *libvsgpt_partition_type_identifier_get_description(
             const uint8_t *partition_type_identifier );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_PARTITION_TYPE_IDENTIFIER_H ) */

