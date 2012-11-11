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
#include "types.h"
#include "mm.h"
#include "kmalloc.h"

/* kmalloc sucks++ :). With this version we can't free */
/* It's just for debug */
void *kmalloc(uint32_t size)
{
  void *ptr = NULL;
  static uint8_t *max = NULL;
  static uint8_t *base = NULL;

  if (!max && !base){
    base = (uint8_t *)getPage();
    max = base + PAGE_SIZE;
  }

  if (base+size < max){
    ptr = base;
    base += size;
  }
  else if (size < PAGE_SIZE){
    base = (uint8_t *)getPage();
    max = base + PAGE_SIZE;
    ptr = base;
    base += size;
  }

  return (ptr);
}

/* need a real kmmaloc version for use free() :) */
void kfree(void *addr)
{
}

