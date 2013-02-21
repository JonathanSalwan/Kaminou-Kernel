/*
**  Copyright (C) 2012 - Jonathan Salwan - http://www.twitter.com/jonathansalwan
** 
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
** 
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef   __STRING_H__
#define   __STRING_H__

# include "types.h"

size_t  strlen(const char *str);
void    *memset(char *s, int c, size_t n);
char    *strcat(char *dest, const char *src);
char    *strcpy(char *dest, const char *src);
char    *strncpy(char *dest, const char *src, size_t i);
void    *memcpy(void *dest, const void *src, size_t n);

#endif     /* !__STRING_H__ */
