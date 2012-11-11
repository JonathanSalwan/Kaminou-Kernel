##
##  Copyright (C) 2012 - Jonathan Salwan - http://www.twitter.com/jonathansalwan
##
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

INCLUDE = "../includes/"

CC = gcc -W -Wextra -ansi -nostdlib -nodefaultlibs -I$(INCLUDE)

OBJ = kmain.o \
      handler_interrupt.o \
      panic.o \
      interrupt.o \
      syscalls.o \
      sys_write.o \
      sys_getpid.o \
      sys_getuid.o \
      sys_getgid.o \
      sys_nice.o \
      sys_exit.o \
      video.o \
      init.o \
      mm.o \
      process.o \
      sched.o

all: $(OBJ)

handler_interrupt.o: handler_interrupt.asm
	nasm -f elf -o $@ $^

sched.o: sched.asm
	nasm -f elf -o $@ $^

.o: .c
	$(CC) -c $^

clean:
	rm -f *.o

