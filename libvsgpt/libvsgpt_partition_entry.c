/*
 * The partition entry functions
 *
 * Copyright (C) 2019-2020, Joachim Metz <joachim.metz@gmail.com>
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
		 0 );
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

