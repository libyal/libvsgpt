/*
 * The partition entry functions
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

#if !defined( _LIBVSGPT_PARTITION_ENTRY_H )
#define _LIBVSGPT_PARTITION_ENTRY_H

#include <common.h>
#include <types.h>

#include "libvsgpt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_partition_entry libvsgpt_partition_entry_t;

struct libvsgpt_partition_entry
{
	/* The type identifier
	 */
	uint8_t type_identifier[ 16 ];

	/* The identifier
	 */
	uint8_t identifier[ 16 ];

	/* The start block number
	 */
	uint64_t start_block_number;

	/* The end block number
	 */
	uint64_t end_block_number;

	/* The attribute flags
	 */
	uint64_t attribute_flags;

	/* The name
	 */
	uint8_t name[ 72 ];
};

int libvsgpt_partition_entry_initialize(
     libvsgpt_partition_entry_t **partition_entry,
     libcerror_error_t **error );

int libvsgpt_partition_entry_free(
     libvsgpt_partition_entry_t **partition_entry,
     libcerror_error_t **error );

int libvsgpt_partition_entry_check_for_empty_block(
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvsgpt_partition_entry_read_data(
     libvsgpt_partition_entry_t *partition_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_PARTITION_ENTRY_H ) */

