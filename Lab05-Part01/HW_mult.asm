;-------------------------------------------------------------------------------
; File:        HW_mult.asm
; Function:    [Does...
; Description: [Does that by...
; Input:       [Takes inputs...
; Output:      [Gives outputs...
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        February 11th, 2020
;-------------------------------------------------------------------------------
			.cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
			.def	HW_mult					; Export sub-process entry-point to
 											; make it known to linker.
;-------------------------------------------------------------------------------
			.text

HW_mult:	push	R4						;
			push	R5
			mov.w	-6(SP), R4				; Obtain argument 1
			mov.w	-8(SP), R5				; Obtain argument 2
			clr		R13						; Clear output
loop:		dec.w	R5
			jge		exit
			mov.w	@R4, &MPY
			mov.w	@R4+, &OP2
			add.w	&RESLO, R13
			jmp		loop
exit:		pop R5							;
			pop R4
			ret								;


;-------------------------------------------------------------------------------
			.end
