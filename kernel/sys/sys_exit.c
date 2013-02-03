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

#include "syscalls.h"
#include "kernel.h"
#include "process.h"

void sys_exit(void)
{
  if (!current_proc)
    return ; /* normally, never go here */

  cli();
  printk("pid = %d\n", current_proc->pid);
  current_proc->back->next = current_proc->next;
  current_proc->next->back = current_proc->back;
  if (current_proc == first_proc)
    first_proc = current_proc->next;
  if (current_proc == last_proc)
    last_proc = current_proc->back;
  current_proc = current_proc->next;
  /* Bug, si kfree panic in magic malloc */
  /* Si comment, cancer dans les taches1 */
  /*kfree(current_proc);*/
  nb_proc--;
  sti();
}

