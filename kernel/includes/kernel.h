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


#ifndef   __KERNEL_H__
#define   __KERNEL_H__

#include "types.h"

/* Load Global Description Table */
# define loadGDT()                      \
  __asm__(                              \
          "lgdtl (kgdtr)\n"             \
          "movw $0x10, %ax\n"           \
          "movw %ax, %ds\n"             \
          "movw %ax, %es\n"             \
          "movw %ax, %fs\n"             \
          "movw %ax, %gs\n"             \
          "ljmp $0x08, $.flush\n"       \
          ".flush:"                     \
         );

/* Load Interrupt Description Table */
# define loadIDT()                      \
  __asm__("lidtl (kidtr)");

/* Load TR */
# define loadTR()                       \
  __asm__(                              \
          "movw $0x38, %ax\n"           \
          "ltr %ax"                     \
         );


# define initTSS()                      \
  __asm__(                              \
          "movw %%ss, %0\n"             \
          "movl %%esp, %1"              \
          : "=m" (ktss.ss0),            \
          "=m" (ktss.esp0)              \
         );

/* Set Kernel Stack addr */
# define initEsp()                      \
  __asm__(                              \
          "movw $0x18, %ax\n"           \
          "movw %ax, %ss\n"             \
          "movl $0x00200000, %esp\n"    \
          "movl $0x001ff000, %ebp\n"    \
);

/* Return Stack pointer */
# define GET_STACK()({                  \
  uint32_t *_stack;                     \
  __asm__("mov (%%ebp), %%eax\n"        \
          "mov %%eax, %0"               \
          : "=m" (_stack));             \
  _stack;                               \
})

/* desable int */
# define cli() __asm__("cli");

/* enable int */
# define sti() __asm__("sti");

/* halt system */
# define hlt() __asm__("hlt");

# define CONCAT_CR(num)                 \
  "mov %%cr" #num ", %0"

# define GET_CR(num)({                  \
  uint32_t _ret;                        \
   __asm__(CONCAT_CR(num)               \
           : "=r" (_ret));              \
  _ret;                                 \
})

struct gdt
{
  uint16_t  limit_low;
  uint16_t  base_low;
  uint8_t   base_middle;
  uint8_t   access;
  uint8_t   granularity;
  uint8_t   base_high;
} __attribute__((packed));

struct gdtr
{
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));

struct idt
{
   uint16_t base_lo;
   uint16_t sel;
   uint8_t  always0;
   uint8_t  flags;
   uint16_t base_hi;
} __attribute__((packed));

struct idtr
{
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));

struct tss
{
  uint16_t previous_task, __padd1;
  uint32_t esp0;
  uint16_t ss0, __padd2;
  uint32_t esp1;
  uint16_t ss1, __padd3;
  uint32_t esp2;
  uint16_t ss2, __padd4;
  uint32_t cr3;
  uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
  uint16_t es, __padd5;
  uint16_t cs, __padd7;
  uint16_t ss, __padd8;
  uint16_t ds, __padd9;
  uint16_t fs, __padd10;
  uint16_t gs, __padd11;
  uint16_t ldt_selector, __padd12;
  uint16_t debug_flag, io_map;
} __attribute__ ((packed));


# define GDT_NUMBERS  0xFF
# define IDT_NUMBERS  0xFF

struct idt  kidt[IDT_NUMBERS];
struct idtr kidtr;
struct gdt  kgdt[GDT_NUMBERS];
struct gdtr kgdtr;
struct tss ktss;

uint32_t kclock;

#endif     /* !__KERNEL_H__ */

