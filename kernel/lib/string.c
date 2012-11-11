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

#include "stdlib.h"
#include "string.h"

size_t strlen(const char *str)
{
  int i = 0;

  while(str[i++]);
  return (i);
}

void *memset(char *s, int c, size_t n)
{
  size_t i = 0;

  while (i < n)
    s[i++] = c;
  return (s);
}

char *strcat(char *dest, const char *src)
{
  size_t dest_l, src_l, i = 1;

  dest_l = strlen(dest);
  src_l = strlen(src);
  while (i < src_l){
    dest[dest_l + i] = src[i];
    i++;
  }
  dest[dest_l + i] = '\0';
  return (dest);
}

char *strcpy(char *dest, const char *src)
{
  char *p_save = dest;

  while((*(dest++) = *(src++)));
  return (p_save);
}

char *strncpy(char *dest, const char *src, size_t i)
{
  char *p_save = dest;

  while((*(dest++) = *(src++)) && i--);
  return (p_save);
}

void *memcpy(void *dest, const void *src, size_t n)
{
  void *save = dest;

  while(n --> 0)
    *((char*)(dest)++) = *((char*)(src)++);
  return (save);
}
