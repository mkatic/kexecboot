/*
 *  kexecboot - A kexec based bootloader
 *  XPM parsing routines based on libXpm
 *  NOTE: Only XPM 3 are supported!
 *
 *  Copyright (c) 2008-2011 Yuri Bushmelev <jay4mail@gmail.com>
 *  Copyright (C) 1989-95 GROUPE BULL
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

/* NOTE:
 * 1. Sorry, but we don't support ATM:
 *    - hotspot coordinates;
 *    - 's' color context;
 *    - XPM 1 and XPM 2 notation.
 * 2. We replace all unknown named colors with red color (like libXpm does).
 * 3. We consider all unknown pixels in image data as transparent.
 * 4. We allow only ASCII chars with codes inclusive from 32 to 127
 *    as pixel chars (for 1 or 2 char per pixel case only).
 */


#ifndef _HAVE_XPM_H
#define _HAVE_XPM_H

#include "config.h"

#ifdef USE_ICONS
#include "fb.h"

/* Limit maximum xpm file size to 64Kb */
#ifndef MAX_XPM_FILE_SIZE
#define MAX_XPM_FILE_SIZE 65535
#endif

/* Maximum length of color line */
#define MAX_XPM_CLINE_SIZE 128

/* We can use only 95 ASCII chars when coding colors [32-127]
 * but use 96 to speed up ariphmetic ((x << 6) + (x << 5))
 * Returns x * 96
 */
#define XPM_ASCII_RANGE(x) (((x) << 6) + ((x) << 5))


/* Color keys */
enum xpm_ckey_t {
	XPM_KEY_MONO	= 0,
	XPM_KEY_GREY4	= 1,
	XPM_KEY_GRAY4	= 1,
	XPM_KEY_GREY	= 2,
	XPM_KEY_GRAY	= 2,
	XPM_KEY_COLOR	= 3,
	XPM_KEY_SYMBOL	= 4,
	XPM_KEY_UNKNOWN = 5,
};

/*
 * Function: xpm_destroy_image()
 * Free XPM image array allocated by xpm_load_image()
 * Args:
 * - pointer to xpm image data
 * - rows count of xpm image data
 * Return value: None
 * NOTE: Use it only on images loaded with xpm_load_image()
 */
void xpm_destroy_image(char **xpm_data, const int rows);

/*
 * Function: xpm_load_image()
 * Load XPM image to array of strings to be like compiled-in image.
 * Args:
 * - pointer to store address of XPM image data
 * - filename of XPM image to load
 * Return value:
 * - rows count of xpm image data
 * - -1 on error
 * xpm_data should be destroyed with xpm_destroy_image()
 */
int xpm_load_image(char ***xpm_data, const char *filename);

/*
 * Function: xpm_parse_image()
 * Process XPM image data and make it 'drawable'.
 * Processed data will be stored into allocated buffer.
 * Args:
 * - pointer to xpm image data
 * - rows count of xpm image data
 * - device bits per pixel value
 * Return value:
 * - pointer to allocated and processed data
 * - NULL on error
 * Should be free()'d
 */
kx_picture *xpm_parse_image(char **xpm_data, const int rows);

#endif // USE_ICONS
#endif // _HAVE_XPM_H
