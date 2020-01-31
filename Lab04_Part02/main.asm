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
			call	#getNum					;
			jz		strFail					;
			mov.b	#'*', R5				;
			cmp.b	@R4+, R6				;
			jne		strFail					;
			mov.w	R6, R5					;
			call	#getNum					;
			jz		strFail					;
			cmp.w	R5, R6					;
			jge		multiply				;
			

getNum:		

isNum:		

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
