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

#include "sys/kernel.h"
#include "sys/interrupt.h"
#include "sys/video.h"
#include "sys/syscalls.h"
#include "sys/io.h"

static uint32_t jiffies;

static uint8_t keyboardMap[] =
{
  0x1B,	0x1B,	0x1B,	0x1B,	/*	esc	(0x01)	*/
  '1',	'!',	'1',	'1',
  '2',	'@',	'2',	'2',
  '3',	'#',	'3',	'3',
  '4',	'$',	'4',	'4',
  '5',	'%',	'5',	'5',
  '6',	'^',	'6',	'6',
  '7',	'&',	'7',	'7',
  '8',	'*',	'8',	'8',
  '9',	'(',	'9',	'9',
  '0',	')',	'0',	'0',
  '-',	'_',	'-',	'-',
  '=',	'+',	'=',	'=',
  0x08,	0x08,	0x7F,	0x08,	/*	backspace	*/
  0x09,	0x09,	0x09,	0x09,	/*	tab	*/
  'q',	'Q',	'q',	'q',
  'w',	'W',	'w',	'w',
  'e',	'E',	'e',	'e',
  'r',	'R',	'r',	'r',
  't',	'T',	't',	't',
  'y',	'Y',	'y',	'y',
  'u',	'U',	'u',	'u',
  'i',	'I',	'i',	'i',
  'o',	'O',	'o',	'o',
  'p',	'P',	'p',	'p',
  '[',	'{',	'[',	'[',
  ']',	'}',	']',	']',
  0x0A,	0x0A,	0x0A,	0x0A,	/*	enter	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	ctrl	*/
  'a',	'A',	'a',	'a',
  's',	'S',	's',	's',
  'd',	'D',	'd',	'd',
  'f',	'F',	'f',	'f',
  'g',	'G',	'g',	'g',
  'h',	'H',	'h',	'h',
  'j',	'J',	'j',	'j',
  'k',	'K',	'k',	'k',
  'l',	'L',	'l',	'l',
  ';',	':',	';',	';',
  0x27,	0x22,	0x27,	0x27,	/*	'"	*/
  '`',	'~',	'`',	'`',	/*	`~	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	Lshift	(0x2a)	*/
  '\\',	'|',	'\\',	'\\',
  'z',	'Z',	'z',	'z',
  'x',	'X',	'x',	'x',
  'c',	'C',	'c',	'c',
  'v',	'V',	'v',	'v',
  'b',	'B',	'b',	'b',
  'n',	'N',	'n',	'n',
  'm',	'M',	'm',	'm',
  0x2C,	0x3C,	0x2C,	0x2C,	/*	,<	*/
  0x2E,	0x3E,	0x2E,	0x2E,	/*	.>	*/
  0x2F,	0x3F,	0x2F,	0x2F,	/*	/?	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	Rshift	(0x36)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x37)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x38)	*/
  ' ',	' ',	' ',	' ',	/*	(0x39)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x3a)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x3b)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x3c)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x3d)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x3e)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x3f)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x40)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x41)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x42)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x43)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x44)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x45)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x46)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x47)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x48)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x49)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x4a)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x4b)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x4c)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x4d)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x4e)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x4f)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x50)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x51)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x52)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x53)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x54)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x55)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x56)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x57)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x58)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x59)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x5a)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x5b)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x5c)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x5d)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x5e)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x5f)	*/
  0xFF,	0xFF,	0xFF,	0xFF,	/*	(0x60)	*/
  0xFF,	0xFF,	0xFF,	0xFF	/*	(0x61)	*/
};

void int_default(void)
{
}

/* IRQ 0 */
void int_irq0(void)
{
  jiffies++;
  scheduler();
}

/* IRQ 1 */
void int_irq1(void)
{
  unsigned char _ret;

  if (ksys_readLock == TRUE)
    return;
  _ret = inb(0x64);
  while (!(_ret & 0x01))
    _ret = inb(0x64);
  _ret = inb(0x60);
  if (_ret & 0x80)
    return;
  if (_ret < 0x40)
    kVideo_putchar(keyboardMap[(_ret - 1) * 4]);
  if (keyboardMap[(_ret - 1) * 4] == '\n')
    ksys_readLock = TRUE;
  else{
    if ((kbuffer_keyboard - kbuffer_keyboard) > ksys_size)
      return;
    *kbuffer_keyboard = keyboardMap[(_ret - 1) * 4];
    kbuffer_keyboard++;
  }
}

/* IRQ 2 */
void int_irq2(void)
{
}

/* IRQ 3 */
void int_irq3(void)
{
}

/* IRQ 4 */
void int_irq4(void)
{
}

/* IRQ 5 */
void int_irq5(void)
{
}

/* IRQ 6 */
void int_irq6(void)
{
}

/* IRQ 7 */
void int_irq7(void)
{
}

/* Divide by Zero */
void int_dz(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nDivide by Zero\n");
  hlt();
}

/* Single step */
void int_ss(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nSingle step\n");
}

/* Non-maskable */
void int_nm(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nNon-maskable\n");
  hlt();
}

/* Break Point */
void int_bp(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nBreak Point\n");
}

/* Overflow trap */
void int_ot(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nOverflow trap\n");
  hlt();
}

/* BOUND range exceeded  */
void int_bre(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nBOUND range exceeded\n");
  hlt();
}

/* Invalid opcode */
void int_io(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nInvalid opcode\n");
  hlt();
}

/* Coprocessor not available */
void int_cna(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nCoprocessor not available\n");
  hlt();
}

/* Double fault exception */
void int_dfe(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nDouble fault exception\n");
  hlt();
}

/* Coprocessor segment overrun */
void int_cso(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nCoprocessor segment overrun\n");
  hlt();
}

/* Invalid task state segment */
void int_itss(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nInvalid task state segment\n");
  hlt();
}

/* Segment not present */
void int_snp(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nSegment not present\n");
  hlt();
}

/* Stack exception */
void int_se(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nStack exception\n");
  hlt();
}

/* General protection exception */
/*
** All protection violations that do not cause another exception cause a general
** protection exception. This includes, but is not limited to:
**
** - Exceeding the segment limit when using the CS, DS, ES, FS, or GS segments.
**   This is a very common problem in programs; it is usually caused by
**   miscalculating how much memory is required in an allocation.
** - Transferring execution to a segment that is not executable (for example,
**   jumping to a location that contains garbage).
** - Writing to a read-only or a code segment.
** - Loading a bad value into a segment register.
** - Using a null pointer. A value of 0 is defined as a null pointer. In
**   Protected mode, it is always invalid to use a segment register that
**   contains 0.
*/
void int_gpe(void)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nGeneral protection exception\n");
  hlt();
}

/* Page Fault */
void int_pf(uint32_t eax, uint32_t ebx, uint32_t ecx,
            uint32_t edx, uint32_t edi, uint32_t esi,
            uint32_t ebp, uint32_t esp)
{
  kVideo.attr = COLOR_RED;
  kVideo_print("\nPage Fault\n");
  kernel_panic(eax, ebx, ecx, edx, edi, esi, ebp, esp);
}


