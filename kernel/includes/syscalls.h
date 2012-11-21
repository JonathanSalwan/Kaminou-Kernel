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


#ifndef   __SYSCALLS_H__
#define   __SYSCALLS_H__

# define SYS_NB       0x05

# define SYS_WRITE    0x01
# define SYS_GETPID   0x02
# define SYS_GETUID   0x03
# define SYS_GETGID   0x04
# define SYS_NICE     0x05
# define SYS_EXIT     0x06

#include "types.h"
#include <stdarg.h>

typedef uint32_t (*sys_func)(uint32_t eax, ...);

uint32_t  sys_write(char *msg, uint32_t size);
uint32_t  sys_getpid(void);
uint32_t  sys_getuid(void);
uint32_t  sys_getgid(void);
void      sys_nice(uint32_t priority);
void      sys_exit(void);

static sys_func syscall_tables[] =
{
  (sys_func)sys_write
};

#define _write(msg, size)({           \
    uint32_t _ret = 0;                \
    __asm__("mov %1, %%ebx\n"         \
            "mov $0x1, %%eax\n"       \
            "mov $0x6, %%ecx\n"       \
            "int $0x80\n"             \
            "mov %%eax, %0"           \
            : "=r"(_ret) : "m"(msg)); \
    _ret;                             \
})


#endif     /* !__SYSCALLS_H__ */

