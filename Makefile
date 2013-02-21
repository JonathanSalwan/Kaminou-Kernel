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

KERN_D = ./kernel

all: kernel copy

kernel:
	make -C $(KERN_D)

run:
	bochs -f ./bochsrc

fclean:
	make -C kernel fclean

mount:
	sudo mount -o loop -t ext2 ./floppy.img ./loop

umount:
	sleep 1
	sudo umount ./loop

cp:
	cp ./kernel/kernel ./loop/kernel

re: fclean all

copy: mount cp umount

.PHONY: kernel run fclean mount re

