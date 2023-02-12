/*
 * Codepage definitions for libvsgpt
 *
 * Copyright (C) 2019-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVSGPT_CODEPAGE_H )
#define _LIBVSGPT_CODEPAGE_H

#include <libvsgpt/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBVSGPT_CODEPAGES
{
	LIBVSGPT_CODEPAGE_ASCII				= 20127,

	LIBVSGPT_CODEPAGE_ISO_8859_1			= 28591,
	LIBVSGPT_CODEPAGE_ISO_8859_2			= 28592,
	LIBVSGPT_CODEPAGE_ISO_8859_3			= 28593,
	LIBVSGPT_CODEPAGE_ISO_8859_4			= 28594,
	LIBVSGPT_CODEPAGE_ISO_8859_5			= 28595,
	LIBVSGPT_CODEPAGE_ISO_8859_6			= 28596,
	LIBVSGPT_CODEPAGE_ISO_8859_7			= 28597,
	LIBVSGPT_CODEPAGE_ISO_8859_8			= 28598,
	LIBVSGPT_CODEPAGE_ISO_8859_9			= 28599,
	LIBVSGPT_CODEPAGE_ISO_8859_10			= 28600,
	LIBVSGPT_CODEPAGE_ISO_8859_11			= 28601,
	LIBVSGPT_CODEPAGE_ISO_8859_13			= 28603,
	LIBVSGPT_CODEPAGE_ISO_8859_14			= 28604,
	LIBVSGPT_CODEPAGE_ISO_8859_15			= 28605,
	LIBVSGPT_CODEPAGE_ISO_8859_16			= 28606,

	LIBVSGPT_CODEPAGE_KOI8_R			= 20866,
	LIBVSGPT_CODEPAGE_KOI8_U			= 21866,

	LIBVSGPT_CODEPAGE_WINDOWS_874			= 874,
	LIBVSGPT_CODEPAGE_WINDOWS_932			= 932,
	LIBVSGPT_CODEPAGE_WINDOWS_936			= 936,
	LIBVSGPT_CODEPAGE_WINDOWS_949			= 949,
	LIBVSGPT_CODEPAGE_WINDOWS_950			= 950,
	LIBVSGPT_CODEPAGE_WINDOWS_1250			= 1250,
	LIBVSGPT_CODEPAGE_WINDOWS_1251			= 1251,
	LIBVSGPT_CODEPAGE_WINDOWS_1252			= 1252,
	LIBVSGPT_CODEPAGE_WINDOWS_1253			= 1253,
	LIBVSGPT_CODEPAGE_WINDOWS_1254			= 1254,
	LIBVSGPT_CODEPAGE_WINDOWS_1255			= 1255,
	LIBVSGPT_CODEPAGE_WINDOWS_1256			= 1256,
	LIBVSGPT_CODEPAGE_WINDOWS_1257			= 1257,
	LIBVSGPT_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBVSGPT_CODEPAGE_US_ASCII			LIBVSGPT_CODEPAGE_ASCII

#define LIBVSGPT_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBVSGPT_CODEPAGE_ISO_8859_1
#define LIBVSGPT_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBVSGPT_CODEPAGE_ISO_8859_2
#define LIBVSGPT_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBVSGPT_CODEPAGE_ISO_8859_3
#define LIBVSGPT_CODEPAGE_ISO_NORTH_EUROPEAN		LIBVSGPT_CODEPAGE_ISO_8859_4
#define LIBVSGPT_CODEPAGE_ISO_CYRILLIC			LIBVSGPT_CODEPAGE_ISO_8859_5
#define LIBVSGPT_CODEPAGE_ISO_ARABIC			LIBVSGPT_CODEPAGE_ISO_8859_6
#define LIBVSGPT_CODEPAGE_ISO_GREEK			LIBVSGPT_CODEPAGE_ISO_8859_7
#define LIBVSGPT_CODEPAGE_ISO_HEBREW			LIBVSGPT_CODEPAGE_ISO_8859_8
#define LIBVSGPT_CODEPAGE_ISO_TURKISH			LIBVSGPT_CODEPAGE_ISO_8859_9
#define LIBVSGPT_CODEPAGE_ISO_NORDIC			LIBVSGPT_CODEPAGE_ISO_8859_10
#define LIBVSGPT_CODEPAGE_ISO_THAI			LIBVSGPT_CODEPAGE_ISO_8859_11
#define LIBVSGPT_CODEPAGE_ISO_BALTIC			LIBVSGPT_CODEPAGE_ISO_8859_13
#define LIBVSGPT_CODEPAGE_ISO_CELTIC			LIBVSGPT_CODEPAGE_ISO_8859_14

#define LIBVSGPT_CODEPAGE_ISO_LATIN_1			LIBVSGPT_CODEPAGE_ISO_8859_1
#define LIBVSGPT_CODEPAGE_ISO_LATIN_2			LIBVSGPT_CODEPAGE_ISO_8859_2
#define LIBVSGPT_CODEPAGE_ISO_LATIN_3			LIBVSGPT_CODEPAGE_ISO_8859_3
#define LIBVSGPT_CODEPAGE_ISO_LATIN_4			LIBVSGPT_CODEPAGE_ISO_8859_4
#define LIBVSGPT_CODEPAGE_ISO_LATIN_5			LIBVSGPT_CODEPAGE_ISO_8859_9
#define LIBVSGPT_CODEPAGE_ISO_LATIN_6			LIBVSGPT_CODEPAGE_ISO_8859_10
#define LIBVSGPT_CODEPAGE_ISO_LATIN_7			LIBVSGPT_CODEPAGE_ISO_8859_13
#define LIBVSGPT_CODEPAGE_ISO_LATIN_8			LIBVSGPT_CODEPAGE_ISO_8859_14
#define LIBVSGPT_CODEPAGE_ISO_LATIN_9			LIBVSGPT_CODEPAGE_ISO_8859_15
#define LIBVSGPT_CODEPAGE_ISO_LATIN_10			LIBVSGPT_CODEPAGE_ISO_8859_16

#define LIBVSGPT_CODEPAGE_KOI8_RUSSIAN			LIBVSGPT_CODEPAGE_KOI8_R
#define LIBVSGPT_CODEPAGE_KOI8_UKRAINIAN		LIBVSGPT_CODEPAGE_KOI8_U

#define LIBVSGPT_CODEPAGE_WINDOWS_THAI			LIBVSGPT_CODEPAGE_WINDOWS_874
#define LIBVSGPT_CODEPAGE_WINDOWS_JAPANESE		LIBVSGPT_CODEPAGE_WINDOWS_932
#define LIBVSGPT_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBVSGPT_CODEPAGE_WINDOWS_936
#define LIBVSGPT_CODEPAGE_WINDOWS_KOREAN		LIBVSGPT_CODEPAGE_WINDOWS_949
#define LIBVSGPT_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBVSGPT_CODEPAGE_WINDOWS_950
#define LIBVSGPT_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBVSGPT_CODEPAGE_WINDOWS_1250
#define LIBVSGPT_CODEPAGE_WINDOWS_CYRILLIC		LIBVSGPT_CODEPAGE_WINDOWS_1251
#define LIBVSGPT_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBVSGPT_CODEPAGE_WINDOWS_1252
#define LIBVSGPT_CODEPAGE_WINDOWS_GREEK			LIBVSGPT_CODEPAGE_WINDOWS_1253
#define LIBVSGPT_CODEPAGE_WINDOWS_TURKISH		LIBVSGPT_CODEPAGE_WINDOWS_1254
#define LIBVSGPT_CODEPAGE_WINDOWS_HEBREW		LIBVSGPT_CODEPAGE_WINDOWS_1255
#define LIBVSGPT_CODEPAGE_WINDOWS_ARABIC		LIBVSGPT_CODEPAGE_WINDOWS_1256
#define LIBVSGPT_CODEPAGE_WINDOWS_BALTIC		LIBVSGPT_CODEPAGE_WINDOWS_1257
#define LIBVSGPT_CODEPAGE_WINDOWS_VIETNAMESE		LIBVSGPT_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSGPT_CODEPAGE_H ) */

