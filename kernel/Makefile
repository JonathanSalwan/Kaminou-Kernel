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

LD      = ld

BOOT_O	= ./boot/bootgrub

LIB_O	= ./lib/string.o \
	  ./lib/kmalloc.o \
	  ./lib/kprintf.o

SYS_O   = ./sys/kmain.o \
	  ./sys/video.o \
	  ./sys/handler_interrupt.o \
	  ./sys/panic.o \
          ./sys/interrupt.o \
	  ./sys/syscalls.o \
          ./sys/sys_write.o \
          ./sys/sys_getpid.o \
          ./sys/sys_getuid.o \
          ./sys/sys_getgid.o \
          ./sys/sys_nice.o \
          ./sys/sys_exit.o \
	  ./sys/init.o \
	  ./sys/mm.o \
	  ./sys/process.o \
	  ./sys/sched.o

all: boot lib sys kern

boot:
	make -C boot
sys:
	make -C sys
lib:
	make -C lib

kern:
	$(LD) -Ttext=100000 --entry=_start $^ $(BOOT_O) $(LIB_O) $(SYS_O) -o kernel

fclean:
	make -C ./boot clean
	make -C ./sys clean
	make -C ./lib clean
	rm -rf ./kernel

.PHONY: sys boot kern lib

