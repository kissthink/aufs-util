/*
 * Copyright (C) 2013 Junjiro R. Okajima
 *
 * This program, aufs is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>

#include <linux/aufs_type.h>
#include "au_util.h"

int au_errno;
const char *au_errlist[] = {
	[EAU_MVDOWN_OPAQUE]	= "Opaque ancestor",
	[EAU_MVDOWN_WHITEOUT]	= "Whiteout-ed by ancestor",
	[EAU_MVDOWN_UPPER]	= "Upper exists",
	[EAU_MVDOWN_BOTTOM]	= "No writable lower"
};

void au_perror(const char *s)
{
	const char *colon;

	if (!s || !*s)
		s = colon = "";
	else
		colon = ": ";

	if (!au_errno)
		perror(s);
	else if (0 < au_errno && au_errno < EAU_Last)
		fprintf(stderr, "%s%s%s\n", s, colon, au_errlist[au_errno]);
	else
		fprintf(stderr, "%s%sUnknown error %d\n", s, colon, au_errno);
	fflush(stderr);
}
