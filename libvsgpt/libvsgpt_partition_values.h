/*
 * The partition values functions
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

#if !defined( _LIBVSGPT_PARTITION_VALUES_H )
#define _LIBVSGPT_PARTITION_VALUES_H

#include <common.h>
#include <types.h>

#include "libvsgpt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_partition_values libvsgpt_partition_values_t;

struct libvsgpt_partition_values
{
	/* The entry index
	 */
	uint32_t entry_index;

	/* The type identifier
	 */
	uint8_t type_identifier[ 16 ];

	/* The identifier
	 */
	uint8_t identifier[ 16 ];

	/* The type
	 */
	uint8_t type;

	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;
};

int libvsgpt_partition_values_initialize(
     libvsgpt_partition_values_t **partition_values,
     libcerror_error_t **error );

int libvsgpt_partition_values_free(
     libvsgpt_partition_values_t **partition_values,
     libcerror_error_t **error );

int libvsgpt_partition_values_get_entry_index(
     libvsgpt_partition_values_t *partition_values,
     uint32_t *entry_index,
     libcerror_error_t **error );

int libvsgpt_partition_values_get_identifier(
     libvsgpt_partition_values_t *partition_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libvsgpt_partition_values_get_type_identifier(
     libvsgpt_partition_values_t *partition_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libvsgpt_partition_values_get_type(
     libvsgpt_partition_values_t *partition_values,
     uint8_t *type,
     libcerror_error_t **error );

int libvsgpt_partition_values_get_offset(
     libvsgpt_partition_values_t *partition_values,
     off64_t *offset,
     libcerror_error_t **error );

int libvsgpt_partition_values_get_size(
     libvsgpt_partition_values_t *partition_values,
     size64_t *size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_PARTITION_VALUES_H ) */

