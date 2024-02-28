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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libvsgpt_boot_record.h"
#include "libvsgpt_debug.h"
#include "libvsgpt_definitions.h"
#include "libvsgpt_volume.h"
#include "libvsgpt_io_handle.h"
#include "libvsgpt_libbfio.h"
#include "libvsgpt_libcerror.h"
#include "libvsgpt_libcnotify.h"
#include "libvsgpt_libcthreads.h"
#include "libvsgpt_mbr_partition_entry.h"
#include "libvsgpt_partition.h"
#include "libvsgpt_partition_entry.h"
#include "libvsgpt_partition_table_header.h"
#include "libvsgpt_partition_values.h"
#include "libvsgpt_section_values.h"
#include "libvsgpt_types.h"

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_initialize(
     libvsgpt_volume_t **volume,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_initialize";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( *volume != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume value already set.",
		 function );

		return( -1 );
	}
	internal_volume = memory_allocate_structure(
	                   libvsgpt_internal_volume_t );

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volume.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_volume,
	     0,
	     sizeof( libvsgpt_internal_volume_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear volume.",
		 function );

		memory_free(
		 internal_volume );

		return( -1 );
	}
	if( libvsgpt_io_handle_initialize(
	     &( internal_volume->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_volume->partitions ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create partitions array.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_volume->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	*volume = (libvsgpt_volume_t *) internal_volume;

	return( 1 );

on_error:
	if( internal_volume != NULL )
	{
		if( internal_volume->io_handle != NULL )
		{
			libvsgpt_io_handle_free(
			 &( internal_volume->io_handle ),
			 NULL );
		}
		memory_free(
		 internal_volume );
	}
	return( -1 );
}

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_free(
     libvsgpt_volume_t **volume,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_free";
	int result                                  = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( *volume != NULL )
	{
		internal_volume = (libvsgpt_internal_volume_t *) *volume;

		if( internal_volume->file_io_handle != NULL )
		{
			if( libvsgpt_volume_close(
			     *volume,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close volume.",
				 function );

				result = -1;
			}
		}
		*volume = NULL;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_volume->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		if( libcdata_array_free(
		     &( internal_volume->partitions ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvsgpt_partition_values_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the partitions array.",
			 function );

			result = -1;
		}
		if( libvsgpt_io_handle_free(
		     &( internal_volume->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_volume );
	}
	return( result );
}

/* Signals the volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_signal_abort(
     libvsgpt_volume_t *volume,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_signal_abort";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_volume->io_handle->abort = 1;

	return( 1 );
}

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_open(
     libvsgpt_volume_t *volume,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_open";
	size_t filename_length                      = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSGPT_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSGPT_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSGPT_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libvsgpt_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume: %s.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_volume->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_open_wide(
     libvsgpt_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_open_wide";
	size_t filename_length                      = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSGPT_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSGPT_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSGPT_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libvsgpt_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume: %ls.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_volume->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a volume using a Basic File IO (bfio) volume
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_open_file_io_handle(
     libvsgpt_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_open_file_io_handle";
	uint8_t file_io_handle_opened_in_library    = 0;
	int bfio_access_flags                       = 0;
	int file_io_handle_is_open                  = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( internal_volume->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume - file IO handle value already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSGPT_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSGPT_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSGPT_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSGPT_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libvsgpt_internal_volume_open_read(
	     internal_volume,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_volume->file_io_handle                   = file_io_handle;
	internal_volume->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
int libvsgpt_volume_close(
     libvsgpt_volume_t *volume,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_close";
	int result                                  = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( internal_volume->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_volume->file_io_handle_created_in_library != 0 )
		{
			if( libvsgpt_debug_print_read_offsets(
			     internal_volume->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_volume->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_volume->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_volume->file_io_handle_opened_in_library = 0;
	}
	if( internal_volume->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_volume->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_volume->file_io_handle_created_in_library = 0;
	}
	internal_volume->file_io_handle = NULL;

	if( libvsgpt_io_handle_clear(
	     internal_volume->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear the IO handle.",
		 function );

		result = -1;
	}
	if( libvsgpt_partition_table_header_free(
	     &( internal_volume->partition_table_header ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free partition table header.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_volume->partitions,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvsgpt_partition_values_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to empty the partitions array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Opens a volume for reading
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_internal_volume_open_read(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libvsgpt_boot_record_t *master_boot_record = NULL;
	static char *function                      = "libvsgpt_internal_volume_open_read";
	off64_t file_offset                        = 0;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( internal_volume->size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size from file IO handle.",
		 function );

		goto on_error;
	}
	if( libvsgpt_internal_volume_read_partition_table_headers(
	     internal_volume,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition table header and backup.",
		 function );

		goto on_error;
	}
	if( internal_volume->partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing partition table header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading GUID Partition Table (GPT) entries.\n",
		 function );
	}
#endif
	file_offset = internal_volume->partition_table_header->partition_entries_start_block_number * internal_volume->io_handle->bytes_per_sector;

	if( libvsgpt_internal_volume_read_partition_entries(
	     internal_volume,
	     file_io_handle,
	     file_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition entries.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading Master Boot Record (MBR).\n",
		 function );
	}
#endif
	if( libvsgpt_boot_record_initialize(
	     &master_boot_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create master boot record.",
		 function );

		goto on_error;
	}
	if( libvsgpt_boot_record_read_file_io_handle(
	     master_boot_record,
	     file_io_handle,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read master boot record.",
		 function );

		goto on_error;
	}
	if( libvsgpt_internal_volume_read_mbr_partition_entries(
	     internal_volume,
	     file_io_handle,
	     0,
	     master_boot_record,
	     1,
	     0,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition entries.",
		 function );

		goto on_error;
	}
	if( libvsgpt_boot_record_free(
	     &master_boot_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free master boot record.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( master_boot_record != NULL )
	{
		libvsgpt_boot_record_free(
		 &master_boot_record,
		 NULL );
	}
	if( internal_volume->partition_table_header != NULL )
	{
		libvsgpt_partition_table_header_free(
		 &( internal_volume->partition_table_header ),
		 NULL );
	}
	return( -1 );
}

/* Reads the partition table header and the backup
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_internal_volume_read_partition_table_headers(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libvsgpt_partition_table_header_t *backup_partition_table_header = NULL;
	libvsgpt_partition_table_header_t *partition_table_header        = NULL;
	static char *function                                            = "libvsgpt_internal_volume_read_partition_table_headers";
	off64_t file_offset                                              = 0;
	int result                                                       = 0;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( internal_volume->partition_table_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume - partition table header already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading GUID Partition Table (GPT) header.\n",
		 function );
	}
#endif
	if( libvsgpt_partition_table_header_initialize(
	     &partition_table_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create partition table header.",
		 function );

		goto on_error;
	}
	internal_volume->io_handle->bytes_per_sector = 512;

	result = libvsgpt_partition_table_header_read_file_io_handle(
	          partition_table_header,
	          file_io_handle,
	          (off64_t) internal_volume->io_handle->bytes_per_sector,
	          error );

	while( ( result == 0 )
	    && ( internal_volume->io_handle->bytes_per_sector < 4096 ) )
	{
		internal_volume->io_handle->bytes_per_sector *= 2;

		result = libvsgpt_partition_table_header_read_file_io_handle(
		          partition_table_header,
		          file_io_handle,
		          (off64_t) internal_volume->io_handle->bytes_per_sector,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition table header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: bytes per sector\t: %" PRIzd ".\n",
		 function,
		 internal_volume->io_handle->bytes_per_sector );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( partition_table_header->partition_header_block_number != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: unsupported partition table header block number: %" PRIu64 ".",
		 function,
		 partition_table_header->partition_header_block_number );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading backup GUID Partition Table (GPT) header.\n",
		 function );
	}
#endif
	if( libvsgpt_partition_table_header_initialize(
	     &backup_partition_table_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create backup partition table header.",
		 function );

		goto on_error;
	}
	result      = 0;
	file_offset = partition_table_header->backup_partition_header_block_number * internal_volume->io_handle->bytes_per_sector;

	if( file_offset > 0 )
	{
		result = libvsgpt_partition_table_header_read_file_io_handle(
		          backup_partition_table_header,
		          file_io_handle,
		          file_offset,
		          error );
	}
	if( ( result == 0 )
	 || ( file_offset == 0 ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: invalid backup partition header block number fallback to last block.\n",
			 function );
		}
#endif
		file_offset = internal_volume->size - internal_volume->io_handle->bytes_per_sector;

		result = libvsgpt_partition_table_header_read_file_io_handle(
		          backup_partition_table_header,
		          file_io_handle,
		          file_offset,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read backup partition table header.",
		 function );

		goto on_error;
	}
	if( ( partition_table_header->is_corrupt != 0 )
	 && ( backup_partition_table_header->is_corrupt != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_INPUT,
		 LIBCERROR_INPUT_ERROR_INVALID_DATA,
		 "%s: partition table header and backup are both corrupt.",
		 function );

		goto on_error;
	}
	if( ( partition_table_header->is_corrupt != 0 )
	 || ( backup_partition_table_header->is_corrupt != 0 ) )
	{
		internal_volume->is_corrupt = 1;
	}
	else
	{
		if( partition_table_header->partition_header_block_number != backup_partition_table_header->backup_partition_header_block_number )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of partition table header block number.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
		if( partition_table_header->backup_partition_header_block_number != backup_partition_table_header->partition_header_block_number )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of backup partition table header block number.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
		if( partition_table_header->partition_area_start_block_number != backup_partition_table_header->partition_area_start_block_number )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of partition area start block number.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
		if( partition_table_header->partition_area_end_block_number != backup_partition_table_header->partition_area_end_block_number )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of partition area end block number.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
		if( memory_compare(
		     partition_table_header->disk_identifier,
		     backup_partition_table_header->disk_identifier,
		     16 ) != 0 )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of disk identifier.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
		/* The partition entries start block number will be different
		 */
		if( partition_table_header->number_of_partition_entries != backup_partition_table_header->number_of_partition_entries )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of number of partition entries.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
		if( partition_table_header->partition_entry_data_size != backup_partition_table_header->partition_entry_data_size )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of partition entry data size.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
		if( partition_table_header->partition_entries_data_checksum != backup_partition_table_header->partition_entries_data_checksum )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch of partition entries data checksum.\n",
				 function );
			}
#endif
			internal_volume->is_corrupt = 1;
		}
	}
	if( partition_table_header->is_corrupt != 0 )
	{
		if( libvsgpt_partition_table_header_free(
		     &partition_table_header,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free partition table header.",
			 function );

			goto on_error;
		}
		internal_volume->partition_table_header = backup_partition_table_header;
	}
	else
	{
		if( libvsgpt_partition_table_header_free(
		     &backup_partition_table_header,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free backup partition table header.",
			 function );

			goto on_error;
		}
		internal_volume->partition_table_header = partition_table_header;
	}
	return( 1 );

on_error:
	if( backup_partition_table_header != NULL )
	{
		libvsgpt_partition_table_header_free(
		 &backup_partition_table_header,
		 NULL );
	}
	if( partition_table_header != NULL )
	{
		libvsgpt_partition_table_header_free(
		 &partition_table_header,
		 NULL );
	}
	return( -1 );
}

