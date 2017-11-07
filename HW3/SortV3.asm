        ; 8080 assembler code
        .hexfile SortV3.hex
        .binfile SortV3.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6
FORK        equ 7
EXEC        equ 8
WAITPID     equ 9


	; Position for stack pointer
stack   equ F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE     
sortFileName:   dw 'loadsort.com', 00AH, 00H


begin:
	LXI SP,stack 		; always initialize the stack pointer
	MVI C, 1052       	;

    MVI A,FORK
	call GTU_OS         ; fork make child
	MVI a,0
	CMP B
	JZ StartSort        ;child1 code jump
	MVI A,FORK          ; child 2
	call GTU_OS         ; make child
	MVI A,0
	CMP B
	JZ StartSort        ;child 2 Code
	jmp StartSort       ;last parent code

StartSort:
    MVI A,EXEC
	LXI B,sortFileName  ; put sortv3com   
    call GTU_OS
    hlt

