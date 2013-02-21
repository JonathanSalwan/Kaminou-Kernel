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


#ifndef   __VIDEO_H__
#define   __VIDEO_H__

/* Mode 0x03 - 80x25 - 16 colors */
# define VIDEOADDR         0xB8000
# define VIDEOSIZE         0xFA0   /* 4000 - number of byte by text page */
# define MAXLINE           25
# define MAXCOLUMN         80

/* Mode 0x13 - 320x200 - 256 colors - Graphic Mode */
# define X_WIDTH            320
# define X_HEIGHT           200
# define X_ADDR             0xA0000
# define X_SIZE             64000

/*
**  Video attribut byte :
**
**  7                                                   0
**  [Blink 1 bit - BG 3 bits - Bold 1 bit - Color 3 bits]
**
*/
# define COLOR_BLACK       0b00000000
# define COLOR_BLUE        0b00000001
# define COLOR_GREEN       0b00000010
# define COLOR_CYAN        0b00000011
# define COLOR_RED         0b00000100
# define COLOR_MAGENTA     0b00000101
# define COLOR_YELLOW      0b00000110
# define COLOR_WHITE       0b00000111

# define COLOR_BG_BLACK    0b00000000
# define COLOR_BG_BLUE     0b00010000
# define COLOR_BG_GREEN    0b00100000
# define COLOR_BG_CYAN     0b00110000
# define COLOR_BG_RED      0b01000000
# define COLOR_BG_MAGENTA  0b01010000
# define COLOR_BG_YELLOW   0b01100000
# define COLOR_BG_WHITE    0b01110000

# define COLOR_BOLD        0b00001000
# define COLOR_BLINK       0b10000000

struct s_kVideo
{
  char posX;          /* 80 */
  char posY;          /* 25 */
  unsigned char attr; /* color */
};

static struct s_kVideo kVideo =
{
  .posX = 0x00,
  .posY = 0x00,
  .attr = COLOR_WHITE
};


union vga_color
{
  struct
    {
      unsigned char blink:1;
      unsigned char bg:3;
      unsigned char bold:1;
      unsigned char tc:3;
    } bits;
  unsigned char attr;
};

void kVideo_clear_screen(void);
void kVideo_putchar(unsigned char);
void kVideo_print(char *);
void kVideo_printBase(unsigned int, unsigned int);
void kVideo_printOK(void);
void kVideo_XEnable(void);
void kVideo_XDisable(void);
void kVideo_Xline_W(uint32_t base, uint32_t size, uint8_t color);
void kVideo_Xsquare(uint32_t base, uint32_t size, uint8_t color);

#endif     /* !__VIDEO_H__ */

