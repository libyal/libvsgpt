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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvsgpt_libcerror.h"
#include "libvsgpt_partition_values.h"

/* Creates partition values
 * Make sure the value partition_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_initialize(
     libvsgpt_partition_values_t **partition_values,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_initialize";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( *partition_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition values value already set.",
		 function );

		return( -1 );
	}
	*partition_values = memory_allocate_structure(
	                     libvsgpt_partition_values_t );

	if( *partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *partition_values,
	     0,
	     sizeof( libvsgpt_partition_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear partition values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *partition_values != NULL )
	{
		memory_free(
		 *partition_values );

		*partition_values = NULL;
	}
	return( -1 );
}

/* Frees partition values
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_free(
     libvsgpt_partition_values_t **partition_values,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_free";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( *partition_values != NULL )
	{
		memory_free(
		 *partition_values );

		*partition_values = NULL;
	}
	return( 1 );
}

/* Retrieves the partition entry index
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_get_entry_index(
     libvsgpt_partition_values_t *partition_values,
     uint32_t *entry_index,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_get_entry_index";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( entry_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry index.",
		 function );

		return( -1 );
	}
	*entry_index = partition_values->entry_index;

	return( 1 );
}

/* Retrieves the identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_get_identifier(
     libvsgpt_partition_values_t *partition_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_get_identifier";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     partition_values->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the type identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_get_type_identifier(
     libvsgpt_partition_values_t *partition_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_get_type_identifier";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     partition_values->type_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy type identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the partition type
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_get_type(
     libvsgpt_partition_values_t *partition_values,
     uint8_t *type,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_get_type";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = partition_values->type;

	return( 1 );
}

/* Retrieves the partition offset
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_get_offset(
     libvsgpt_partition_values_t *partition_values,
     off64_t *offset,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_get_offset";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	*offset = partition_values->offset;

	return( 1 );
}

/* Retrieves the partition size
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_partition_values_get_size(
     libvsgpt_partition_values_t *partition_values,
     size64_t *size,
     libcerror_error_t **error )
{
	static char *function = "libvsgpt_partition_values_get_size";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = partition_values->size;

	return( 1 );
}

