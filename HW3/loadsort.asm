        ; 8080 assembler code
        .hexfile loadsort.hex
        .binfile loadsort.com
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

	;This program prints a null terminated string to the screen




;for(int i=0; i< size; i++)
;		for (int j = 0; j < size; j++)
;			if(a[i] > a[j])
;			{
;				temp = a[i];
;				a[i] = a[j];
;				a[j] = temp;
;			}
;		}
;	}


Array: dw $12, $34, $53, $2A, $5B, $6F, $33, $21, $7C, $FF, $BA, $CB, $A1, $1A, $3B, $C3, $4A, $5D, $62, $A3, $B1, $5C, $7F, $CC, $AA, $34, $3B, $C3, $4A, $5D, $62, $A3, $B1, $5C, $7F, $CC, $AA, $34, $52, $51, $5B, $6F, $11, $AB, $44, $55, $22, $7F, $CC, $AA, $34, $52, $51, $11, $AB, $44, $55, $22, $34, $53, $2A, $5B, $6F, $33, $21, $7C, $FF, $AC, $7A, $1D, $2D, $5F, $11, $56, $8A, $21, $3A, $56, $BA, $CB, $CD, $BD, $88, $99, $AA, $99, $AA, $99, $AA, $DD, $FF, $DD, $FF, $DD, $FF, $CC, $98, $7D, $C3, $46, $78, $12, $44, $6A, $BC, $DF, $E2, $32, $56, $13, $47, $23, $44, $76, $AB, $B6, $B9, $A1, $A4, $A1, $24, $A1, $24, $10, $C8, $10, $C8, $E3, $C3, $4A, $5D, $3E, $34, $E4, $2A, $24, $BC, $34, $C5, $6C, $14, $12, $56, $78, $12, $56, $67, $56, $67, $89, $1A, $89, $1A, $89, $1A, $67, $C3, $4A, $67, $C3, $4A, $5D, $67, $AC, $AC, $7A, $1D, $2D, $5F, $11, $56, $8A, $21, $3A, $56, $AC, $7A, $1D, $2D, $5F, $11, $56, $8A, $21, $3A, $56, $1A, $CC, $5A, $19, $A0, $60, $C3, $4A, $5D, $2C, $A3, $C8, $C3, $4A, $5D, $2C, $A3, $C8, $12, $E2, $32, $56, $13, $5D, $C3, $4A, $47, $23, $44, $76, $AB, $B6, $B9, $A1, $AC, $7A, $12, $E2, $32, $56, $13, $5D, $C3, $4A, $47, $23, $44, $76, $AB, $B6, $B9, $A1, $AC, $7A, $1D, $2D, $5F, $11, $56, $8A, $21, $3A, $56, $AC, $56, $3A, $56, $56, $7A, $1D, $2D, $5F, $11, $C8, $12, $E2, $A1, $24, $10, $C8, $56, $8A, $21, $3A, $56, $C3, $4A, $5D, $C3, $4A, $5D, $A0, $F0, $D0, $56, $44, $76, $AB, $B6, $B9, $A1, $A4, $A1, $24, $A1, $24, $10, $C8, $10, $C8, $E3, $C3, $4A, $5D, $3E, $34, $E4, $2A, $24, $BC, $34, $C5, $6C, $14, $12, $56, $78, $12, $56, $67, $56, $67, $89, $1A, $89, $1A, $67, $C3, $4A, $5D, $67, $AC, $AC, $7A, $1D, $2D, $5F, $11, $56, $8A, $21, $3A, $56, $AC, $7A, $1D, $8D, $5F, $11, $56, $8D, $5F, $11, $56, $8A, $21, $13, $8A, $13, $8A, $21, $3A, $56, $21, $3A, $56, $8A, $21, $3A, $56, $1A, $CC, $5A, $19, $A0, $60, $C3, $4A, $5D, $2C, $A3, $C8, $12, $E2, $32, $56, $13, $32, $56, $13, $5D, $5D, $C3, $4A, $47, $23, $44, $76, $AB, $B6, $B9, $A1, $AC, $7A, $AC, $7A, $1D, $2D, $1D, $2D, $5F, $11, $56, $8A, $21, $3A, $56, $AC, $7A, $1D, $2D, $5F, $11, $C8, $12, $E2, $A1, $24, $10, $C8, $56, $8A, $21, $3A, $56, $C3, $4A, $5D, $43, $4A, $5D, $A0, $F0, $D0, $56, $67, $89, $1A, $89, $1A, $30, $30, $50, $1D, $A3, $5D, $6A, $23, $3F, $A2, $21, $90, $02, $9C, $CC, $A1, $24, $8A, $21, $3A, $8A, $21, $8A, $21, $3A, $56, $3A, $56, $56, $10, $02, $30, $50, $1D, $A3, $5D, $6A, $23, $3F, $A2, $21, $90, $02, $9C, $CC, $A1, $24, $8A, $21, $3A, $8A, $21, $8A, $21, $3A, $56, $3A, $56, $56, $10, $02, $9C, $CC, $20, $2D, $9C, $CC, $20, $2D, $8D, $54, $B1, $5C, $7F, $CC, $AA, $34, $52, $51, $11, $AB, $44, $3A, $56, $8A, $21, $3A, $56, $AC, $7A, $1D, $2D, $5F, $21, $C8, $12, $E2, $8D, $5F, $8D, $5F, $11, $56, $8A, $21, $11, $56, $13, $8A, $21, $3A, $56, $8A, $21, $A1, $24, $10, $C8, $56, $8A, $21, $3A, $3A, $56, $C3, $56, $C3, $4A, $5D, $C3, $4A, $5D, $A0, $F0, $3A, $56, $AC, $7A, $1D, $AC, $7A, $1D, $2D, $5F, $11, $C8, $2D, $5F, $11, $C8, $12, $72, $A1, $24, $10, $C8, $56, $8A, $21, $67, $89, $1A, $30, $50, $1D, $A3, $5D, $6A, $23, $3F, $A2, $21, $90, $02, $9C, $CC, $A1, $24, $13, $8A, $21, $3A, $56, $8A, $21, $3A, $8A, $21, $8A, $21, $3A, $56, $3A, $56, $56, $10, $02, $9C, $67, $89, $1A, $30, $50, $1D, $A3, $56, $3A, $56, $56, $5D, $6A, $23, $3F, $A2, $21, $90, $02, $9C, $CC, $A1, $24, $8A, $13, $8A, $21, $3A, $56, $11, $FA, $81, $21, $82, $21, $34, $56, $3A, $56, $56, $67, $89, $1A, $30, $50, $1D, $A3, $5D, $6A, $23, $3F, $A2, $21, $90, $02, $9C, $CC, $02, $9C, $CC, $A1, $24, $A1, $24, $8A, $21, $3A, $8A, $21, $8A, $21, $3A, $56, $3A, $56, $56, $10, $02, $9C, $CC, $10, $02, $9C, $CC, $CC, $20, $2D, $8D, $54, $B1, $5C, $7F, $CC, $AA, $34, $52, $51, $11, $AB, $44, $3A, $56, $8A, $21, $3A, $56, $AC, $7A, $AC, $7A, $1D, $2D, $1D, $2D, $5F, $11, $C8, $12, $E2, $A1, $E2, $A1, $24, $10, $C8, $24, $10, $C8, $56, $8A, $21, $3A, $3A, $56, $56, $3A, $56, $56, $C3, $56, $C3, $4A, $5D, $C3, $4A, $5D, $AC, $7A, $1D, $2D, $5F, $11, $C8, $A0, $F0, $3A, $56, $AC, $7A, $1D, $2D, $5F, $11, $C8, $12, $E2, $13, $8A, $21, $3A, $56, $A1, $56, $A1, $24, $56, $A1, $24, $E2, $A1, $E2, $A1, $24, $E2, $A1, $24, $10, $C8, $10, $C8, $56, $8A, $21, $3A, $56, $C3, $4A, $5D, $C3, $4A, $5D, $A0, $F0, $D0, $56, $67, $89, $1A, $56, $A1, $24, $E2, $A1, $30, $D0, $56, $67, $89, $1A, $30, $55, $22, $7F, $CC, $AA, $34, $52, $34, $52, $51, $11, $51, $11, $AB, $44, $55, $22, $34, $53, $2A, $5B, $A1, $24, $10, $C8, $6F, $33, $C8, $12, $E2, $21, $7C, $FF, $AC, $7A, $C8, $12, $E2, $1D, $2D, $5F, $11, $8A, $21, $32, $56, $32, $56, $13, $5D, $13, $5D, $3A, $56, $56, $8A, $21, $3A, $56, $BA, $CB, $CD, $BD, $88, $3A, $56, $C3, $99, $AA, $99, $AA, $DD, $FF, $DD, $FF, $CC, $98, $56, $3A, $56, $56, $7D, $C3, $46, $78, $12, $C3, $56, $67, $89, $1A, $46, $78, $C3, $46, $78, $12, $44, $12, $44, $44, $6A, $BC, $DF, $E2, $32, $56, $13, $8A, $13, $8A, $21, $3A, $56, $21, $3A, $56, $C3, $4A, $5D, $C3, $34, $52, $51, $11, $4A, $5D, $A0, $F0, $D0, $30, $50, $1D, $A3, $5D, $6A, $23, $02, $9C, $CC, $3F, $CC, $3F, $CC, $3F, $A2, $21, $8D, $5F, $11, $56, $8A, $21, $A2, $21, $A2, $02, $9C, $CC, $A1, $24, $21, $90, $02, $9C, $CC, $56, $A1, $24, $E2, $A1, $A1, $24, $10, $C8, $12, $E2, $20, $2D, $8D, $54, $CC, $3F, $A2, $21, $51, $58, $A5