/* Reads partition entries
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_internal_volume_read_partition_entries(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t *empty_partition_type[ 16 ]           = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	libvsgpt_partition_entry_t *partition_entry   = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	uint8_t *partition_entries_data               = NULL;
	static char *function                         = "libvsgpt_internal_volume_read_partition_entries";
	size_t data_offset                            = 0;
	size_t partition_entries_data_size            = 0;
	ssize_t read_count                            = 0;
	uint32_t maximum_number_of_partition_entries  = 0;
	uint32_t partition_entry_index                = 0;
	int entry_index                               = 0;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( internal_volume->partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing partition table header.",
		 function );

		return( -1 );
	}
#if ( SIZEOF_SIZE_T <= 4 )
	if( ( internal_volume->partition_table_header->partition_entry_data_size < 128 )
	 || ( internal_volume->partition_table_header->partition_entry_data_size > (size_t) SSIZE_MAX ) )
#else
	if( internal_volume->partition_table_header->partition_entry_data_size < 128 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid volume - invalid partition table table header - partition entry data size value out of bounds.",
		 function );

		return( -1 );
	}
	maximum_number_of_partition_entries = ( 32 * internal_volume->io_handle->bytes_per_sector ) / internal_volume->partition_table_header->partition_entry_data_size;

	if( internal_volume->partition_table_header->number_of_partition_entries > maximum_number_of_partition_entries )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid volume - invalid partition table table header - number of partition entries value out of bounds.",
		 function );

		return( -1 );
	}
	partition_entries_data_size = (size_t) internal_volume->partition_table_header->partition_entry_data_size * (size_t) internal_volume->partition_table_header->number_of_partition_entries;

	if( partition_entries_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid partition entries data size value out of bounds.",
		 function );

		return( -1 );
	}
	partition_entries_data = (uint8_t *) memory_allocate(
	                                      sizeof( uint8_t ) * partition_entries_data_size );

	if( partition_entries_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition entries data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading partition entries at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              partition_entries_data,
	              partition_entries_data_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) partition_entries_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition entries data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: partition entries data:\n",
		 function );
		libcnotify_print_data(
		 partition_entries_data,
		 partition_entries_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libvsgpt_partition_entry_initialize(
	     &partition_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create partition entry.",
		 function );

		goto on_error;
	}
	for( partition_entry_index = 0;
	     partition_entry_index < internal_volume->partition_table_header->number_of_partition_entries;
	     partition_entry_index++ )
	{
		if( libvsgpt_partition_entry_read_data(
		     partition_entry,
		     &( partition_entries_data[ data_offset ] ),
		     internal_volume->partition_table_header->partition_entry_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read partition entry data.",
			 function );

			goto on_error;
		}
		data_offset += internal_volume->partition_table_header->partition_entry_data_size;

		/* Ignore empty partition entries
		 */
		if( memory_compare(
		     partition_entry->type_identifier,
		     empty_partition_type,
		     16 ) == 0 )
		{
			continue;
		}
		if( libvsgpt_partition_values_initialize(
		     &partition_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create partition values.",
			 function );

			goto on_error;
		}
