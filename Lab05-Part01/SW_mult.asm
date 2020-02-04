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

SW_mult:	ret


;-------------------------------------------------------------------------------
			.end
