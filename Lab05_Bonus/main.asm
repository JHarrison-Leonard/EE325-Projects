;-------------------------------------------------------------------------------
; File:        main.asm
; Function:    Obtains the decimal for a given input string that is assumed to
;              be properly formatted, at least 5 digits, and no more than 16
;              bits in output size.
; Description: Function performed by calling a sub-process defined in a seperate
;              file labled "StrToInt".
; Input:       Decimal string defined as deciString
; Output:      Decimal value stored to deciVal
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        February 11th, 2020
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.

			.ref	StrToInt				; Reference StrToInt sub-process

deciVal:	.word 0							; Output variable

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

deciString:	.cstring "12345"				; Input string

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		push	deciVal					; Argument 2 of StrToInt
			push	deciToString			; Argument 1 of StrToInt
			call	#StrToInt				; Call StrToInt
			add.w	#4, SP					; Clean arguments off stack

EOP:		jmp		EOP						; End of process


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
            
