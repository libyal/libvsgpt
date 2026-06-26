/*
 * Shows information obtained from a GUID Partition Table (GPT) volume system.
 *
 * Copyright (C) 2019-2026, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <system_string.h>
#include <types.h>

#if defined( HAVE_FCNTL_H ) || defined( WINAPI )
#include <fcntl.h>
#endif

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "info_handle.h"
#include "vsgpttools_getopt.h"
#include "vsgpttools_libcerror.h"
#include "vsgpttools_libclocale.h"
#include "vsgpttools_libcnotify.h"
#include "vsgpttools_libvsgpt.h"
#include "vsgpttools_output.h"
#include "vsgpttools_signal.h"
#include "vsgpttools_unused.h"

info_handle_t *vsgptinfo_info_handle = NULL;
int vsgptinfo_abort                  = 0;

/* Signal handler for vsgptinfo
 */
void vsgptinfo_signal_handler(
      vsgpttools_signal_t signal VSGPTTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vsgptinfo_signal_handler";

	VSGPTTOOLS_UNREFERENCED_PARAMETER( signal )

	vsgptinfo_abort = 1;

	if( vsgptinfo_info_handle != NULL )
	{
		if( info_handle_signal_abort(
		     vsgptinfo_info_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal info handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	const char *description = \
		"Use vsgptinfo to determine information about a GUID Partition Table (GPT) volume system.";

	vsgpttools_option_t options[ ] = {
		{ 'h', NULL, "shows this help" },
		{ 'v', NULL, "verbose output to stderr" },
		{ 'V', NULL, "print version" },
		{ 0, "source", "the source image" },
	};
	system_character_t options_string[ 32 ];

	libvsgpt_error_t *error    = NULL;
	system_character_t *source = NULL;
	char *program              = "vsgptinfo";
	system_integer_t option    = 0;
	int number_of_options      = (int) ( sizeof( options ) / sizeof( vsgpttools_option_t ) );
	int verbose                = 0;

#if defined( __MINGW32__ ) && defined( HAVE_MINGW_BINMODE )
	_setmode( _fileno( stdout ), _O_BINARY );
	_setmode( _fileno( stderr ), _O_BINARY );
#endif

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
	     "vsgpttools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( vsgpttools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	vsgpttools_output_version_fprint(
	 stdout,
	 program );

	if( vsgpttools_getopt_get_options_string(
	     options,
	     number_of_options,
	     options_string,
	     32 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to determine options string.\n" );

		goto on_error;
	}
	while( ( option = vsgpttools_getopt(
	                   argc,
	                   argv,
	                   options_string ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				vsgpttools_getopt_usage_fprint(
				 stdout,
				 program,
				 description,
				 options,
				 number_of_options );

				return( EXIT_FAILURE );

			case (system_integer_t) 'h':
				vsgpttools_getopt_usage_fprint(
				 stdout,
				 program,
				 description,
				 options,
				 number_of_options );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				vsgpttools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source image.\n" );

		vsgpttools_getopt_usage_fprint(
		 stdout,
		 program,
		 description,
		 options,
		 number_of_options );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libvsgpt_notify_set_stream(
	 stderr,
	 NULL );
	libvsgpt_notify_set_verbose(
	 verbose );

	if( info_handle_initialize(
	     &vsgptinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize info handle.\n" );

		goto on_error;
	}
#if defined( __clang_analyzer__ )
	__builtin_assume( vsgptinfo_info_handle != NULL );
#endif
	if( info_handle_open_input(
	     vsgptinfo_info_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open source image.\n" );

		goto on_error;
	}
	if( info_handle_partitions_fprint(
	     vsgptinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print partitions information.\n" );

		goto on_error;
	}
	if( info_handle_close_input(
	     vsgptinfo_info_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close info handle.\n" );

		goto on_error;
	}
	if( info_handle_free(
	     &vsgptinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free info handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( vsgptinfo_info_handle != NULL )
	{
		info_handle_free(
		 &vsgptinfo_info_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

