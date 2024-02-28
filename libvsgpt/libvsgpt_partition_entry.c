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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvsgpt_debug.h"
#include "libvsgpt_definitions.h"
#include "libvsgpt_libcerror.h"
#include "libvsgpt_libcnotify.h"
#include "libvsgpt_libfguid.h"
#include "libvsgpt_libuna.h"
#include "libvsgpt_partition_entry.h"
#include "libvsgpt_partition_type_identifier.h"
#include "libvsgpt_types.h"

#include "vsgpt_partition_entry.h"

/* Creates a partition entry
 * Make sure the value partition_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_entry_initialize(
     libvsgpt_partition_entry_t **partition_entry,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_entry_initialize";

	if( partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition entry.",
		 function );

		return( -1 );
	}
	if( *partition_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition entry value already set.",
		 function );

		return( -1 );
	}
	*partition_entry = memory_allocate_structure(
	                    libvsgpt_partition_entry_t );

	if( *partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *partition_entry,
	     0,
	     sizeof( libvsgpt_partition_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear partition entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *partition_entry != NULL )
	{
		memory_free(
		 *partition_entry );

		*partition_entry = NULL;
	}
	return( -1 );
}

/* Frees a partition entry
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_entry_free(
     libvsgpt_partition_entry_t **partition_entry,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_entry_free";

	if( partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition entry.",
		 function );

		return( -1 );
	}
	if( *partition_entry != NULL )
	{
		memory_free(
		 *partition_entry );

		*partition_entry = NULL;
	}
	return( 1 );
}

/* Checks if a buffer containing the partition entry is filled with same value bytes (empty-block)
 * Returns 1 if a pattern was found, 0 if not or -1 on error
 */
int libvsgpt_partition_entry_check_for_empty_block(
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libvsgpt_aligned_t *aligned_data_index = NULL;
	libvsgpt_aligned_t *aligned_data_start = NULL;
	uint8_t *data_index                    = NULL;
	uint8_t *data_start                    = NULL;
	static char *function                  = "libvsgpt_partition_entry_check_for_empty_block";

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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	data_start = (uint8_t *) data;
	data_index = (uint8_t *) data + 1;
	data_size -= 1;

	/* Only optimize for data larger than the alignment
	 */
	if( data_size > ( 2 * sizeof( libvsgpt_aligned_t ) ) )
	{
		/* Align the data start
		 */
		while( ( (intptr_t) data_start % sizeof( libvsgpt_aligned_t ) ) != 0 )
		{
			if( *data_start != *data_index )
			{
				return( 0 );
			}
			data_start += 1;
			data_index += 1;
			data_size  -= 1;
		}
		/* Align the data index
		 */
		while( ( (intptr_t) data_index % sizeof( libvsgpt_aligned_t ) ) != 0 )
		{
			if( *data_start != *data_index )
			{
				return( 0 );
			}
			data_index += 1;
			data_size  -= 1;
		}
		aligned_data_start = (libvsgpt_aligned_t *) data_start;
		aligned_data_index = (libvsgpt_aligned_t *) data_index;

		while( data_size > sizeof( libvsgpt_aligned_t ) )
		{
			if( *aligned_data_start != *aligned_data_index )
			{
				return( 0 );
			}
			aligned_data_index += 1;
			data_size          -= sizeof( libvsgpt_aligned_t );
		}
		data_index = (uint8_t *) aligned_data_index;
	}
	while( data_size != 0 )
	{
		if( *data_start != *data_index )
		{
			return( 0 );
		}
		data_index += 1;
		data_size  -= 1;
	}
	return( 1 );
}

/* Reads a partition entry
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_entry_read_data(
     libvsgpt_partition_entry_t *partition_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_entry_read_data";

	if( partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition entry.",
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
	if( ( data_size < sizeof( vsgpt_partition_entry_t) )
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
		 "%s: entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_copy(
	     partition_entry->type_identifier,
	     ( (vsgpt_partition_entry_t *) data )->type_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to copy type identifier.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     partition_entry->identifier,
	     ( (vsgpt_partition_entry_t *) data )->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 ( (vsgpt_partition_entry_t *) data )->start_block_number,
	 partition_entry->start_block_number );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vsgpt_partition_entry_t *) data )->end_block_number,
	 partition_entry->end_block_number );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vsgpt_partition_entry_t *) data )->attribute_flags,
	 partition_entry->attribute_flags );

	if( memory_copy(
	     partition_entry->name,
	     ( (vsgpt_partition_entry_t *) data )->name,
	     72 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to copy name.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libvsgpt_debug_print_guid_value(
		     function,
		     "type identifier\t\t\t",
		     ( (vsgpt_partition_entry_t *) data )->type_identifier,
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
		libcnotify_printf(
		 "%s: type identifier description\t\t: %s\n",
		 function,
		 libvsgpt_partition_type_identifier_get_description(
		  ( (vsgpt_partition_entry_t *) data )->type_identifier ) );

		if( libvsgpt_debug_print_guid_value(
		     function,
		     "identifier\t\t\t\t",
		     ( (vsgpt_partition_entry_t *) data )->identifier,
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
		libcnotify_printf(
		 "%s: start block number\t\t\t: %" PRIu64 "\n",
		 function,
		 partition_entry->start_block_number );

		libcnotify_printf(
		 "%s: end block number\t\t\t: %" PRIu64 "\n",
		 function,
		 partition_entry->end_block_number );

		libcnotify_printf(
		 "%s: attribute flags\t\t\t: %" PRIu64 "\n",
		 function,
		 partition_entry->attribute_flags );

		if( libvsgpt_debug_print_utf16_string_value(
		     function,
		     "name\t\t\t\t",
		     ( (vsgpt_partition_entry_t *) data )->name,
		     72,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print UTF-16 string value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

