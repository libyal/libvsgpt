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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvsgpt_error.h"
#include "pyvsgpt_file_object_io_handle.h"
#include "pyvsgpt_volume.h"
#include "pyvsgpt_libbfio.h"
#include "pyvsgpt_libcerror.h"
#include "pyvsgpt_libvsgpt.h"
#include "pyvsgpt_partition.h"
#include "pyvsgpt_partitions.h"
#include "pyvsgpt_python.h"
#include "pyvsgpt_unused.h"

#if !defined( LIBVSGPT_HAVE_BFIO )

LIBVSGPT_EXTERN \
int libvsgpt_volume_open_file_io_handle(
     libvsgpt_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsgpt_error_t **error );

#endif /* !defined( LIBVSGPT_HAVE_BFIO ) */

PyMethodDef pyvsgpt_volume_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyvsgpt_volume_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the volume to abort the current activity." },

	{ "open",
	  (PyCFunction) pyvsgpt_volume_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a volume." },

	{ "open_file_object",
	  (PyCFunction) pyvsgpt_volume_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a volume using a file-like object." },

	{ "close",
	  (PyCFunction) pyvsgpt_volume_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a volume." },

	{ "get_bytes_per_sector",
	  (PyCFunction) pyvsgpt_volume_get_bytes_per_sector,
	  METH_NOARGS,
	  "get_bytes_per_sector() -> Integer\n"
	  "\n"
	  "Retrieves the number of bytes per sector." },

	{ "get_number_of_partitions",
	  (PyCFunction) pyvsgpt_volume_get_number_of_partitions,
	  METH_NOARGS,
	  "get_number_of_partitions() -> Integer\n"
	  "\n"
	  "Retrieves the number of partitions." },

	{ "get_partition",
	  (PyCFunction) pyvsgpt_volume_get_partition,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_partition(partition_index) -> Object\n"
	  "\n"
	  "Retrieves the partition specified by the index." },

	{ "has_partition_with_identifier",
	  (PyCFunction) pyvsgpt_volume_has_partition_with_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "has_partition_with_identifier(identifier) -> Boolean\n"
	  "\n"
	  "Determines if the volume contains a partition with the identifier." },

	{ "get_partition_by_identifier",
	  (PyCFunction) pyvsgpt_volume_get_partition_by_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_partition_by_identifier(identifier) -> Object or None\n"
	  "\n"
	  "Retrieves the partition specified by the identifier." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvsgpt_volume_object_get_set_definitions[] = {

	{ "bytes_per_sector",
	  (getter) pyvsgpt_volume_get_bytes_per_sector,
	  (setter) 0,
	  "The number of bytes per sector.",
	  NULL },

	{ "number_of_partitions",
	  (getter) pyvsgpt_volume_get_number_of_partitions,
	  (setter) 0,
	  "The number of partitions.",
	  NULL },

	{ "partitions",
	  (getter) pyvsgpt_volume_get_partitions,
	  (setter) 0,
	  "The partitions.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvsgpt_volume_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvsgpt.volume",
	/* tp_basicsize */
	sizeof( pyvsgpt_volume_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvsgpt_volume_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyvsgpt volume object (wraps libvsgpt_volume_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyvsgpt_volume_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvsgpt_volume_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyvsgpt_volume_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Initializes a volume object
 * Returns 0 if successful or -1 on error
 */
int pyvsgpt_volume_init(
     pyvsgpt_volume_t *pyvsgpt_volume )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsgpt_volume_init";

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	/* Make sure libvsgpt volume is set to NULL
	 */
	pyvsgpt_volume->volume         = NULL;
	pyvsgpt_volume->file_io_handle = NULL;

	if( libvsgpt_volume_initialize(
	     &( pyvsgpt_volume->volume ),
	     &error ) != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a volume object
 */
void pyvsgpt_volume_free(
      pyvsgpt_volume_t *pyvsgpt_volume )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvsgpt_volume_free";
	int result                  = 0;

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvsgpt_volume );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyvsgpt_volume->file_io_handle != NULL )
	{
		if( pyvsgpt_volume_close(
		     pyvsgpt_volume,
		     NULL ) == NULL )
		{
			return;
		}
	}
	if( pyvsgpt_volume->volume != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvsgpt_volume_free(
		          &( pyvsgpt_volume->volume ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsgpt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libvsgpt volume.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pyvsgpt_volume );
}

/* Signals the volume to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_signal_abort(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments PYVSGPT_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsgpt_volume_signal_abort";
	int result               = 0;

	PYVSGPT_UNREFERENCED_PARAMETER( arguments )

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_signal_abort(
	          pyvsgpt_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_open(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	const char *filename_narrow  = NULL;
	static char *function        = "pyvsgpt_volume_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyvsgpt_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3
		filename_wide = (wchar_t *) PyUnicode_AsWideCharString(
		                             string_object,
		                             NULL );
#else
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvsgpt_volume_open_wide(
		          pyvsgpt_volume->volume,
		          filename_wide,
		          LIBVSGPT_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3
		PyMem_Free(
		 filename_wide );
#endif
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyvsgpt_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvsgpt_volume_open(
		          pyvsgpt_volume->volume,
		          filename_narrow,
		          LIBVSGPT_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pyvsgpt_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyvsgpt_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvsgpt_volume_open(
		          pyvsgpt_volume->volume,
		          filename_narrow,
		          LIBVSGPT_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsgpt_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a volume using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_open_file_object(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvsgpt_volume_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
	int result                  = 0;

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pyvsgpt_volume->file_io_handle != NULL )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid volume - file IO volume already set.",
		 function );

		goto on_error;
	}
	if( pyvsgpt_file_object_initialize(
	     &( pyvsgpt_volume->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO volume.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_open_file_io_handle(
	          pyvsgpt_volume->volume,
	          pyvsgpt_volume->file_io_handle,
	          LIBVSGPT_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open volume.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyvsgpt_volume->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pyvsgpt_volume->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_close(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments PYVSGPT_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsgpt_volume_close";
	int result               = 0;

	PYVSGPT_UNREFERENCED_PARAMETER( arguments )

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_close(
	          pyvsgpt_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close volume.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pyvsgpt_volume->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pyvsgpt_volume->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsgpt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libbfio file IO volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the number of bytes per sector
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_get_bytes_per_sector(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments PYVSGPT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsgpt_volume_get_bytes_per_sector";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYVSGPT_UNREFERENCED_PARAMETER( arguments )

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_get_bytes_per_sector(
	          pyvsgpt_volume->volume,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of bytes per sector.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the number of partitions
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_get_number_of_partitions(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments PYVSGPT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsgpt_volume_get_number_of_partitions";
	int number_of_partitions = 0;
	int result               = 0;

	PYVSGPT_UNREFERENCED_PARAMETER( arguments )

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_get_number_of_partitions(
	          pyvsgpt_volume->volume,
	          &number_of_partitions,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of partitions.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_partitions );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_partitions );
#endif
	return( integer_object );
}

/* Retrieves a specific partition by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_get_partition_by_index(
           PyObject *pyvsgpt_volume,
           int partition_index )
{
	PyObject *partition_object      = NULL;
	libcerror_error_t *error        = NULL;
	libvsgpt_partition_t *partition = NULL;
	static char *function           = "pyvsgpt_volume_get_partition_by_index";
	int result                      = 0;

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_get_partition_by_index(
	          ( (pyvsgpt_volume_t *) pyvsgpt_volume )->volume,
	          partition_index,
	          &partition,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve partition: %d.",
		 function,
		 partition_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	partition_object = pyvsgpt_partition_new(
	                    partition,
	                    pyvsgpt_volume );

	if( partition_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create partition object.",
		 function );

		goto on_error;
	}
	return( partition_object );

on_error:
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific partition
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_get_partition(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *partition_object  = NULL;
	static char *keyword_list[] = { "partition_index", NULL };
	int partition_index         = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &partition_index ) == 0 )
	{
		return( NULL );
	}
	partition_object = pyvsgpt_volume_get_partition_by_index(
	                    (PyObject *) pyvsgpt_volume,
	                    partition_index );

	return( partition_object );
}

/* Retrieves a sequence and iterator object for the partitions
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_get_partitions(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments PYVSGPT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyvsgpt_volume_get_partitions";
	int number_of_partitions  = 0;
	int result                = 0;

	PYVSGPT_UNREFERENCED_PARAMETER( arguments )

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_get_number_of_partitions(
	          pyvsgpt_volume->volume,
	          &number_of_partitions,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of partitions.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyvsgpt_partitions_new(
	                   (PyObject *) pyvsgpt_volume,
	                   &pyvsgpt_volume_get_partition_by_index,
	                   number_of_partitions );

	if( sequence_object == NULL )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

/* Determines if the volume contains a partition with the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_has_partition_with_identifier(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvsgpt_volume_has_partition_with_identifier";
	static char *keyword_list[] = { "entry_index", NULL };
	unsigned long entry_index   = 0;
	int result                  = 0;

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "k",
	     keyword_list,
	     &entry_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_has_partition_with_identifier(
	          ( (pyvsgpt_volume_t *) pyvsgpt_volume )->volume,
	          (uint32_t) entry_index,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine if volume has partition: %d.",
		 function,
		 entry_index );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result != 0 )
	{
		Py_IncRef(
		 Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 Py_False );

	return( Py_False );
}

/* Retrieves a specific of partition by identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsgpt_volume_get_partition_by_identifier(
           pyvsgpt_volume_t *pyvsgpt_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *partition_object      = NULL;
	libcerror_error_t *error        = NULL;
	libvsgpt_partition_t *partition = NULL;
	static char *function           = "pyvsgpt_volume_get_partition_by_identifier";
	static char *keyword_list[]     = { "entry_index", NULL };
	unsigned long entry_index       = 0;
	int result                      = 0;

	if( pyvsgpt_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "k",
	     keyword_list,
	     &entry_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsgpt_volume_get_partition_by_identifier(
	          ( (pyvsgpt_volume_t *) pyvsgpt_volume )->volume,
	          (uint32_t) entry_index,
	          &partition,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvsgpt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve of partition: %d.",
		 function,
		 entry_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	partition_object = pyvsgpt_partition_new(
	                    partition,
	                    (PyObject *) pyvsgpt_volume );

	if( partition_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create partition object.",
		 function );

		goto on_error;
	}
	return( partition_object );

on_error:
	if( partition != NULL )
	{
		libvsgpt_partition_free(
		 &partition,
		 NULL );
	}
	return( NULL );
}

