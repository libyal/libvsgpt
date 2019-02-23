/*
 * The partition table header functions
 *
 * Copyright (C) 2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBVSGPT_PARTITION_TABLE_HEADER_H )
#define _LIBVSGPT_PARTITION_TABLE_HEADER_H

#include <common.h>
#include <types.h>

#include "libvsgpt_libbfio.h"
#include "libvsgpt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_partition_table_header libvsgpt_partition_table_header_t;

struct libvsgpt_partition_table_header
{
	/* The disk identity
	 */
	uint32_t disk_identity;
};

int libvsgpt_partition_table_header_initialize(
     libvsgpt_partition_table_header_t **partition_table_header,
     libcerror_error_t **error );

int libvsgpt_partition_table_header_free(
     libvsgpt_partition_table_header_t **partition_table_header,
     libcerror_error_t **error );

int libvsgpt_partition_table_header_read_data(
     libvsgpt_partition_table_header_t *partition_table_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvsgpt_partition_table_header_read_file_io_handle(
     libvsgpt_partition_table_header_t *partition_table_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_PARTITION_TABLE_HEADER_H ) */

