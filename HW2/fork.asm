; 8080 assembler code
.hexfile paralel.hex
.binfile paralel.com
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

begin:
	LXI SP,stack 	; always initialize the stack pointer
	MVI A,FORK
	call GTU_OS     ; fork make child
	MVI a,0
	CMP B
	JZ zeroTofifty   ;child1 code jump
	MVI A,FORK        ; child 2
	call GTU_OS       ; make child
	MVI A,0
	CMP B
	JZ thousandsTofifty  ;child 2 Code
	jmp zeropls10     ;last parent code

	
zeropls10:
	mvi B, 10		; counter
	mvi A, 0		; printing register

loop2:
    ADD B           ;
    DCR B
    JNZ loop2
	
	MOV B,A
	MVI A,PRINT_B
	
	call GTU_OS
	
    jmp end         
	
zeroTofifty:
	mvi C, 51		; counter
	mvi B, 0		; printing register
loop1:
		MVI A, PRINT_B 	; print the b register
		call GTU_OS		; call the os
		INR B			; increment to next number
		DCR C			; decrement the counter
		JNZ loop1		; while

end:

    hlt		; end program

thousandsTofifty:
	mvi C, 51		; counter
	mvi B, 100		; printing register
loop:
		MVI A, PRINT_B 	; print the b register
		call GTU_OS		; call the os
		DCR B			; decrement to next number
		DCR C			; decrement the counter
		JNZ loop		; while
		
    jmp end
