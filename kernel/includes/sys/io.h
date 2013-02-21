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


#ifndef   __IO_H__
#define   __IO_H__

/* I/O PIC 8259A */
# define MASTER_A   0x20
# define MASTER_B   0x21
# define SLAVE_A    0xA0
# define SLAVE_B    0xA1

/* write byte on port */
# define outb(port, value)                  \
  __asm__ (                                 \
            "outb %%al, %%dx"               \
            :: "d" (port), "a" (value)      \
          );


/* read byte on port */
# define inb(port)                          \
({                                          \
      unsigned char _ret;                   \
      __asm__ (                             \
                "inb %%dx, %%al"            \
                : "=a" (_ret) : "d" (port)  \
              );                            \
      _ret;                                 \
})

#endif     /* !__IO_H__ */
