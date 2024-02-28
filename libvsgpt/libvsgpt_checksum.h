/*
 * Checksum functions
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

#if !defined( _LIBVSGPT_CHECKSUM_H )
#define _LIBVSGPT_CHECKSUM_H

#include <common.h>
#include <types.h>

#include "libvsgpt_extern.h"
#include "libvsgpt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBVSGPT_EXTERN_VARIABLE \
uint32_t libvsgpt_checksum_crc32_table[ 256 ];

LIBVSGPT_EXTERN_VARIABLE \
int libvsgpt_checksum_crc32_table_computed;

void libvsgpt_checksum_initialize_crc32_table(
      int );

int libvsgpt_checksum_calculate_crc32(
     uint32_t *checksum,
     const uint8_t *buffer,
     size_t size,
     uint32_t initial_value,
     libcerror_error_t **error );

int libvsgpt_checksum_calculate_weak_crc32(
     uint32_t *checksum,
     const uint8_t *buffer,
     size_t size,
     uint32_t initial_value,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_CHECKSUM_H ) */

