/*
 * Cylinder Head Sector (CHS) address functions
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

#if !defined( _LIBVSGPT_CHS_ADDRESS_H )
#define _LIBVSGPT_CHS_ADDRESS_H

#include <common.h>
#include <types.h>

#include "libvsgpt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsgpt_chs_address libvsgpt_chs_address_t;

struct libvsgpt_chs_address
{
	/* The cylinder
	 */
	uint16_t cylinder;

	/* The head
	 */
	uint8_t head;

	/* The sector
	 */
	uint8_t sector;
};

int libvsgpt_chs_address_initialize(
     libvsgpt_chs_address_t **chs_address,
     libcerror_error_t **error );

int libvsgpt_chs_address_free(
     libvsgpt_chs_address_t **chs_address,
     libcerror_error_t **error );

int libvsgpt_chs_address_copy_from_byte_stream(
     libvsgpt_chs_address_t *chs_address,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_CHS_ADDRESS_H ) */

