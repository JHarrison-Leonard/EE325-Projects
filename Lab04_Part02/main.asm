;-------------------------------------------------------------------------------
; File:        main.asm
; Function:    [Does...
; Description: [Does that by...
; Input:       [Takes inputs...
; Output:      [Gives outputs...
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        Febuary 4th, 2020
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

inputStr:	.cstring "6*9"

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		bis.b	#0xFF, &P1DIR			;
			mov.w	#inputStr, R4			;
			mov.w	#0xFF, R7				;
			call	#getNum					;
			jnz		#strFail				;
			mov.b	#'*', R10				;
			cmp.b	R5, R9					;
			jne		strFail					;
			mov.w	R6, R5					;
			call	#getNum					;
			jz		#strFail				;
			mov.b	#0x00, R10				;
			cmp.b	R10, R9					;
			jne		#strFail				;
			cmp.w	R5, R6					;
			jge		multiply				;
			mov.w	R5, R7					;
			mov.w	R6, R5					;
			mov.w	R7, R6					;
multiply:	clr.w	R7						;
mLoop:		add.w	R6, R7					;
			dec.w	R5						;
			jnz		#mLoop					;
strFail:	
output:		bis.b	R7,	&P2OUT				;
done:		jmp		#done					;

getNum:		clr		R8						;
gnLoop:		mov.w	#10, R9					;
			clr		R10						;
			add.w	R8, R10					;
			dec.w	R9						;
			jnz		#gnLoop					;
			mov.w	R10, R8					;
			call	#isNum					;
			jnz		#gnExit					;
			sub.b	#'0', R9				;
			add.w	R9, R8					;
			jmp		#gnLoop					;
gnExit:		cmp.b	#'*', R9				;
			jeq		#gnSucc					;
			cmp.b	#0x00, R9				;
gnSucc	:	ret								;

isNum:		mov.b	@R4+, R9				;
			cmp.b	#'0', R9				;
			jl		#inF					;
			cmp.b	#'9'+1, R9				;
			jl		#inT					;
			clrz							;
			ret								;
inT:		setz							;
inF:		ret								;

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack

;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
