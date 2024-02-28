/*
 * The IO handle functions
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

#if !defined( _LIBVSGPT_IO_HANDLE_H )
#define _LIBVSGPT_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvsgpt_libbfio.h"
#include "libvsgpt_libcdata.h"
#include "libvsgpt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_io_handle libvsgpt_io_handle_t;

struct libvsgpt_io_handle
{
	/* The number of bytes per sector
	 */
	size_t bytes_per_sector;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libvsgpt_io_handle_initialize(
     libvsgpt_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvsgpt_io_handle_free(
     libvsgpt_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvsgpt_io_handle_clear(
     libvsgpt_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_IO_HANDLE_H ) */

