/*
 * GUID Partition Table (GPT) partition table definitions
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

#if !defined( _VSGPT_PARTITION_TABLE_H )
#define _VSGPT_PARTITION_TABLE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vsgpt_partition_table_header vsgpt_partition_table_header_t;

struct vsgpt_partition_table_header
{
	/* Signature
	 * Consists of 8 bytes
	 * Contains "EFI PART"
	 */
	uint8_t signature[ 8 ];

	/* Minor format version
	 * Consists of 2 bytes
	 */
	uint8_t minor_format_version[ 2 ];

	/* Major format version
	 * Consists of 2 bytes
	 */
	uint8_t major_format_version[ 2 ];

	/* Header data size
	 * Consists of 4 bytes
	 */
	uint8_t header_data_size[ 4 ];

	/* Header data checksum
	 * Consists of 4 bytes
	 */
	uint8_t header_data_checksum[ 4 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Partition header block number
	 * Consists of 8 bytes
	 */
	uint8_t header_block_number[ 8 ];

	/* Backup partition header block number
	 * Consists of 8 bytes
	 */
	uint8_t backup_header_block_number[ 8 ];

	/* Partition area start block number
	 * Consists of 8 bytes
	 */
	uint8_t area_start_block_number[ 8 ];

	/* Partition area end block number
	 * Consists of 8 bytes
	 */
	uint8_t area_end_block_number[ 8 ];

	/* Disk identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t disk_identifier[ 16 ];

	/* Partition entries start block number
	 * Consists of 8 bytes
	 */
	uint8_t entries_start_block_number[ 8 ];

	/* Number of partition entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* Partition entry data size
	 * Consists of 4 bytes
	 */
	uint8_t entry_data_size[ 4 ];

	/* Partition entries data checksum
	 * Consists of 4 bytes
	 */
	uint8_t entries_data_checksum[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSGPT_PARTITION_TABLE_H ) */

