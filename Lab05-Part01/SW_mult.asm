;-------------------------------------------------------------------------------
; File:        SW_mult.asm
; Function:    [Does...
; Description: [Does that by...
; Input:       [Takes inputs...
; Output:      [Gives outputs...
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        February 11th, 2020
;-------------------------------------------------------------------------------
			.cdecls C,LIST,"msp430.h"		; Include device header file

;-------------------------------------------------------------------------------
 			.def	SW_mult					; Export sub-process entry-point to
											; make it known to linker.
;-------------------------------------------------------------------------------
			.text

SW_mult:	push	R4							;
			push	R5
			push	R6
			push	R7
			push	R8
			mov.w	12(SP), R4					; Obtain argument 1
			mov.w	14(SP), R5					; Obtain argument 2
			clr		R12							; Clear output
mLoop:		dec.w	R5
			jge		exit
			mov.w	@R4+, R6
			mov.w	R6, R7
			mov.w	#16, R8
nLoop:		bit.w	#0x01, R7
			jz		skipA
			add.w	R6, R12
skipA:		rla.w	R6
			rra.w	R7
			dec.w	R8
			jge		nLoop
			bit.w	#0x01, R7
			jz		skipS
			sub.w	R6, R8
			add.w	R8, R12
			jmp		mLoop
exit:		pop		R8							;
			pop		R7
			pop		R6
			pop		R5
			pop		R4
			ret									;


;-------------------------------------------------------------------------------
			.end
