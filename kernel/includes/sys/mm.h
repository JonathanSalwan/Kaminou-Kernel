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


#ifndef   __MM_H__
#define   __MM_H__

# include "lib/types.h"

# define PAGING_FLAG  0x80000000      /* CR0 - bit 31 */
# define PAGE_SIZE    0x1000          /* 4096 */
# define MAX_PAGE     0x10000
# define PAGE(addr)   ((addr) >> 12)
# define DIRE(addr)   ((addr) >> 22)
# define GET_PD(addr) ((addr) & 0xFFC00000) >> 22 /* Return Page Directory */
# define GET_PT(addr) ((addr) & 0x003FF000) >> 12 /* Return Page Table */
# define FREE 0
# define USED !FREE

union addr_u
{
  struct
    {
      unsigned offset:12;
      unsigned ptab:10;
      unsigned pdir:10;
    } vaddr;

  struct
    {
      unsigned p:1;         /* Present          */
      unsigned r:1;         /* Read/write       */
      unsigned u:1;         /* User/Supervisor  */
      unsigned w:1;         /* Write Through    */
      unsigned d:1;         /* Cache Disabled   */
      unsigned a:1;         /* Accessed         */
      unsigned _unused:1;
      unsigned s:1;         /* Page Size        */
      unsigned g:1;         /* Global           */
      unsigned avail:3;
      unsigned pdir:20;
    } page_dir;

  struct
    {
      unsigned p:1;         /* Present          */
      unsigned r:1;         /* Read/write       */
      unsigned u:1;         /* User/Supervisor  */
      unsigned w:1;         /* Write Through    */
      unsigned c:1;         /* Cache Disabled   */
      unsigned a:1;         /* Accessed         */
      unsigned d:1;         /* Dirty            */
      unsigned _unused:1;
      unsigned g:1;         /* Global           */
      unsigned avail:3;
      unsigned ptab:20;
    } page_tab;

  uint32_t addr;
};

# define USER_VADDR             0x08040000
# define USER_VADDR_STACK       0xbfffffff
# define USER_VADDR_STACK_P     0xbffff000
# define KERNEL_VADDR           0xc0000000
# define KERNEL_VADDR_STACK     0xffffffff

/* Enable paging */
# define EnablePaging()                     \
  __asm__(                                  \
          /* PD_PHY_ADDR */                 \
          "mov  %0, %%eax\n"                \
          "mov  %%eax, %%cr3\n"             \
          "mov  %%cr0, %%eax\n"             \
          /* PAGING_FLAG */                 \
          "or   $0x80000000, %%eax\n"       \
          "mov  %%eax, %%cr0"               \
          ::"m"(kpage_dir)                  \
);

extern uint32_t *kpage_dir;
extern uint32_t  *kpage_tab;
extern uint32_t  nb_page;               /* Number of pages used */
extern uint32_t  kmm[];

#endif     /* !__MM_H__ */

