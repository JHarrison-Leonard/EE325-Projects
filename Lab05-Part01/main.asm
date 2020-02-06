;-------------------------------------------------------------------------------
; File:        main.asm
; Function:    Obtains the sum of the squares for an integer array using two
;              different methods: A software algorithm for multiplication and
;              the hardware multiplier.
; Description: Function performed by calling sub-processes SW_mult for the
;              software algorithm and HW_mult for the hardware method.
; Input:       Integer array defined at inputArr
;              Size of array defined at iALength
; Output:      Software algorithm output stored to R12
;              Hardware solution output stored to R13
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        February 11th, 2020
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.

			.ref	SW_mult					; Reference SW_mult sub-process
			.ref	HW_mult					; Reference HW_mult sub-process
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

inputArr:	.int 1 2 3 4 5					; Input array of integers
iALength:	.word 5							; Length of inputArr

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		push	iAlength				; Argument 2 of SW_mult
			push	#inputArr				; Argument 1 of SW_mult
			call	#SW_mult				; Call SW_mult
			add.w	#4, SP					; Clean arguments off stack
			push	iAlength				; Argument 2 of HW_mult
			push	#inputArr				; Argument 1 of HW_mult
			call	#HW_mult				; Call HW_mult
			add.w	#4, SP					; Clean arguments off stack

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
            
