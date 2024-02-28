/*
 * The partition table header functions
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
	/* The partition header block number
	 */
	uint64_t partition_header_block_number;

	/* The backup partition header block number
	 */
	uint64_t backup_partition_header_block_number;

	/* The partition area start block number
	 */
	uint64_t partition_area_start_block_number;

	/* The partition area end block number
	 */
	uint64_t partition_area_end_block_number;

	/* The disk identifier
	 */
	uint8_t disk_identifier[ 16 ];

	/* The partition entries start block number
	 */
	uint64_t partition_entries_start_block_number;

	/* The number of partition entries
	 */
	uint32_t number_of_partition_entries;

	/* The partition entry data size
	 */
	uint32_t partition_entry_data_size;

	/* The partition entries data checksum
	 */
	uint32_t partition_entries_data_checksum;

	/* Value to indicate the partition table header is corrupt
	 */
	uint8_t is_corrupt;
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

int libvsgpt_partition_table_header_get_disk_identifier(
     libvsgpt_partition_table_header_t *partition_table_header,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_PARTITION_TABLE_HEADER_H ) */

