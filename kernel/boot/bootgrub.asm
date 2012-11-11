; jonathan salwan

extern 	kmain

global 	_start

_start:
	jmp 	start

align 	4

multiboot_header:
	dd	0x1BADB002
	dd 	0x00000003
	dd 	-0x1BADB005

start:
	call 	kmain

