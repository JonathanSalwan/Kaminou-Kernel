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

void *checkFreeSpace(uint8_t *first, uint32_t size)
{
  struct s_header header;
  static uint8_t *ptr;

  ptr = first;
  header.flags = *(unsigned *)ptr;
  header.size = *(unsigned *)(ptr + sizeof(header.flags));
  while ((header.flags >> 8) == MAGIC){
    if ((header.flags & 0x01) == FREE && (size + sizeof(struct s_header)) < header.size){

      if ((header.size - (size + sizeof(struct s_header))) > sizeof(struct s_header)){
        *(unsigned *)(ptr + size) = (MAGIC << 8);
        *(unsigned *)(ptr + size + sizeof(header.flags)) = (header.size - (size + sizeof(struct s_header)));
      }

      header.flags = (MAGIC << 8) + USED;
      header.size = size;
      *(unsigned *)ptr = header.flags;
      *(unsigned *)(ptr + sizeof(header.flags)) = header.size;
      return (ptr);
    }
    ptr += header.size;
    header.flags = *(unsigned *)ptr;
    header.size = *(unsigned *)(ptr + sizeof(header.flags));
  }
  return (NULL);
}

void *kmalloc(uint32_t size)
{
  void *ptr = NULL;
  void *ptrAvailable = NULL;
  struct s_header header;
  static uint8_t *max = NULL;
  static uint8_t *base = NULL;
  static uint8_t *first = NULL;

  if (!max && !base && !first){
    base = (uint8_t *)getPage();
    max = base + PAGE_SIZE;
    first = base;
  }

  if ((ptrAvailable = checkFreeSpace(first, size))){
    return (ptrAvailable + sizeof(struct s_header));
  }
  if (base+size+sizeof(struct s_header) < max){
    ptr = base;
    base += size;
  }
  else if (size+sizeof(struct s_header) < PAGE_SIZE){
    base = (uint8_t *)getPage();
    max = base + PAGE_SIZE;
    ptr = base;
    base += size;
  }

  header.flags = (MAGIC << 8) + USED;
  header.size = size;
  *(unsigned *)ptr = header.flags;
  *(unsigned *)(ptr + sizeof(header.flags)) = header.size;
  return (ptr + sizeof(struct s_header));
}

void kfree(void *addr)
{
  *(unsigned *)(addr - 8) = (MAGIC << 8);
}

