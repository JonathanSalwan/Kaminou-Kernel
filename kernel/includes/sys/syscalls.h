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

# define SYS_WRITE    0x01
# define SYS_GETPID   0x02
# define SYS_GETUID   0x03
# define SYS_GETGID   0x04
# define SYS_NICE     0x05
# define SYS_EXIT     0x06
# define SYS_READ     0x07

#include "lib/types.h"

#define TRUE  1
#define FALSE !TRUE

uint32_t  sys_write(char *msg, uint32_t size);
uint32_t  sys_getpid(void);
uint32_t  sys_getuid(void);
uint32_t  sys_getgid(void);
void      sys_nice(uint32_t priority);
void      sys_exit(void);
uint32_t  sys_read(char *addr, uint32_t size);

extern uint32_t  ksys_readLock;
extern uint32_t  ksys_size;
extern uint8_t   *ksbuffer_keyboard;
extern uint8_t   *kbuffer_keyboard;

#define write(msg, size)({                  \
    uint32_t _ret = 0;                      \
    __asm__("mov %1, %%ebx\n"               \
            "mov $0x1, %%eax\n"             \
            "mov %2, %%ecx\n"               \
            "int $0x80\n"                   \
            "mov %%eax, %0"                 \
            : "=r"(_ret)                    \
            : "m"(msg),                     \
              "i"(size));                   \
    _ret;                                   \
})

#define getpid()({                          \
    uint32_t _ret = 0;                      \
    __asm__("mov $0x2, %%eax\n"             \
            "int $0x80\n"                   \
            "mov %%eax, %0"                 \
            : "=r"(_ret));                  \
    _ret;                                   \
})

#define getuid()({                          \
    uint32_t _ret = 0;                      \
    __asm__("mov $0x3, %%eax\n"             \
            "int $0x80\n"                   \
            "mov %%eax, %0"                 \
            : "=r"(_ret));                  \
    _ret;                                   \
})

#define getgid()({                          \
    uint32_t _ret = 0;                      \
    __asm__("mov $0x4, %%eax\n"             \
            "int $0x80\n"                   \
            "mov %%eax, %0"                 \
            : "=r"(_ret));                  \
    _ret;                                   \
})

#define nice(priority)({                    \
    uint32_t _ret = 0;                      \
    __asm__("mov $0x5, %%eax\n"             \
            "mov %1, %%ebx\n"               \
            "int $0x80\n"                   \
            "mov %%eax, %0"                 \
            : "=r"(_ret) : "i"(priority));  \
    _ret;                                   \
})

#define exit()({                            \
    uint32_t _ret = 0;                      \
    __asm__("mov $0x6, %%eax\n"             \
            "int $0x80\n"                   \
            "mov %%eax, %0"                 \
            : "=r"(_ret));                  \
    _ret;                                   \
})

#define read(addr, size)({                  \
    uint32_t _ret = 0;                      \
    __asm__("mov %1, %%ebx\n"               \
            "mov $0x7, %%eax\n"             \
            "mov %2, %%ecx\n"               \
            "int $0x80\n"                   \
            "mov %%eax, %0"                 \
            : "=r"(_ret)                    \
            : "m"(addr),                    \
              "n"(size));                   \
    _ret;                                   \
})

#endif     /* !__SYSCALLS_H__ */