;; 1052 sayı var
begin:
	LXI SP,stack 		; always initialize the stack pointer
	MVI C, 1052       	;
outherLoop:
	LXI D, Array	; address array to registers D and E
	MVI H, 1052       	; h = 1052

innerLoop:	
	LDAX D              ; first elem a 
	MOV B, A            ; B = A
	INX	D 				; ++DE
	INX D 				; ++DE
	LDAX D 				; A <­ DE
	CMP	B    			; 
	JC swapping			; 

dec_HC:
	DCR	H 				; h-- inner loop
	JNZ innerLoop		; if not 0  go inner
	DCR C 				; c-- outter loop
	JNZ	outherLoop 		; if not 0  go outherLoop 
	JMP finishLoop      ; 

swapping:
	DCX D 				; --[DE]
	DCX D 				; --[DE]
	STAX D 				; [DE] = A
	INX D 				; ++[DE]
	INX D 				; ++[DE]
	MOV A, B 			; A = B
	STAX D 				; [DE] = A
	JMP dec_HC   ;	

finishLoop:
	MVI C, 1052         ; ekrana basmak icin tekrardan c ye 26 yuklenir
	LXI D, Array    ; addres of array
	MVI A, PRINT_B		; system call print_b
PrintArray:
	LDAX D			    ; A = [DE]
	MOV B, A   		    ; B = A
	call GTU_OS			; call OS
	INX D				; ++[DE]
	INX D				; ++[DE]
	DCR C				; --C
	JNZ PrintArray		;
	HLT					;