/* TODO refactor to libvsgtp_partition_values_copy_from_partition_entry */
		if( memory_copy(
		     partition_values->type_identifier,
		     partition_entry->type_identifier,
		     16 ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to copy type identifier.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     partition_values->identifier,
		     partition_entry->identifier,
		     16 ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to copy identifier.",
			 function );

			goto on_error;
		}
		if( ( partition_entry->start_block_number < internal_volume->partition_table_header->partition_area_start_block_number )
		 || ( partition_entry->start_block_number >= (uint64_t) ( internal_volume->size / internal_volume->io_handle->bytes_per_sector ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid partition entry - start block number value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( partition_entry->end_block_number < partition_entry->start_block_number )
		 || ( partition_entry->end_block_number > (uint64_t) ( internal_volume->size / internal_volume->io_handle->bytes_per_sector ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid partition entry - end block number value out of bounds.",
			 function );

			goto on_error;
		}
		partition_values->entry_index = partition_entry_index;
		partition_values->offset      = (off64_t) ( partition_entry->start_block_number * internal_volume->io_handle->bytes_per_sector );
		partition_values->size        = (size64_t) ( ( partition_entry->end_block_number - partition_entry->start_block_number + 1 ) * internal_volume->io_handle->bytes_per_sector );

		if( libcdata_array_append_entry(
		     internal_volume->partitions,
		     &entry_index,
		     (intptr_t *) partition_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append partition to array.",
			 function );

			goto on_error;
		}
		partition_values = NULL;
	}
	if( libvsgpt_partition_entry_free(
	     &partition_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free partition entry.",
		 function );

		goto on_error;
	}
	memory_free(
	 partition_entries_data );

	return( 1 );

on_error:
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	if( partition_entry != NULL )
	{
		libvsgpt_partition_entry_free(
		 &partition_entry,
		 NULL );
	}
	if( partition_entries_data != NULL )
	{
		memory_free(
		 partition_entries_data );
	}
	return( -1 );
}

/* Reads partition entries in a master boot record or extended partition record
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_internal_volume_read_mbr_partition_entries(
     libvsgpt_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libvsgpt_boot_record_t *boot_record,
     uint8_t is_master_boot_record,
     off64_t first_extended_boot_record_offset,
     int recursion_depth,
     libcerror_error_t **error )
{
	libvsgpt_boot_record_t *extended_partition_record = NULL;
	libvsgpt_mbr_partition_entry_t *partition_entry   = NULL;
	libvsgpt_partition_values_t *partition_values     = NULL;
	static char *function                             = "libvsgpt_internal_volume_read_mbr_partition_entries";
	off64_t extended_partition_record_offset          = 0;
	int partition_entry_index                         = 0;
	int result                                        = 0;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( ( recursion_depth < 0 )
	 || ( recursion_depth > LIBVSGPT_MAXIMUM_RECURSION_DEPTH ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid recursion depth value out of bounds.",
		 function );

		return( -1 );
	}
	for( partition_entry_index = 0;
	     partition_entry_index < 4;
	     partition_entry_index++ )
	{
		if( libvsgpt_boot_record_get_partition_entry_by_index(
		     boot_record,
		     partition_entry_index,
		     &partition_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve partition entry: %d.",
			 function,
			 partition_entry_index );

			goto on_error;
		}
		if( partition_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing partition entry: %" PRIu8 ".",
			 function,
			 partition_entry_index );

			goto on_error;
		}
		/* Ignore empty partition entries
		 */
		if( partition_entry->type == 0 )
		{
			continue;
		}
		if( ( partition_entry->type == 0x05 )
		 || ( ( is_master_boot_record != 0 )
		  &&  ( partition_entry->type == 0x0f ) ) )
		{
			if( extended_partition_record != NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: more than 1 extended partition entry per table is not supported.",
				 function );

				goto on_error;
			}
			extended_partition_record_offset = first_extended_boot_record_offset + ( (off64_t) partition_entry->start_address_lba * internal_volume->io_handle->bytes_per_sector );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: reading Extended Partition Record (EPR) at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
				 function,
				 extended_partition_record_offset,
				 extended_partition_record_offset );
			}
