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


#ifndef   __PROCESS_H__
#define   __PROCESS_H__

# include "types.h"
# include "stdlib.h"

# define SWITCH()                         \
__asm__(                                  \
        "mov %0, %%esp\n"                 \
        "push %1\n"                       \
        "push %2\n"                       \
        "push %3\n"                       \
        "push %4\n"                       \
        "push %5\n"                       \
        "push %6\n"                       \
        "ljmp $0x08, $switch_proc\n"      \
        ::                                \
        "m" (esp0),                       \
        "m" (ss),                         \
        "m" (current_proc->regs.esp),     \
        "m" (eflags),                     \
        "m" (cs),                         \
        "m" (current_proc->regs.eip),     \
        "m" (current_proc)                \
);

struct regs_s
{
  uint32_t eax, ecx, edx, ebx;
  uint32_t esp, ebp, esi, edi;
  uint32_t eip, eflags;
  uint32_t cs:16, ss:16, ds:16, es:16, fs:16, gs:16;
  uint32_t cr3;
  uint32_t esp0;
  uint16_t ss0;
} __attribute__ ((packed));

struct process_s
{
  uint32_t  pid;

  struct regs_s regs;

  uint32_t  uid;
  uint32_t  gid;

  uint8_t   *name;      /* process name */
  uint32_t  *mm;        /* map addr process */
  uint32_t  mem_size;   /* size mapped */

  uint8_t   priority;

  struct process_s *next;
  struct process_s *back;

} __attribute__ ((packed));

extern uint32_t  nb_proc;
extern uint32_t  pid_g;
extern struct    process_s *current_proc;
extern struct    process_s *first_proc;
extern struct    process_s *last_proc;

#endif     /* !__PROCESS_H__ */

