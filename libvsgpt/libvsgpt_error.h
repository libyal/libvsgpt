/*
 * Error functions
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

#if !defined( _LIBVSGPT_INTERNAL_ERROR_H )
#define _LIBVSGPT_INTERNAL_ERROR_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if !defined( HAVE_LOCAL_LIBVSGPT )
#include <libvsgpt/error.h>
#endif

#include "libvsgpt_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBVSGPT )

LIBVSGPT_EXTERN \
void libvsgpt_error_free(
      libvsgpt_error_t **error );

LIBVSGPT_EXTERN \
int libvsgpt_error_fprint(
     libvsgpt_error_t *error,
     FILE *stream );

LIBVSGPT_EXTERN \
int libvsgpt_error_sprint(
     libvsgpt_error_t *error,
     char *string,
     size_t size );

LIBVSGPT_EXTERN \
int libvsgpt_error_backtrace_fprint(
     libvsgpt_error_t *error,
     FILE *stream );

LIBVSGPT_EXTERN \
int libvsgpt_error_backtrace_sprint(
     libvsgpt_error_t *error,
     char *string,
     size_t size );

#endif /* !defined( HAVE_LOCAL_LIBVSGPT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_INTERNAL_ERROR_H ) */

