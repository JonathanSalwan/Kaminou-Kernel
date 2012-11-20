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

#ifndef   __KMALLOC_H__
#define   __KMALLOC_H__

#include "stdlib.h"

#define MAGIC 0x4B4D4D00

struct s_header
{
  unsigned flags;
  unsigned size;
};

void *kmalloc(uint32_t size);
void kfree(void *addr);

#endif     /* !__KMALLOC_H__ */
