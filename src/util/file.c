/*
 * StarPU
 * Copyright (C) Université Bordeaux 1, CNRS 2008-2009 (see AUTHORS file)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Lesser General Public License in COPYING.LGPL for more details.
 */

#include <starpu.h>

void _starpu_drop_comments(FILE *f)
{
	while(1) {
		int c = getc(f);

		switch (c) {
			case '#':
			{
				char s[128];
				do {
					fgets(s, sizeof(s), f);
				} while (!strchr(s, '\n'));
			}
			case '\n':
				continue;
			default:
				ungetc(c, f);
				return;
		}
	}
}

