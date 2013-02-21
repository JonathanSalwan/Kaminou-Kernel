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

#include <stdarg.h>
#include "lib/types.h"
#include "sys/video.h"

void printk(const char *str, ...)
{
  va_list ap;
  int i;

  va_start(ap, str);
  for (i = 0; str[i] ; i++){
    if (str[i] == '%'){
      switch(str[i+1]){
        case 's':
                  kVideo_print(va_arg(ap, char *));
                  i++;
                  break;
        case 'x':
                  kVideo_printBase(va_arg(ap, uint32_t), 16);
                  i++;
                  break;
        case 'd':
                  kVideo_printBase(va_arg(ap, int), 10);
                  i++;
                  break;
        case 'u':
                  kVideo_printBase(va_arg(ap, uint32_t), 10);
                  i++;
                  break;
        default:
                  i++;
                  break;
      }
    }
    else
      kVideo_putchar(str[i]);
  }
  va_end(ap);
}

