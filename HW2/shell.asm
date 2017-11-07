; 8080 assembler code
.hexfile shell.hex
.binfile shell.com
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
stack   equ 02000h

org 0000H
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
enter_promptstr:    dw 'Enter >>  ',00AH,00H
donestr:            dw 'Done .', 00AH, 00H

begin:
	LXI SP,stack 	; always initialize the stack pointer
prmpt:	
	LXI B, enter_promptstr ; put Show Message
	MVI A, PRINT_STR       ; 
	call GTU_OS            ; call os and show message
	MVI B,20H              ; 2001 adress is input adress
	MVI C,01H              ; just after stack
	MVI A, READ_STR        ; 
	call GTU_OS            ; call os the capture input
	;;;Now we got a location of com file
	MVI A,FORK
	call GTU_OS
	MVI A,00H
	CMP B
	JZ CHILDCODE           ; child continues here
	;;;; parent will wait for it 
	MVI A,WAITPID          ; child id is still in b register
	call GTU_OS            ; wait child to done his work
	LXI B,donestr
	MVI A,PRINT_STR
	call GTU_OS            ; show done message
	JMP prmpt
    
    hlt

CHILDCODE:
    MVI A,EXEC
	MVI B,20H              ; 2001 adress is input adress
	MVI C,01H              ; just after stack    
    call GTU_OS
    hlt
    
