/*
 * Info handle
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

#if !defined( _INFO_HANDLE_H )
#define _INFO_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "vsgpttools_libcerror.h"
#include "vsgpttools_libvsgpt.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct info_handle info_handle_t;

struct info_handle
{
	/* The libvsgpt input volume
	 */
	libvsgpt_volume_t *input_volume;

	/* The notification output stream
	 */
	FILE *notify_stream;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_guid_value_fprint(
     info_handle_t *info_handle,
     const char *value_name,
     const uint8_t *guid_data,
     libcerror_error_t **error );

int info_handle_partition_type_fprint(
     info_handle_t *info_handle,
     uint8_t partition_type,
     libcerror_error_t **error );

int info_handle_partition_fprint(
     info_handle_t *info_handle,
     libvsgpt_partition_t *partition,
     libcerror_error_t **error );

int info_handle_partitions_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _INFO_HANDLE_H ) */

