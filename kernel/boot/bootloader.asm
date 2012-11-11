; Jonathan Salwan

[BITS 16]
[ORG 0x0]

%define FLOPPY_MEM 	0x07C0
%define STAGE2		0x1000
%define SEG_CS		0x08
%define SEG_DS		0x10


jmp bootloader

loadmsg: db "Loading kernel, waiting...", 0x00

; gdt struct
gdt:
	; Null Entry
    	dw 0x0000 		; limit 16
	dw 0x0000 		; base_low 16
        db 0x00			; base_middle 8
	db 0x00			; access 8
	db 0x00			; granularity 8
	db 0x00			; base_high 8
	; CS ring0 Entry
	dw 0xffff
	dw 0x0000
	db 0x00
	db 0x9b
	db 0xdf
	db 0x00
	; DS ES FS GS ring0 Entry
	dw 0xffff
	dw 0x0000
	db 0x00
	db 0x93
	db 0xdf
	db 0x00
	; SS ring0 Entry
    	dw 0x0000
	dw 0x0000
	db 0x00
	db 0x97
	db 0xdf
	db 0x00
gdtend:

; gdtr struct
; limit 16
; base 32
gdtr:
    dw    0x0000
    dd    0x00000000

; unity bios boot
unity: db 0

modX:
	mov 	ah, 0x00
	mov 	al, 0x13
	int 	0x10
	ret

modT:
	mov 	ah, 0x00
	mov 	al, 0x03
	int 	0x10
	ret

print:
	push 	ax
	push 	bx
	.1:
		lodsb			; ds:si -> al && inc si
		cmp 	al,0		; cmp *str != 0
		jz 	.2
		mov 	ah,0x0E		; e0 print char - bios init
		mov 	bx,0x07		; bx = attr 0x07 = no blink, no bold, bg black, text white
		int 	0x10		; bios int
        	jmp 	.1
	.2:
	pop 	bx
	pop 	ax
	ret

copy_stage2:
	; copy stage2 opcodes from floppy in 0x1000
    	push 	es
    	mov 	ax, 0x100
    	mov 	es, ax
    	mov 	bx, 0			; offset 0 - es:bs
    	mov 	ah, 2			; Function - Read floppy sector
    	mov 	al, 54 			; Number of sector to read - 54 * 512 = 26624 (size max stage2)
    	mov 	ch, 0			; Number of cylinder
    	mov 	cl, 2
    	mov 	dh, 0
    	mov 	dl, [unity]		; unity
    	int 	0x13   			; Mode floppy - bios interrupt
    	pop 	es
	ret

calc_gdt_base:
    	mov 	ax, gdtend
    	mov 	bx, gdt
    	sub 	ax, bx
    	mov 	word [gdtr], ax

	xor  	eax, eax
    	mov  	ax, ds			; ds = 0
    	mov  	bx, gdt			; addr of gdt tab
    	xor 	ecx, ecx
    	mov 	cx, ax
    	shl 	ecx, 4
    	and 	ebx, 0x0000FFFF
    	add 	ecx, ebx
    	mov 	dword [gdtr + 2], ecx	; set base
	ret

jmp_stage2:
	; set protected mode
    	cli				; disable int
    	lgdt 	[gdtr]  		; load gdt
    	mov 	eax, cr0
    	or   	ax, 1
    	mov 	cr0, eax
	; init segments
    	jmp 	flush				; need this jmp for init seg
	flush:
    		mov 	ax, SEG_DS    		; 0x10 = DS
    		mov 	ds, ax
    		mov 	fs, ax
    		mov 	gs, ax
    		mov 	es, ax
    		mov 	ss, ax
    		mov 	esp, 0x9F000
    		jmp 	dword SEG_CS:STAGE2	; jmp in stage2 in 0x1000

bootloader:
	; get unity attr
   	mov 	[unity], dl

	; init seg floppy
    	mov 	ax, FLOPPY_MEM
    	mov 	ds, ax
    	mov 	es, ax
	; init stack
    	mov 	ax, 0xffff    		; stack en 0xFFFF
    	mov 	ss, ax
    	mov 	sp, 0xffff

    	mov 	si, loadmsg
    	call 	print
	;call modX

	call 	copy_stage2
	call 	calc_gdt_base
	call 	jmp_stage2

;  padding for img Floppy boot disk
times 510-($-$$) db 144
dw 0xAA55

