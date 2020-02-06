;-------------------------------------------------------------------------------
; File:        StrToInt.asm
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
 			.def	StrToInt				; Export sub-process entry-point to
											; make it known to linker.
;-------------------------------------------------------------------------------
			.text

SW_mult:	push	R4							; Place register contents on stack
			push	R5
			push	R6
			mov.w	6(SP), R4					; Obtain argument 1 (String pointer)
			mov.w	8(SP), R5					; Obtain argument 2 (Output pointer)
			clr		&RESLO						; Clear multiplier output
			mov.b	@R4+, R6					; Get first char of string
			cmp.b	#'-', R6					; Test if first char is a '-'
			jne		mLoop						; If not, then skip the negation
			mov.w	#-10, &MACS
			mov.b	@R4+, R6
			sub.b	#'0', R6
			mov.w	R6, &OP2
			mov.b	@R4+, R6
mLoop:		cmp.b	#0x00, R6
			jeq		exit
			sub.b	#'0', R6
			mov.w	R6,
exit:
			pop		R6							; Retrieve register contents from stack
			pop		R5
			pop		R4
			ret									; Return


;-------------------------------------------------------------------------------
			.end
