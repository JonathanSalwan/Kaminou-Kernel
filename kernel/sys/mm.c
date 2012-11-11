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

#include "mm.h"
#include "stdlib.h"
#include "kernel.h"

uint32_t *getPage(void)
{
  uint32_t i;

  for (i = 0; i < MAX_PAGE ; i++){
    if (kmm[i] == FREE){
      kmm[i] = USED;
      nb_page++;
      return ((uint32_t *)(i * PAGE_SIZE));
    }
  }
  /* TODO bien gerer l'erreur */
  kVideo_print("Fatal Error: Page free not found !!!\n");
  hlt();
  return (NULL);
}

uint32_t *getConsecutivePage(uint32_t nb)
{
  uint32_t i, x;

  for (i = 0; i < MAX_PAGE ; i++){
    for (x = 0; x < nb ; x++){
      if (kmm[i+x] != FREE)
        break;
    }
    if (x == nb){
      for ( ; x > 0 ; x--)
        kmm[i+x-1] = USED;
      nb_page += nb;
      return ((uint32_t *)(i * PAGE_SIZE));
    }
  }
  /* TODO bien gerer l'erreur */
  kVideo_print("Fatal Error: Page free not found !!!\n");
  hlt();
  return (NULL);
}

void reservePageScope(uint32_t start, uint32_t end)
{
  uint32_t i;

  for (i = start ; i < end ; i += PAGE_SIZE){
    if (PAGE(i) < MAX_PAGE){
      kmm[PAGE(i)] = USED;
      nb_page++;
    }
    else
      kVideo_print("Fatal Error: ReservePageScope() PAGE(i) < MAX_PAGE\n");
  }
}

uint32_t *create_pagedir(uint8_t *phy_addr, uint32_t code_size)
{
  uint32_t *page_dir, *page_tab, *u_stack;
  uint32_t i;

  page_dir = getPage();
  for (i = 0; i < 1024; i++)
    page_dir[i] = 0;

  page_dir[0] = kpage_dir[0] | 0b00000011;

  /* user space CS 0x08040000 */
  /* TODO: allouer le bon nombre de page en fonction de code_size */
  page_tab = getPage();
  page_dir[GET_PD(USER_VADDR)] = (uint32_t)page_tab | 0b00000111;
  page_tab[GET_PT(USER_VADDR)] = (uint32_t)phy_addr | 0b00000111;
  kmm[(PAGE((uint32_t)phy_addr))] = USED;

  /* stack 0xbffff000 0xbfffffff (1 PAGE) */
  /* Sur linux la stack contient 33 pages */
  page_tab = getPage();
  u_stack = getPage();
  page_dir[GET_PD(USER_VADDR_STACK_P)] = (uint32_t)page_tab | 0b00000111;
  page_tab[GET_PT(USER_VADDR_STACK_P)] = (uint32_t)u_stack | 0b00000111;

  return (page_dir);
}

void kMM_init(void)
{
  union addr_u addr;
  int i;

  /* hardware space */
  reservePageScope(0x00000000, 0x00020000);
  reservePageScope(0x000a0000, 0x00100000);

  /* Kernel space */
  reservePageScope(0x00100000, 0x00200000);

  kpage_dir = getPage();
  kpage_tab = getPage();

  addr.addr = (uint32_t)kpage_tab;
  addr.page_tab.r = 1;
  addr.page_tab.p = 1;
  kpage_dir[0] = addr.addr;
  for (i = 1; i < 1024; i++)
    kpage_dir[i] = 0;

  /* Init page table */
  for (i = 0; i < 1024; i++) {
    addr.addr = (i * PAGE_SIZE);
    addr.page_tab.r = 1;
    addr.page_tab.p = 1;
    kpage_tab[i] = addr.addr;
  }

  EnablePaging();
  kVideo_print("* Init Mapping Memory Paging"), kVideo_printOK();
}

