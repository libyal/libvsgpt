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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvsgpt_debug.h"
#include "libvsgpt_libbfio.h"
#include "libvsgpt_libcerror.h"
#include "libvsgpt_libcnotify.h"
#include "libvsgpt_libfguid.h"
#include "libvsgpt_partition_table_header.h"

#include "vsgpt_partition_table.h"

/* Creates a partition table header
 * Make sure the value partition_table_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_table_header_initialize(
     libvsgpt_partition_table_header_t **partition_table_header,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_table_header_initialize";

	if( partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition table header.",
		 function );

		return( -1 );
	}
	if( *partition_table_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition table header value already set.",
		 function );

		return( -1 );
	}
	*partition_table_header = memory_allocate_structure(
	                           libvsgpt_partition_table_header_t );

	if( *partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition table header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *partition_table_header,
	     0,
	     sizeof( libvsgpt_partition_table_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear partition table header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *partition_table_header != NULL )
	{
		memory_free(
		 *partition_table_header );

		*partition_table_header = NULL;
	}
	return( -1 );
}

/* Frees a partition table header
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_table_header_free(
     libvsgpt_partition_table_header_t **partition_table_header,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_table_header_free";

	if( partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition table header.",
		 function );

		return( -1 );
	}
	if( *partition_table_header != NULL )
	{
		memory_free(
		 *partition_table_header );

		*partition_table_header = NULL;
	}
	return( 1 );
}

/* Reads a partition table header
 * Returns 1 if successful, 0 if signature does not match or -1 on error
 */
int libvsgpt_partition_table_header_read_data(
     libvsgpt_partition_table_header_t *partition_table_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function         = "libvsgpt_partition_table_header_read_data";
	uint16_t major_format_version = 0;
	uint16_t minor_format_version = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit          = 0;
	uint32_t value_32bit          = 0;
#endif

	if( partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition table header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( vsgpt_partition_table_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: partition table header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vsgpt_partition_table_header_t *) data )->signature,
	     "EFI PART",
	     8 ) != 0 )
	{
		return( 0 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (vsgpt_partition_table_header_t *) data )->major_format_version,
	 major_format_version );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vsgpt_partition_table_header_t *) data )->minor_format_version,
	 minor_format_version );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 0 ],
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 1 ],
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 2 ],
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 3 ],
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 4 ],
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 5 ],
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 6 ],
		 ( (vsgpt_partition_table_header_t *) data )->signature[ 7 ] );

		libcnotify_printf(
		 "%s: format version\t\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 major_format_version,
		 minor_format_version );

		byte_stream_copy_to_uint32_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->header_data_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: header data size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->header_data_checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: header data checksum\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->header_block_number,
		 value_64bit );
		libcnotify_printf(
		 "%s: header block number\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->backup_header_block_number,
		 value_64bit );
		libcnotify_printf(
		 "%s: backup header block number\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->area_start_block_number,
		 value_64bit );
		libcnotify_printf(
		 "%s: area start block number\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->area_end_block_number,
		 value_64bit );
		libcnotify_printf(
		 "%s: area end block number\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		if( libvsgpt_debug_print_guid_value(
		     function,
		     "disk identifier\t\t\t\t",
		     ( (vsgpt_partition_table_header_t *) data )->disk_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint64_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->entries_start_block_number,
		 value_64bit );
		libcnotify_printf(
		 "%s: entries start block number\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->number_of_entries,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of entries\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->entry_data_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: entry data size\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (vsgpt_partition_table_header_t *) data )->entries_data_checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: entries data checksum\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads a partition table header
 * Returns 1 if successful, 0 if signature does not match or -1 on error
 */
int libvsgpt_partition_table_header_read_file_io_handle(
     libvsgpt_partition_table_header_t *partition_table_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t block_data[ 512 ];

	static char *function = "libvsgpt_partition_table_header_read_file_io_handle";
	ssize_t read_count    = 0;
	int result            = 0;

	if( partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition table header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading partition table header at offset: %" PRIu64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset: %" PRIu64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              block_data,
	              512,
	              error );

	if( read_count != (ssize_t) 512 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition table header data.",
		 function );

		return( -1 );
	}
	result = libvsgpt_partition_table_header_read_data(
	          partition_table_header,
	          block_data,
	          512,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition table header.",
		 function );

		return( -1 );
	}
	return( result );
}

