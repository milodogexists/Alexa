/* Copyright (C) 1997 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include <config.h>

#if defined (HAVE_LONG_LONG) && !defined (HAVE_STRTOULL)

#define QUAD		1
#define	UNSIGNED	1
#undef HAVE_STRTOL

#include "strtol.c"

#endif /* HAVE_LONG_LONG && !HAVE_STRTOULL */
