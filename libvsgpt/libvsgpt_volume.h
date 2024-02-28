/*
 * The volume functions
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

#if !defined( _LIBVSGPT_VOLUME_H )
#define _LIBVSGPT_VOLUME_H

#include <common.h>
#include <types.h>

#include "libvsgpt_boot_record.h"
#include "libvsgpt_extern.h"
#include "libvsgpt_io_handle.h"
#include "libvsgpt_libbfio.h"
#include "libvsgpt_libcdata.h"
#include "libvsgpt_libcerror.h"
#include "libvsgpt_libcthreads.h"
#include "libvsgpt_partition_table_header.h"
#include "libvsgpt_partition_values.h"
#include "libvsgpt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_internal_volume libvsgpt_internal_volume_t;

struct libvsgpt_internal_volume
{
	/* The volume size
	 */
	size64_t size;

	/* The partition table header
	 */
	libvsgpt_partition_table_header_t *partition_table_header;

	/* The partitions array
	 */
	libcdata_array_t *partitions;

	/* The IO handle
	 */
	libvsgpt_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* Value to indicate the volume is corrupt
	 */
	uint8_t is_corrupt;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBVSGPT_EXTERN \
int libvsgpt_volume_initialize(
     libvsgpt_volume_t **volume,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_free(
     libvsgpt_volume_t **volume,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_signal_abort(
     libvsgpt_volume_t *volume,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_open(
     libvsgpt_volume_t *volume,
     char const *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBVSGPT_EXTERN \
int libvsgpt_volume_open_wide(
     libvsgpt_volume_t *volume,
     wchar_t const *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBVSGPT_EXTERN \
int libvsgpt_volume_open_file_io_handle(
     libvsgpt_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_close(
     libvsgpt_volume_t *volume,
     libcerror_error_t **error );

int libvsgpt_internal_volume_open_read(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvsgpt_internal_volume_read_partition_table_headers(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvsgpt_internal_volume_read_partition_entries(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvsgpt_internal_volume_read_mbr_partition_entries(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libvsgpt_boot_record_t *boot_record,
     uint8_t is_master_boot_record,
     off64_t first_extended_boot_record_offset,
     int recursion_depth,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_get_bytes_per_sector(
     libvsgpt_volume_t *volume,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_get_disk_identifier(
     libvsgpt_volume_t *volume,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_get_number_of_partitions(
     libvsgpt_volume_t *volume,
     int *number_of_partitions,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_get_partition_by_index(
     libvsgpt_volume_t *volume,
     int partition_index,
     libvsgpt_partition_t **partition,
     libcerror_error_t **error );

int libvsgpt_internal_volume_get_partition_values_by_identifier(
     libvsgpt_internal_volume_t *internal_volume,
     uint32_t entry_index,
     libvsgpt_partition_values_t **partition_values,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_has_partition_with_identifier(
     libvsgpt_volume_t *volume,
     uint32_t entry_index,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_volume_get_partition_by_identifier(
     libvsgpt_volume_t *volume,
     uint32_t entry_index,
     libvsgpt_partition_t **partition,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_VOLUME_H ) */

