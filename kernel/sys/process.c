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

#include "sys/mm.h"
#include "sys/process.h"
#include "sys/kernel.h"
#include "lib/stdlib.h"
#include "lib/string.h"

uint32_t  nb_proc = 0;
uint32_t  pid_g = 1;
struct    process_s *current_proc = NULL;
struct    process_s *first_proc = NULL;
struct    process_s *last_proc = NULL;

/* create_task() is for execute a function in user mode */
void create_task(uint8_t *opcode, uint32_t size)
{

  struct process_s *proc;
  uint32_t *page, *page_dir;

  /* Todo: fixe that */
  if (size >= PAGE_SIZE)
    return;

  page = (uint32_t *)getPage();
  memcpy(page, (uint8_t*)opcode, size);

  page_dir = (uint32_t *)create_pagedir(page, size);
  proc = (struct process_s *)kmalloc(sizeof(struct process_s));
  if (!proc){
    kmm[PAGE((uint32_t)page)] = FREE;
    return ;
  }
  proc->pid = pid_g++;
  proc->uid = 0;                        /* TODO */
  proc->gid = 0;                        /* TODO */
  proc->name = NULL;                    /* TODO */
  proc->mm = page;
  proc->mem_size = size;
  proc->priority = 0;                   /* TODO */
  proc->regs.ss = 0x33;
  proc->regs.esp = USER_VADDR_STACK;
  proc->regs.cs = 0x23;
  proc->regs.eip = USER_VADDR;
  proc->regs.ds = 0x2B;
  proc->regs.es = 0x2B;
  proc->regs.fs = 0x2B;
  proc->regs.gs = 0x2B;
  proc->regs.cr3 = (uint32_t)page_dir;
  proc->regs.esp0 = 0x18;
  proc->regs.ss0 = (uint32_t)(getPage() + PAGE_SIZE - 1);
  proc->regs.eax = 0;
  proc->regs.ebx = 0;
  proc->regs.ecx = 0;
  proc->regs.edx = 0;
  proc->regs.esi = 0;
  proc->regs.edi = 0;
  proc->regs.ebp = 0;

  /* TODO: reinit first_proc and last_proc if sys_exit() in process */
  if (!first_proc)
    first_proc = proc;

  proc->next = first_proc;
  proc->back = last_proc;
  if (proc->back != proc)
    proc->back->next = proc;
  last_proc = proc;

  nb_proc++;
}

void scheduler(void)
{
  uint32_t *stack;
  uint32_t esp0, eflags;
  uint16_t ss, cs;

  if (nb_proc == 0){
    return;
  }
  else if (nb_proc >= 2){
    stack = GET_STACK();
    ktss.esp0 = (uint32_t)(stack+19);

    /* save context execution */
    current_proc->regs.gs     = stack[2];
    current_proc->regs.fs     = stack[3];
    current_proc->regs.es     = stack[4];
    current_proc->regs.ds     = stack[5];
    current_proc->regs.edi    = stack[6];
    current_proc->regs.esi    = stack[7];
    current_proc->regs.ebp    = stack[8];
    current_proc->regs.ebx    = stack[10];
    current_proc->regs.edx    = stack[11];
    current_proc->regs.ecx    = stack[12];
    current_proc->regs.eax    = stack[13];
    current_proc->regs.eip    = stack[14];
    current_proc->regs.cs     = stack[15];
    current_proc->regs.eflags = stack[16];
    current_proc->regs.esp    = stack[17];
    current_proc->regs.ss     = stack[18];

    current_proc = current_proc->next;
  }

  /* if !current_proc, init current_proc, because is a first proc */
  if (!current_proc)
    current_proc = last_proc;
  ss = current_proc->regs.ss;
  cs = current_proc->regs.cs;
  eflags = (current_proc->regs.eflags | 0x200) & 0xFFFFBFFF;
  esp0 = ktss.esp0;
  SWITCH();
}