#endif
			if( libvsgpt_boot_record_initialize(
			     &extended_partition_record,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create extended partition record.",
				 function );

				goto on_error;
			}
			result = libvsgpt_boot_record_read_file_io_handle(
				  extended_partition_record,
				  file_io_handle,
				  extended_partition_record_offset,
				  error );

			/* Linux fdisk supports sector sizes of: 512, 1024, 2048, 4096
			 */
			while( ( result != 1 )
			    && ( is_master_boot_record != 0 )
			    && ( internal_volume->io_handle->bytes_per_sector <= 4096 ) )
			{
				libcerror_error_free(
				 error );

				internal_volume->io_handle->bytes_per_sector *= 2;

				extended_partition_record_offset = (off64_t) partition_entry->start_address_lba * internal_volume->io_handle->bytes_per_sector;

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: reading Extended Partition Record (EPR) at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
					 function,
					 extended_partition_record_offset,
					 extended_partition_record_offset );
				}
#endif
				result = libvsgpt_boot_record_read_file_io_handle(
					  extended_partition_record,
					  file_io_handle,
					  extended_partition_record_offset,
					  error );
			}
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read extended partition record.",
				 function );

				goto on_error;
			}
		}
		else
		{
/* TODO do bytes per sector check for known volume types and GPT */

#ifdef TODO
			if( libvsgpt_partition_values_initialize(
			     &partition_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create partition values.",
				 function );

				goto on_error;
			}
			partition_values->type = partition_entry->type;

			partition_values->offset = first_extended_boot_record_offset + ( (off64_t) partition_entry->start_address_lba * internal_volume->io_handle->bytes_per_sector );
			partition_values->size   = partition_entry->number_of_sectors * internal_volume->io_handle->bytes_per_sector;

/* TODO offset and size sanity check */

			if( libcdata_array_append_entry(
			     internal_volume->partitions,
			     &entry_index,
			     (intptr_t *) partition_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append partition to array.",
				 function );

				goto on_error;
			}
			partition_values = NULL;
#endif /* TODO */
		}
	}
	if( extended_partition_record != NULL )
	{
		if( ( extended_partition_record_offset == 0 )
		 || ( extended_partition_record_offset == file_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: unsupported extended partition record offset.",
			 function );

			goto on_error;
		}
		if( is_master_boot_record != 0 )
		{
			first_extended_boot_record_offset = extended_partition_record_offset;
		}
		if( libvsgpt_internal_volume_read_mbr_partition_entries(
		     internal_volume,
		     file_io_handle,
		     extended_partition_record_offset,
		     extended_partition_record,
		     0,
		     first_extended_boot_record_offset,
		     recursion_depth + 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read partition entries.",
			 function );

			goto on_error;
		}
		if( libvsgpt_boot_record_free(
		     &extended_partition_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extended partition record.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( partition_values != NULL )
	{
		libvsgpt_partition_values_free(
		 &partition_values,
		 NULL );
	}
	if( extended_partition_record != NULL )
	{
		libvsgpt_boot_record_free(
		 &extended_partition_record,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_get_bytes_per_sector(
     libvsgpt_volume_t *volume,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_get_bytes_per_sector";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	if( bytes_per_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bytes per sector.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*bytes_per_sector = internal_volume->io_handle->bytes_per_sector;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the disk identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_get_disk_identifier(
     libvsgpt_volume_t *volume,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_get_disk_identifier";
	int result                                  = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( internal_volume->partition_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing partition table header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libvsgpt_partition_table_header_get_disk_identifier(
	     internal_volume->partition_table_header,
	     guid_data,
	     guid_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve disk identifier.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the number of partitions
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_get_number_of_partitions(
     libvsgpt_volume_t *volume,
     int *number_of_partitions,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsgpt_volume_get_number_of_partitions";
	int result                                  = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libcdata_array_get_number_of_entries(
	     internal_volume->partitions,
	     number_of_partitions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of partitions from array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves a specific partition
 * Returns 1 if successful or -1 on error
 */
int libvsgpt_volume_get_partition_by_index(
     libvsgpt_volume_t *volume,
     int partition_index,
     libvsgpt_partition_t **partition,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume   = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	static char *function                         = "libvsgpt_volume_get_partition_by_index";
	int result                                    = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( partition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition.",
		 function );

		return( -1 );
	}
	if( *partition != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libcdata_array_get_entry_by_index(
	     internal_volume->partitions,
	     partition_index,
	     (intptr_t **) &partition_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition values: %d from array.",
		 function,
		 partition_index );

		result = -1;
	}
	else
	{
		if( libvsgpt_partition_initialize(
		     partition,
		     internal_volume->file_io_handle,
		     partition_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create partition: %d.",
			 function,
			 partition_index );

			result = -1;
		}
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		result = -1;
	}
#endif
	if( result == -1 )
	{
		goto on_error;
	}
	return( 1 );

on_error:
	if( *partition != NULL )
	{
		libvsgpt_partition_free(
		 partition,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the partition values with the corresponding (partition) entry index
 * This function is not multi-thread safe acquire read lock before call
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libvsgpt_internal_volume_get_partition_values_by_identifier(
     libvsgpt_internal_volume_t *internal_volume,
     uint32_t entry_index,
     libvsgpt_partition_values_t **partition_values,
     libcerror_error_t **error )
{
	libvsgpt_partition_values_t *safe_partition_values = NULL;
	static char *function                              = "libvsgpt_internal_volume_get_partition_values_by_identifier";
	uint32_t safe_entry_index                          = 0;
	int number_of_partitions                           = 0;
	int partition_index                                = 0;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
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
	if( libcdata_array_get_number_of_entries(
	     internal_volume->partitions,
	     &number_of_partitions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of partitions from array.",
		 function );

		return( -1 );
	}
	for( partition_index = 0;
	     partition_index < number_of_partitions;
	     partition_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_volume->partitions,
		     partition_index,
		     (intptr_t **) &safe_partition_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve partition values: %d from array.",
			 function,
			 partition_index );

			return( -1 );
		}
		if( libvsgpt_partition_values_get_entry_index(
		     safe_partition_values,
		     &safe_entry_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry index from partition values: %d.",
			 function,
			 partition_index );

			return( -1 );
		}
		if( safe_entry_index == entry_index )
		{
			*partition_values = safe_partition_values;

			return( 1 );
		}
	}
	return( 0 );
}

/* Determines if the volume contains a partition with the corresponding (partition) entry index
 * Returns 1 if the volume contains such a partition, 0 if not or -1 on error
 */
int libvsgpt_volume_has_partition_with_identifier(
     libvsgpt_volume_t *volume,
     uint32_t entry_index,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume   = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	static char *function                         = "libvsgpt_volume_has_partition_with_identifier";
	int result                                    = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	result = libvsgpt_internal_volume_get_partition_values_by_identifier(
	          internal_volume,
	          entry_index,
	          &partition_values,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition values.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the partition with the corresponding (partition) entry index
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libvsgpt_volume_get_partition_by_identifier(
     libvsgpt_volume_t *volume,
     uint32_t entry_index,
     libvsgpt_partition_t **partition,
     libcerror_error_t **error )
{
	libvsgpt_internal_volume_t *internal_volume   = NULL;
	libvsgpt_partition_values_t *partition_values = NULL;
	static char *function                         = "libvsgpt_volume_get_partition_by_identifier";
	int result                                    = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsgpt_internal_volume_t *) volume;

	if( partition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition.",
		 function );

		return( -1 );
	}
	if( *partition != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	result = libvsgpt_internal_volume_get_partition_values_by_identifier(
	          internal_volume,
	          entry_index,
	          &partition_values,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition values.",
		 function );

		result = -1;
	}
	else if( result != 0 )
	{
		if( libvsgpt_partition_initialize(
		     partition,
		     internal_volume->file_io_handle,
		     partition_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create partition.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBVSGPT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		result = -1;
	}
#endif
	if( result == -1 )
	{
		goto on_error;
	}
	return( result );

on_error:
	if( *partition != NULL )
	{
		libvsgpt_partition_free(
		 partition,
		 NULL );
	}
	return( -1 );
}

