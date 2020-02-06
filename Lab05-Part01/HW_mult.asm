;-------------------------------------------------------------------------------
; File:        HW_mult.asm
; Function:    Obtains the sum of squares of the integers in an array
; Description: Function performed by iterating through the array and using the
;              hardware multiplier to perform the square and adding the results
;              to an output register
; Input:       Given by the stack in ascending order (e.g. &arg1 < &arg2)
;              arg1: Pointer to integer array
;              arg2: Size of array
; Output:      R13: Sum of the squares as an unsigned integer
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

HW_mult:	push	R4						; Place register contents on stack
			push	R5
			mov.w	6(SP), R4				; Obtain argument 1
			mov.w	8(SP), R5				; Obtain argument 2
			clr		R13						; Clear output
loop:		dec.w	R5						;{ Iterating through array
			jge		exit					;  Exiting loop when array fully iterated
			mov.w	@R4, &MPYS				;  Set operand 1 of signed multiply to element
			mov.w	@R4+, &OP2				;  Set operand 2 to element
			add.w	&RESLO, R13				;  Accumulate result in R13
			jmp		loop					;} Continue looping through loop
exit:		pop R5							; Retrieve register contents from stack
			pop R4
			ret								; Return


;-------------------------------------------------------------------------------
			.end
