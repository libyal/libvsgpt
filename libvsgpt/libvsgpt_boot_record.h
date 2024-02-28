/*
 * The boot record functions
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

#if !defined( _LIBVSGPT_BOOT_RECORD_H )
#define _LIBVSGPT_BOOT_RECORD_H

#include <common.h>
#include <types.h>

#include "libvsgpt_libbfio.h"
#include "libvsgpt_libcdata.h"
#include "libvsgpt_libcerror.h"
#include "libvsgpt_mbr_partition_entry.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_boot_record libvsgpt_boot_record_t;

struct libvsgpt_boot_record
{
	/* The disk identity
	 */
	uint32_t disk_identity;

	/* The partition entries array
	 */
	libcdata_array_t *partition_entries;
};

int libvsgpt_boot_record_initialize(
     libvsgpt_boot_record_t **boot_record,
     libcerror_error_t **error );

int libvsgpt_boot_record_free(
     libvsgpt_boot_record_t **boot_record,
     libcerror_error_t **error );

int libvsgpt_boot_record_read_data(
     libvsgpt_boot_record_t *boot_record,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvsgpt_boot_record_read_file_io_handle(
     libvsgpt_boot_record_t *boot_record,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvsgpt_boot_record_get_number_of_partition_entries(
     libvsgpt_boot_record_t *boot_record,
     int *number_of_partition_entries,
     libcerror_error_t **error );

int libvsgpt_boot_record_get_partition_entry_by_index(
     libvsgpt_boot_record_t *boot_record,
     int partition_entry_index,
     libvsgpt_mbr_partition_entry_t **partition_entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_BOOT_RECORD_H ) */

