/*
 * The partition functions
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

#if !defined( _LIBVSGPT_PARTITION_H )
#define _LIBVSGPT_PARTITION_H

#include <common.h>
#include <types.h>

#include "libvsgpt_extern.h"
#include "libvsgpt_libbfio.h"
#include "libvsgpt_libcerror.h"
#include "libvsgpt_libcthreads.h"
#include "libvsgpt_libfcache.h"
#include "libvsgpt_libfdata.h"
#include "libvsgpt_partition_values.h"
#include "libvsgpt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_internal_partition libvsgpt_internal_partition_t;

struct libvsgpt_internal_partition
{
	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The partition values
	 */
	libvsgpt_partition_values_t *partition_values;

	/* The sectors vector
	 */
	libfdata_vector_t *sectors_vector;

	/* The sectors cache
	 */
	libfcache_cache_t *sectors_cache;

	/* The current offset
	 */
	off64_t current_offset;

	/* The size
	 */
	size64_t size;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libvsgpt_partition_initialize(
     libvsgpt_partition_t **partition,
     libbfio_handle_t *file_io_handle,
     libvsgpt_partition_values_t *partition_values,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_free(
     libvsgpt_partition_t **partition,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_get_entry_index(
     libvsgpt_partition_t *partition,
     uint32_t *entry_index,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_get_identifier(
     libvsgpt_partition_t *partition,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_get_type_identifier(
     libvsgpt_partition_t *partition,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_get_type(
     libvsgpt_partition_t *partition,
     uint8_t *type,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_get_volume_offset(
     libvsgpt_partition_t *partition,
     off64_t *volume_offset,
     libcerror_error_t **error );

ssize_t libvsgpt_internal_partition_read_buffer_from_file_io_handle(
         libvsgpt_internal_partition_t *internal_partition,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSGPT_EXTERN \
ssize_t libvsgpt_partition_read_buffer(
         libvsgpt_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSGPT_EXTERN \
ssize_t libvsgpt_partition_read_buffer_at_offset(
         libvsgpt_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libvsgpt_internal_partition_seek_offset(
         libvsgpt_internal_partition_t *internal_partition,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSGPT_EXTERN \
off64_t libvsgpt_partition_seek_offset(
         libvsgpt_partition_t *partition,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_get_offset(
     libvsgpt_partition_t *partition,
     off64_t *offset,
     libcerror_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_partition_get_size(
     libvsgpt_partition_t *partition,
     size64_t *size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_PARTITION_H ) */

