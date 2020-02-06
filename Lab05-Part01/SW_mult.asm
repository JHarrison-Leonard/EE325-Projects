;-------------------------------------------------------------------------------
; File:        SW_mult.asm
; Function:    Obtains the sum of the squares of the integers in an array
; Description: Function performed by iterating through the array and for each
;              each element, making positive if negative as squaring removes
;              signage, uses a shift based multiplaction method for squaring,
;              and adds all of these squares into an output register.
; Input:       Given by the stack in ascending order (e.g. &arg1 < &arg2)
;              arg1: Pointer to integer array
;              arg2: Size of array
; Output:      R12: Sum of the squares as an unsigned integer
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

SW_mult:	push	R4							; Place register contents on stack
			push	R5
			push	R6
			push	R7
			push	R8
			mov.w	12(SP), R4					; Obtain argument 1 (Array pointer)
			mov.w	14(SP), R5					; Obtain argument 2 (Size of array)
			clr		R12							; Clear output
mLoop:		dec.w	R5							;{ Iterating through array
			jl		exit						;  Exiting mLoop when array fully iterated
			mov.w	@R4+, R6					;  Get element from array
			cmp.w	#0, R6						;  Testing if element is negative
			jge		skipNeg						;  Skipping negation if positive
			inv.w	R6							;  Perform 2's compliment to invert
			add.w	#1, R6						;  ^
skipNeg:	mov.w	R6, R7						;  Duplicate that element
			mov.w	#16, R8						;  Iterating through each bit in element
nLoop:		bit.w	#0x01, R7					; { Testing for first bit in B
			jz		skipA						;   Skipping addition if first bit is 0
			add.w	R6, R12						;   Adding A to C if first bit is 1
skipA:		rla.w	R6							;   Shift A left
			rra.w	R7							;   Shift B right
			dec.w	R8							;   Decrement bit counter
			jge		nLoop						; } Exiting nLoop when all bits iterated
			jmp		mLoop						;} Continue looping through mLoop
exit:		pop		R8							; Retrieve register contents from stack
			pop		R7
			pop		R6
			pop		R5
			pop		R4
			ret									; Return


;-------------------------------------------------------------------------------
			.end
