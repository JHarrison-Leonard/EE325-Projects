;-------------------------------------------------------------------------------
; File:        main.asm
; Function:    Tests that a given string is palidromic, case insensitive
; Description: Iterating through the beginning and end of the string towards
;              the center. For each character pair of beginning and end,
;              converts to lowercase if applicable and compares for equality.
; Input:       Input string harded as inputStr
; Output:      Outputs to the beginning of RAM as paliBool
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        Febuary 4th, 2020
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.

			.data
paliBool:	.byte	'N'					; Output file

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

inputStr:	.string	"20200202"				;
inputStrE:									;

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		mov.w	#inputStr, R4			; Pointer to first char
			mov.w	#inputStrE-1, R5		; Pointer to last char
			mov.w	#inputStrE-inputStr, R6	; Size of inputStr
			rra.w	R6						; Half the size
mLoop:		call	#paliCmp				; Compare characters (case insensitive)
			jnz		paliNo					; Jump out if not palindromic
			dec.w	R5						; Shift pointers towards center
			dec.w	R6						; Decrement count
			jnz		mLoop					; Loop through full string
			mov.b	#'Y', paliBool			; If palindromic, set paliBool to Y
paliNo:										; Default value of paliBool is already 'N', free to end

done:		jmp		done					; End of process

											; Sub-process paliCmp
											; Expects R4 to point to the beginning of the uncompared string
											; Increments R4
											; Expects R5 to point to the end of uncompared string
											; Set Z to 0 if not palindromic
											; Set Z to 1 if palindromic
											; Case insensitive
paliCmp:	mov.b 	@R4+, R7				; Obtain first char
			mov.b	@R5, R8					; and last char
			cmp.b	#'A', R7				; If first char is upper case
			jl		pC7UF					; make it lower case
			cmp.b	#'Z'+1, R7				; ^
			jge		pC7UF					; ^
			add.b	#'a'-'A', R7			; ^
pC7UF:		cmp.b	#'A', R8				; If last char is upper case
			jl		pC8UF					; make it lower case
			cmp.b	#'Z'+1, R8				; ^
			jge		pC8UF					; ^
			add.b	#'a'-'A', R8			; ^
pC8UF:		cmp.b	R7, R8					; Compare lowercased chars
			ret								; Return

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
            
