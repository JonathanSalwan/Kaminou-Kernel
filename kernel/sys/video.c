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
#include "sys/video.h"
#include "sys/io.h"
#include "lib/string.h"

static void kVideo_cursor(char x, char y)
{
  short pos = x + y * MAXCOLUMN;

  /*
  ** 0x3d4 => control
  ** 0x3d5 => data
  **/
  outb(0x3d4, 0xf);
  outb(0x3d5, (char)pos);
  outb(0x3d4, 0xe);
  outb(0x3d5, (char)(pos >> 8));
}

void kVideo_clear_screen(void)
{
  unsigned char *video;

  video = (unsigned char *)VIDEOADDR;
  while (video < (unsigned char *)(VIDEOADDR + VIDEOSIZE)){
    *video = 0;
    *(video + 1) = kVideo.attr;
    video += 2;
  }
  kVideo.posX = 1;
  kVideo.posY = 1;
  kVideo_cursor(kVideo.posX, kVideo.posY);
}

static void clear_line(int line)
{
  int i;
  unsigned int offset = (line * 160);
  unsigned char *video = (unsigned char *)(VIDEOADDR);

  for (i = 0; i < 160 ; i++){
    *(video + offset + i) = 0;
  }
}

static void scroll_line(int number)
{
  unsigned char *video = (unsigned char *)(VIDEOADDR);
  unsigned int offset = (number * 160);

  memcpy(video, (video + offset),  VIDEOSIZE - 160);
}

/* FIXME: Fixe if kVideo.posY > 25 */
void kVideo_putchar(unsigned char c)
{
  unsigned char *video;
  unsigned int offset;

  video = (unsigned char *)VIDEOADDR;
  offset = (kVideo.posY * 160) + (kVideo.posX * 2);

  if (c == 0xff)
    return ;
  *(video + offset) = c;
  *(video + offset + 1) = kVideo.attr;

  switch(c){
    case 0x08:               /* backspace */
      *(video + offset - 0) = 0;
      *(video + offset - 1) = 0;
      *(video + offset - 2) = 0;
      kVideo.posX--;
      if (kVideo.posX < 1){
        kVideo.posY--;
        kVideo.posX = MAXCOLUMN - 1;
      }
      break;
    case 0x0a:                /* End of line (\n) */
      *(video + offset) = 0;  /* Don't display \n */
      kVideo.posX = 0;        /* For align with 1 after default */
      kVideo.posY++;
    default:
      kVideo.posX++;
      if (kVideo.posX >= MAXCOLUMN - 1){
        kVideo.posX = 1;
        kVideo.posY++;
      }
      break;
  }

  if (kVideo.posY == MAXLINE - 1){
    scroll_line(1);
    kVideo.posX = 1;
    kVideo.posY = 23;
  }

  kVideo_cursor(kVideo.posX, kVideo.posY);
}

void kVideo_print(char *str)
{
  while(*str)
    kVideo_putchar(*(str++));
}

void kVideo_printBase(unsigned int nb,unsigned int base)
{
  char  _base[] = "0123456789abcdef";

  if (nb < base)
    kVideo_putchar(_base[nb]);
  else{
    kVideo_printBase(nb / base, base);
    kVideo_putchar(_base[nb % base]);
  }
}

void kVideo_printOK(void)
{
  unsigned char attr_old;

  attr_old = kVideo.attr;
  kVideo.posX = 74;
  kVideo_print("[");
  kVideo.attr = COLOR_GREEN;
  kVideo_print("OK");
  kVideo.attr = attr_old;
  kVideo_print("]\n");
}

void kVideo_XEnable(void)
{
}

void kVideo_XDisable(void)
{
}

void kVideo_Xline_W(uint32_t base, uint32_t size, uint8_t color)
{
  uint32_t i;
  unsigned char *video = (unsigned char *)X_ADDR;

  for (i = 0; i < size ; i++){
    *(video + base + i) = color;
  }
}

void kVideo_Xsquare(uint32_t base, uint32_t size, uint8_t color)
{
  uint32_t i;

  for (i = 0; i < size ; i++){
    kVideo_Xline_W(base + (i * X_WIDTH), size, color);
  }
}

