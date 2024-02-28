/*
 * GUID Partition Table (GPT) partition entry definition
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

#if !defined( _VSGPT_PARTITION_ENTRY_H )
#define _VSGPT_PARTITION_ENTRY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vsgpt_partition_entry vsgpt_partition_entry_t;

struct vsgpt_partition_entry
{
	/* Partition type identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t type_identifier[ 16 ];

	/* Partition identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* Partition start block number
	 * Consists of 8 bytes
	 */
	uint8_t start_block_number[ 8 ];

	/* Partition end block number
	 * Consists of 8 bytes
	 */
	uint8_t end_block_number[ 8 ];

	/* Partition attribute flags
	 * Consists of 8 bytes
	 */
	uint8_t attribute_flags[ 8 ];

	/* Partition name
	 * Consists of 72 bytes
	 * Contains an UTF-16 little-endian string
	 */
	uint8_t name[ 72 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSGPT_PARTITION_ENTRY_H ) */

