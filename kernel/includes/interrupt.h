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


#ifndef   __INTERRUPT_H__
#define   __INTERRUPT_H__

/* IRQ */
void  _asm_default(void);
void  _asm_irq_0(void);
void  _asm_irq_1(void);
void  _asm_irq_2(void);
void  _asm_irq_3(void);
void  _asm_irq_4(void);
void  _asm_irq_5(void);
void  _asm_irq_6(void);
void  _asm_irq_7(void);

void  int_irq0(void);
void  int_irq1(void);
void  int_irq2(void);
void  int_irq3(void);
void  int_irq4(void);
void  int_irq5(void);
void  int_irq6(void);
void  int_irq7(void);

/* Exceptions */
void  _asm_dz(void);
void  _asm_ss(void);
void  _asm_nm(void);
void  _asm_bp(void);
void  _asm_ot(void);
void  _asm_bre(void);
void  _asm_io(void);
void  _asm_cna(void);
void  _asm_dfe(void);
void  _asm_cso(void);
void  _asm_itss(void);
void  _asm_snp(void);
void  _asm_se(void);
void  _asm_gpe(void);
void  _asm_pf(void);

void  int_dz(void);
void  int_ss(void);
void  int_nm(void);
void  int_bp(void);
void  int_ot(void);
void  int_bre(void);
void  int_io(void);
void  int_cna(void);
void  int_dfe(void);
void  int_cso(void);
void  int_itss(void);
void  int_snp(void);
void  int_se(void);
void  int_gpe(void);

void  int_pf(uint32_t eax, uint32_t ebx, uint32_t ecx,
             uint32_t edx, uint32_t edi, uint32_t esi,
             uint32_t ebp, uint32_t esp);


void kernel_panic(uint32_t eax, uint32_t ebx, uint32_t ecx,
                  uint32_t edx, uint32_t edi, uint32_t esi,
                  uint32_t ebp, uint32_t esp);

/* Interrupts */
void  _asm_syscalls(void);
void  int_syscalls(int syscall_id);

#endif     /* !__INTERRUPT_H__ */
