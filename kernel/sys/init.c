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
#include "string.h"
#include "interrupt.h"
#include "io.h"

static void setGdt(uint32_t num, uint32_t base, uint32_t limit,
                   uint8_t access, uint8_t gran)
{
  kgdt[num].base_low    = (base & 0xFFFF);
  kgdt[num].base_middle = (base >> 16) & 0xff;
  kgdt[num].base_high   = (base >> 24) & 0xff;
  kgdt[num].limit_low   = (limit & 0xffff);
  kgdt[num].granularity = (limit >> 16) & 0x0f;
  kgdt[num].granularity |= gran & 0xf0;
  kgdt[num].access      = access;
}

void kGDT_init(void)
{
  setGdt(0, 0x00000000, 0x00000000, 0x00, 0x00);  /* seg 0x00 */
  setGdt(1, 0x00000000, 0xFFFFFFFF, 0x9A, 0xCF);  /* seg 0x08 - kernel land CS */
  setGdt(2, 0x00000000, 0xFFFFFFFF, 0x92, 0xCF);  /* seg 0x10 - kernel land DS ES FS GS */
  setGdt(3, 0x00000000, 0x00000000, 0x97, 0xCF);  /* seg 0x18 - kernel land SS */

  setGdt(4, 0x00000000, 0xFFFFFFFF, 0xFA, 0xCF);  /* seg 0x20 - User land CS */
  setGdt(5, 0x00000000, 0xFFFFFFFF, 0xF2, 0xCF);  /* seg 0x28 - User land DS ES FS GS */
  setGdt(6, 0x00000000, 0x00000000, 0xF7, 0xCF);  /* seg 0x30 - User land SS */

  setGdt(7, (uint32_t)&ktss, sizeof(struct tss), 0xe9, 0x00);  /* seg 0x38 - TSS */

  kgdtr.limit = GDT_NUMBERS * sizeof(struct gdt);
  kgdtr.base  = (uint32_t)&kgdt;

  loadGDT();
  kprintf("* Init Global Descriptor Table Kernel Land"), kVideo_printOK();
  kprintf("* Init Global Descriptor Table User Land"), kVideo_printOK();

  ktss.debug_flag = 0x00;
  ktss.io_map = 0x00;
  ktss.esp0 = 0x00200000;     /* esp ring 0 kernel land */
  ktss.ss0 = 0x18;            /* ss  ring 0 kernel land */

  loadTR();
  kprintf("* Init Task State Segment"), kVideo_printOK();

  initTSS();
  kprintf("* Init Task Register"), kVideo_printOK();
}

static void setIdt(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
   kidt[num].base_lo = base & 0xFFFF;
   kidt[num].base_hi = (base >> 16) & 0xFFFF;
   kidt[num].sel     = sel;
   kidt[num].always0 = 0;
   kidt[num].flags   = flags;
}

void kIDT_init(void)
{
  int i;

  /* set all int in default function */
  for (i = 0; i < IDT_NUMBERS; i++)
    setIdt(i, (uint32_t)_asm_default, 0x08, 0x8E);

  /* Exceptions */
  setIdt(0,  (uint32_t)_asm_dz,    0x08, 0x8E);   /* Divide by Zero */
  setIdt(1,  (uint32_t)_asm_ss,    0x08, 0x8E);   /* Single step */
  setIdt(2,  (uint32_t)_asm_nm,    0x08, 0x8E);   /* Non-maskable */
  setIdt(3,  (uint32_t)_asm_bp,    0x08, 0x8E);   /* Break Point */
  setIdt(4,  (uint32_t)_asm_ot,    0x08, 0x8E);   /* Overflow trap */
  setIdt(5,  (uint32_t)_asm_bre,   0x08, 0x8E);   /* BOUND range exceeded */
  setIdt(6,  (uint32_t)_asm_io,    0x08, 0x8E);   /* Invalid opcode */
  setIdt(7,  (uint32_t)_asm_cna,   0x08, 0x8E);   /* Coprocessor not available */
  setIdt(8,  (uint32_t)_asm_dfe,   0x08, 0x8E);   /* Double fault exception */
  setIdt(9,  (uint32_t)_asm_cso,   0x08, 0x8E);   /* Coprocessor segment overrun */
  setIdt(10, (uint32_t)_asm_itss,  0x08, 0x8E);   /* Invalid task state segment */
  setIdt(11, (uint32_t)_asm_snp,   0x08, 0x8E);   /* Segment not present */
  setIdt(12, (uint32_t)_asm_se,    0x08, 0x8E);   /* Stack exception */
  setIdt(13, (uint32_t)_asm_gpe,   0x08, 0x8E);   /* General protection exception */
  setIdt(14, (uint32_t)_asm_pf,    0x08, 0x8E);   /* page fault */
  /* IRQ */
  setIdt(32, (uint32_t)_asm_irq_0, 0x08, 0x8E);   /* clock */
  setIdt(33, (uint32_t)_asm_irq_1, 0x08, 0x8E);   /* keyboard */
  setIdt(34, (uint32_t)_asm_irq_2, 0x08, 0x8E);
  setIdt(35, (uint32_t)_asm_irq_3, 0x08, 0x8E);
  setIdt(36, (uint32_t)_asm_irq_4, 0x08, 0x8E);
  setIdt(37, (uint32_t)_asm_irq_5, 0x08, 0x8E);
  setIdt(38, (uint32_t)_asm_irq_6, 0x08, 0x8E);
  setIdt(39, (uint32_t)_asm_irq_7, 0x08, 0x8E);
  /* syscall */
  setIdt(128, (uint32_t)_asm_syscalls, 0x08, 0x8E|0x60); /* 128 = 0x80 (int 0x80) = syscall | 0xEF00 = Trap Gate */

  kidtr.limit = IDT_NUMBERS * sizeof(struct idt);
  kidtr.base = (uint32_t)&kidt;
  loadIDT();

  kprintf("* Init Interrupt Descriptor Table"), kVideo_printOK();
}

void kPIC_init(void)
{
  /* Doc: http://www.acm.uiuc.edu/sigops/roll_your_own/i386/irq.html */
  /* ICW1 */
  outb(MASTER_A, 0x11);
  outb(SLAVE_A,  0x11);
  /* ICW2 */
  outb(MASTER_B, 0x20);
  outb(SLAVE_B,  0x28);
  /* ICW3 */
  outb(MASTER_B, 0x04);
  outb(SLAVE_B,  0x02);
  /* ICW4 */
  outb(MASTER_B, 0x01);
  outb(SLAVE_B,  0x01);
  /* Interrupt Mask */
  outb(MASTER_B, 0x0);
  outb(SLAVE_B,  0x0);

  kprintf("* Init Programmable interrupt controler"), kVideo_printOK();
}
