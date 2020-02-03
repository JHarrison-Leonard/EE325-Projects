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

			.data
painBool:	.byte	'N'						;

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
mLoop:		rra.w	R6						; Half the size
			cmp.b	@R4+, 0(R5)				; Compare characters
			jnz		#paliNo					; Jump out if not palindromic
			dec.b	R5						; Shift pointers towards center
			dec.w	R6						; Decrement count
			jnz		#mLoop					; Loop through full string
			mov.b	#'Y', &paliBool			; If palindromic, set paliBool to Y
paliNo:		
done:		jmp		#done					;

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
            
