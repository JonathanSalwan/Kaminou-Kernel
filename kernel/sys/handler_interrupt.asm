; jonathan salwan

; IRQ
extern      int_default
extern      int_irq0
extern      int_irq1
extern      int_irq2
extern      int_irq3
extern      int_irq4
extern      int_irq5
extern      int_irq6
extern      int_irq7

global      _asm_default
global      _asm_irq_0
global      _asm_irq_1
global      _asm_irq_2
global      _asm_irq_3
global      _asm_irq_4
global      _asm_irq_5
global      _asm_irq_6
global      _asm_irq_7

; Exceptions ;
extern      int_dz
extern      int_ss
extern      int_nm
extern      int_bp
extern      int_ot
extern      int_bre
extern      int_io
extern      int_cna
extern      int_dfe
extern      int_cso
extern      int_itss
extern      int_snp
extern      int_se
extern      int_gpe
extern      int_pf

global      _asm_dz
global      _asm_ss
global      _asm_nm
global      _asm_bp
global      _asm_ot
global      _asm_bre
global      _asm_io
global      _asm_cna
global      _asm_dfe
global      _asm_cso
global      _asm_itss
global      _asm_snp
global      _asm_se
global      _asm_gpe
global      _asm_pf

; Interrupts
extern      int_syscalls

global      _asm_syscalls

_asm_default:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call 	int_default
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ0 clock
_asm_irq_0:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_irq0
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ1 Keyboard
_asm_irq_1:
	pushad
      	push	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_irq1
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ2 real clock
_asm_irq_2:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call    int_irq2
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ3 serie port 2
_asm_irq_3:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call    int_irq3
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ4 serie port 1
_asm_irq_4:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call    int_irq4
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ5 para port 2
_asm_irq_5:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call    int_irq5
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ6 floppy
_asm_irq_6:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call    int_irq6
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; IRQ7 para port 1
_asm_irq_7:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call    int_irq7
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	iret

; Divide by Zero
_asm_dz:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_dz
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Single step
_asm_ss:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_ss
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Non-maskable
_asm_nm:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_nm
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; BreakPoint
_asm_bp:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_bp
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Overflow trap
_asm_ot:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_ot
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; BOUND range exceeded
_asm_bre:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_bre
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Invalid opcode
_asm_io:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_io
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Coprocessor not available
_asm_cna:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_cna
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Double fault exception
_asm_dfe:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_dfe
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Coprocessor segment overrun
_asm_cso:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_cso
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Invalid task state segment
_asm_itss:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_itss
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Segment not present
_asm_snp:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_snp
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Stack exception
_asm_se:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_se
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; General protection exception
_asm_gpe:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx
	call	int_gpe
	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

; Page fault
_asm_pf:
	pushad
      	push 	ds
        push 	es
        push 	fs
        push 	gs
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx

        ; sauvegarde le context d'execution
        ; pour donner les info au kernel panic
        push    esp
        push    ebp
        push    esi
        push    edi
        push    edx
        push    ecx
        push    ebx
        push    eax
	call	int_pf
        pop     eax
        pop     ebx
        pop     ecx
        pop     edx
        pop     edi
        pop     esi
        pop     ebp
        pop     esp

	mov 	al, 0x20
	out 	0x20, al
        pop 	gs
        pop 	fs
        pop 	es
        pop 	ds
        popad
	add 	esp, 4
	iret

_asm_syscalls:
	;pushad <= si place pushad = generale exception wtf ?
        push    eax
        push    ecx
        push    edx
        push    ebx
        push    esp
        push    ebp
        push    esi
        push    edi
        push 	es
        push 	fs
        push 	gs
      	push 	ds
        push 	ebx
        mov 	bx, 0x10
        mov 	ds, bx
        pop 	ebx

        push    esi             ; arg 5
        push    edi             ; arg 4
        push    edx             ; arg 3
        push    ecx             ; arg 2
        push    ebx             ; arg 1
	push 	eax		; syscall number
	call 	int_syscalls
        add     esp, 4          ; pop eax
	;pop 	eax
        pop     ebx
        pop     ecx
        pop     edx
        pop     edi
        pop     esi

        push    eax
	mov 	al, 0x20
	out 	0x20, al
        pop     eax

        pop 	ds
        pop 	gs
        pop 	fs
        pop 	es
        pop     edi
        pop     esi
        pop     ebp
        pop     esp
        pop     ebx
        pop     edx
        pop     ecx
        ;pop     eax
        add     esp, 4
        ;popad
	iret

