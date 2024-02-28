/*
 * Library to access the GUID Partition Table (GPT) volume system
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

#if !defined( _LIBVSGPT_H )
#define _LIBVSGPT_H

#include <libvsgpt/codepage.h>
#include <libvsgpt/definitions.h>
#include <libvsgpt/error.h>
#include <libvsgpt/extern.h>
#include <libvsgpt/features.h>
#include <libvsgpt/types.h>

#include <stdio.h>

#if defined( LIBVSGPT_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBVSGPT_EXTERN \
const char *libvsgpt_get_version(
             void );

/* Returns the access flags for reading
 */
LIBVSGPT_EXTERN \
int libvsgpt_get_access_flags_read(
     void );

/* Returns the access flags for reading and writing
 */
LIBVSGPT_EXTERN \
int libvsgpt_get_access_flags_read_write(
     void );

/* Returns the access flags for writing
 */
LIBVSGPT_EXTERN \
int libvsgpt_get_access_flags_write(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_get_codepage(
     int *codepage,
     libvsgpt_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_set_codepage(
     int codepage,
     libvsgpt_error_t **error );

/* Determines if a volume contains a GUID Partition Table (GPT) signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_check_volume_signature(
     const char *filename,
     libvsgpt_error_t **error );

#if defined( LIBVSGPT_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a volume contains a GUID Partition Table (GPT) signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_check_volume_signature_wide(
     const wchar_t *filename,
     libvsgpt_error_t **error );

#endif /* defined( LIBVSGPT_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSGPT_HAVE_BFIO )

/* Determines if a volume contains a GUID Partition Table (GPT) signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvsgpt_error_t **error );

#endif /* defined( LIBVSGPT_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBVSGPT_EXTERN \
void libvsgpt_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_notify_set_stream(
     FILE *stream,
     libvsgpt_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_notify_stream_open(
     const char *filename,
     libvsgpt_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_notify_stream_close(
     libvsgpt_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBVSGPT_EXTERN \
void libvsgpt_error_free(
      libvsgpt_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_error_fprint(
     libvsgpt_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_error_sprint(
     libvsgpt_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_error_backtrace_fprint(
     libvsgpt_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_error_backtrace_sprint(
     libvsgpt_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Volume functions
 * ------------------------------------------------------------------------- */

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_initialize(
     libvsgpt_volume_t **volume,
     libvsgpt_error_t **error );

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_free(
     libvsgpt_volume_t **volume,
     libvsgpt_error_t **error );

/* Signals a volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_signal_abort(
     libvsgpt_volume_t *volume,
     libvsgpt_error_t **error );

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_open(
     libvsgpt_volume_t *volume,
     const char *filename,
     int access_flags,
     libvsgpt_error_t **error );

#if defined( LIBVSGPT_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_open_wide(
     libvsgpt_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libvsgpt_error_t **error );

#endif /* defined( LIBVSGPT_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSGPT_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_open_file_io_handle(
     libvsgpt_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsgpt_error_t **error );

#endif /* defined( LIBVSGPT_HAVE_BFIO ) */

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_close(
     libvsgpt_volume_t *volume,
     libvsgpt_error_t **error );

/* Retrieves the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_get_bytes_per_sector(
     libvsgpt_volume_t *volume,
     uint32_t *bytes_per_sector,
     libvsgpt_error_t **error );

/* Retrieves the disk identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_get_disk_identifier(
     libvsgpt_volume_t *volume,
     uint8_t *guid_data,
     size_t guid_data_size,
     libvsgpt_error_t **error );

/* Retrieves the number of partitions
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_get_number_of_partitions(
     libvsgpt_volume_t *volume,
     int *number_of_partitions,
     libvsgpt_error_t **error );

/* Retrieves a specific partition
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_get_partition_by_index(
     libvsgpt_volume_t *volume,
     int partition_index,
     libvsgpt_partition_t **partition,
     libvsgpt_error_t **error );

/* Determines if the volume contains a partition with the corresponding (partition) entry index
 * Returns 1 if the volume contains such a partition, 0 if not or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_has_partition_with_identifier(
     libvsgpt_volume_t *volume,
     uint32_t entry_index,
     libvsgpt_error_t **error );

/* Retrieves the partition with the corresponding (partition) entry index
 * Returns 1 if successful, 0 if not found or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_volume_get_partition_by_identifier(
     libvsgpt_volume_t *volume,
     uint32_t entry_index,
     libvsgpt_partition_t **partition,
     libvsgpt_error_t **error );

/* -------------------------------------------------------------------------
 * Partition functions
 * ------------------------------------------------------------------------- */

/* Frees a partition
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_free(
     libvsgpt_partition_t **partition,
     libvsgpt_error_t **error );

/* Retrieves the partition entry index
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_get_entry_index(
     libvsgpt_partition_t *partition,
     uint32_t *entry_index,
     libvsgpt_error_t **error );

/* Retrieves the partition identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_get_identifier(
     libvsgpt_partition_t *partition,
     uint8_t *guid_data,
     size_t guid_data_size,
     libvsgpt_error_t **error );

/* Retrieves the partition type identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_get_type_identifier(
     libvsgpt_partition_t *partition,
     uint8_t *guid_data,
     size_t guid_data_size,
     libvsgpt_error_t **error );

/* Retrieves the partition type
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_get_type(
     libvsgpt_partition_t *partition,
     uint8_t *type,
     libvsgpt_error_t **error );

/* Retrieves the partition offset relative to the start of the volume
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_get_volume_offset(
     libvsgpt_partition_t *partition,
     off64_t *volume_offset,
     libvsgpt_error_t **error );

/* Reads (partition) data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBVSGPT_EXTERN \
ssize_t libvsgpt_partition_read_buffer(
         libvsgpt_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         libvsgpt_error_t **error );

/* Reads (partition) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBVSGPT_EXTERN \
ssize_t libvsgpt_partition_read_buffer_at_offset(
         libvsgpt_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libvsgpt_error_t **error );

/* Seeks a certain offset of the (partition) data
 * Returns the offset if seek is successful or -1 on error
 */
LIBVSGPT_EXTERN \
off64_t libvsgpt_partition_seek_offset(
         libvsgpt_partition_t *partition,
         off64_t offset,
         int whence,
         libvsgpt_error_t **error );

/* Retrieves the current offset
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_get_offset(
     libvsgpt_partition_t *partition,
     off64_t *offset,
     libvsgpt_error_t **error );

/* Retrieves the partition size
 * Returns 1 if successful or -1 on error
 */
LIBVSGPT_EXTERN \
int libvsgpt_partition_get_size(
     libvsgpt_partition_t *partition,
     size64_t *size,
     libvsgpt_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_H ) */

