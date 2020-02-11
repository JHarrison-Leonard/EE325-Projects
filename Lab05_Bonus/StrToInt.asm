;-------------------------------------------------------------------------------
; File:        StrToInt.asm
; Function:    Converts a 5 digit string to it's integer value
; Description: Function performed by interating through the string and
;              multiplying each converted character by 10^n where n is each
;              char's corresponding location in the string corrected by a '-'
;              if applicable. If a '-' is present at the beggining of the
;              string, uses 2's compliment to negate the output value before
;              outputing it to the inputted variable location.
; Input:       Given by the stack in ascending order (e.g. &arg1 < &arg2)
;              arg1: Pointer to string
;              arg2: Pointer to output variable
; Output:      0(arg2): Converted string as a signed integer
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        February 11th, 2020
;-------------------------------------------------------------------------------
			.cdecls C,LIST,"msp430.h"			; Include device header file

;-------------------------------------------------------------------------------
 			.def	StrToInt					; Export sub-process entry-point to
												; make it known to linker.
;-------------------------------------------------------------------------------
			.text

StrToInt:	push	R4							; Place register contents on stack
			push	R5
			push	R6
			mov.w	6(SP), R4					; Obtain argument 1 (String pointer)
			mov.w	8(SP), R5					; Obtain argument 2 (Output pointer)
			clr		&RESLO						; Clear multiplier output
			mov.b	@R4+, R6					; Get first char of string
			cmp.b	#'-', R6					; Test if first char is a '-'
			jne		bulk						; If not, skip negative
			mov.b	@R4+, R6					; Get next char, negative denoted as Z bit
bulk:		push	SR							; Preserve Z bit from negative test
			sub.b	#'0', R6					; Convert char to integer
			mov.w	R6, &MAC					; Move to OP1 of hardware multiplier, set to accumulate
			mov.w	#10000, &OP2				; Move 10^4 to second operand
			mov.b	@R4+, R6					; Get next char
			sub.b	#'0', R6					; Convert to integer
			mov.w	R6, &MAC					; Repeating for all but last digit
			mov.w	#1000, &OP2
			mov.b	@R4+, R6
			sub.b	#'0', R6
			mov.w	R6, &MAC
			mov.w	#100, &OP2
			mov.b	@R4+, R6
			sub.b	#'0', R6
			mov.w	R6, &MAC
			mov.w	#10, &OP2
			mov.b	@R4+, R6					; Obtain last digit
			sub.b	#'0', R6					; Convert to integer
			add.w	&RESLO, R6					; Add accumulated integer
			pop		SR							; Retrieve Z bit
			jnz		exit						; Jump to exit if not negative
			inv.w	R6							; Perform 2's compliment on output value
			inc.w	R6
exit:		mov.w	R6, 0(R5)					; Move output value to output variable
			pop		R6							; Retrieve register contents from stack
			pop		R5
			pop		R4
			ret									; Return


;-------------------------------------------------------------------------------
			.end
