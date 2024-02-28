/*
 * Python object wrapper of libvsgpt_volume_t
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

#if !defined( _PYVSGPT_VOLUME_H )
#define _PYVSGPT_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyvsgpt_libbfio.h"
#include "pyvsgpt_libvsgpt.h"
#include "pyvsgpt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsgpt_volume pyvsgpt_volume_t;

struct pyvsgpt_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvsgpt volume
	 */
	libvsgpt_volume_t *volume;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyvsgpt_volume_object_methods[];
extern PyTypeObject pyvsgpt_volume_type_object;

int pyvsgpt_volume_init(
     pyvsgpt_volume_t *pyvsgpt_volume );

void pyvsgpt_volume_free(
      pyvsgpt_volume_t *pyvsgpt_volume );

PyObject *pyvsgpt_volume_signal_abort(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments );

PyObject *pyvsgpt_volume_open(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsgpt_volume_open_file_object(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsgpt_volume_close(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments );

PyObject *pyvsgpt_volume_get_bytes_per_sector(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments );

PyObject *pyvsgpt_volume_get_number_of_partitions(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments );

PyObject *pyvsgpt_volume_get_partition_by_index(
           PyObject *pyvsgpt_volume,
           int partition_index );

PyObject *pyvsgpt_volume_get_partition(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsgpt_volume_get_partitions(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments );

PyObject *pyvsgpt_volume_has_partition_with_identifier(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsgpt_volume_get_partition_by_identifier(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSGPT_VOLUME_H ) */

