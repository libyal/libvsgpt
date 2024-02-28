/*
 * Python object wrapper of libvsgpt_partition_t
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

#if !defined( _PYVSGPT_PARTITION_H )
#define _PYVSGPT_PARTITION_H

#include <common.h>
#include <types.h>

#include "pyvsgpt_libvsgpt.h"
#include "pyvsgpt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsgpt_partition pyvsgpt_partition_t;

struct pyvsgpt_partition
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvsgpt partition
	 */
	libvsgpt_partition_t *partition;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyvsgpt_partition_object_methods[];
extern PyTypeObject pyvsgpt_partition_type_object;

PyObject *pyvsgpt_partition_new(
           libvsgpt_partition_t *partition,
           PyObject *parent_object );

int pyvsgpt_partition_init(
     pyvsgpt_partition_t *pyvsgpt_partition );

void pyvsgpt_partition_free(
      pyvsgpt_partition_t *pyvsgpt_partition );

PyObject *pyvsgpt_partition_read_buffer(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsgpt_partition_read_buffer_at_offset(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsgpt_partition_seek_offset(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsgpt_partition_get_offset(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments );

PyObject *pyvsgpt_partition_get_size(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments );

PyObject *pyvsgpt_partition_get_entry_index(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments );

PyObject *pyvsgpt_partition_get_identifier(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments );

PyObject *pyvsgpt_partition_get_type_identifier(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments );

PyObject *pyvsgpt_partition_get_type(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments );

PyObject *pyvsgpt_partition_get_volume_offset(
           pyvsgpt_partition_t *pyvsgpt_partition,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSGPT_PARTITION_H ) */

