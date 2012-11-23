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

#include "kernel.h"
#include "syscalls.h"
#include "video.h"
#include "string.h"

/* TODO: fix bug !?!?! Oo */
uint32_t sys_read(char *addr, uint32_t size)
{
  kbuffer_keyboard = (uint8_t*)kmalloc(size);
  memset(kbuffer_keyboard, 0x00, size);
  ksbuffer_keyboard = kbuffer_keyboard;
  ksys_readLock = FALSE;
  while(ksys_readLock != TRUE);
  memcpy(addr, ksbuffer_keyboard, size);
  kbuffer_keyboard = ksbuffer_keyboard;
  kfree(kbuffer_keyboard);
  return 0;
}
