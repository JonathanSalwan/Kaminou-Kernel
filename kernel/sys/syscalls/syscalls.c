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

#include "sys/kernel.h"
#include "sys/syscalls.h"

/* sys_read enable and disable this variable */
/* when this variable is TRUE, the irq1 is ignored */
uint32_t  ksys_readLock;
uint8_t   *ksbuffer_keyboard;
uint8_t   *kbuffer_keyboard;

/* Syscalls gate */
/* eax = syscall number */
/* ebx = arg 1 */
/* ecx = arg 2 */
/* edx = arg 3 */
/* edi = arg 4 */
/* esi = arg 5 */
uint32_t int_syscalls(uint32_t eax, uint32_t ebx, uint32_t ecx,
                      uint32_t edx, uint32_t edi, uint32_t esi)
{
  uint32_t ret = 0;

  switch(eax){
    case SYS_WRITE:   ret = sys_write((char *)(ebx), ecx); break;
    case SYS_GETPID:  ret = sys_getpid(); break;
    case SYS_GETUID:  ret = sys_getuid(); break;
    case SYS_GETGID:  ret = sys_getgid(); break;
    case SYS_NICE:    sys_nice(ebx); break;
    case SYS_EXIT:    sys_exit(); break;
    case SYS_READ:    sys_read((char *)(ebx), ecx); break;
    default:          break;
    }

  return (ret);
}

