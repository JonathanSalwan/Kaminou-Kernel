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
#include "interrupt.h"

void kernel_panic(uint32_t eax, uint32_t ebx, uint32_t ecx,
                  uint32_t edx, uint32_t edi, uint32_t esi,
                  uint32_t ebp, uint32_t esp)
{
  uint32_t cr0, cr2, cr3, cr4;

  cr0 = GET_CR(0);
  cr2 = GET_CR(2);
  cr3 = GET_CR(3);
  cr4 = GET_CR(4);

  kVideo_print("=============================================================================\n");
  kVideo_print("EAX: "), kVideo_printBase(eax, 16), kVideo_print("\n");
  kVideo_print("EBX: "), kVideo_printBase(ebx, 16), kVideo_print("\n");
  kVideo_print("ECX: "), kVideo_printBase(ecx, 16), kVideo_print("\n");
  kVideo_print("EDX: "), kVideo_printBase(edx, 16), kVideo_print("\n");
  kVideo_print("EDI: "), kVideo_printBase(edi, 16), kVideo_print("\n");
  kVideo_print("ESI: "), kVideo_printBase(esi, 16), kVideo_print("\n");
  kVideo_print("EBP: "), kVideo_printBase(ebp, 16), kVideo_print("\n");     /* FIXME */
  kVideo_print("ESP: "), kVideo_printBase(esp, 16), kVideo_print("\n\n");   /* FIXME */

  kVideo_print("CR0: 0x"), kVideo_printBase(cr0, 16), kVideo_print("\n");
  kVideo_print("CR2: 0x"), kVideo_printBase(cr2, 16), kVideo_print("\n");
  kVideo_print("CR3: 0x"), kVideo_printBase(cr3, 16), kVideo_print("\n");
  kVideo_print("CR4: 0x"), kVideo_printBase(cr4, 16), kVideo_print("\n");
  kVideo_print("=============================================================================\n");
  kVideo_print("[Kernel Panic]");
  hlt();
}

