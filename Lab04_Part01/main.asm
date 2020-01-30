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

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

inputStr:	.cstring "Hello! Welcome to CPE325. It is a great day, is it not?"

			.data
sentCount:	.word 0							; Sentence count
wordCount:	.word 0							; Word count

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		mov.w	#inputStr, R4			; R4 points to inputStr
			mov.w	#sentCount, R5			; R5 points to sentCount
			mov.w	#wordCount, R6			; R6 points to wordCount
sLoopNW:	cmp.b	#0x00, 0(R4)			;
			jz		sLoopEnd				;
			call	#isalnum				;
			jnz		sLoopNW					;
			inc.w	0(R6)					;
sLoopNNW:	call	#isalnum				;
			jz		sLoopNNW				;
			cmp.b	#'.', -1(R4)			;
			jeq		incSent					;
			cmp.b	#'!', -1(R4)			;
			jeq		incSent					;
			cmp.b	#'?', -1(R4)			;
			jeq		incSent					;
			jmp		sLoopNW					;
incSent:	inc.w	0(R5)					;
			jmp		sLoopNW					;

sLoopEnd:	jmp		sLoopEnd				;

isalnum:	mov.b	@R4+, R7				;
			cmp.b	#'0', R7				;
			jl		isanF					;
			cmp.b	#'9'+1, R7				;
			jl		isanT					;
			cmp.b	#'A', R7				;
			jl		isanF					;
			cmp.b	#'Z'+1, R7				;
			jl		isanT					;
			cmp.b	#'a', R7				;
			jl		isanF					;
			cmp.b	#'z'+1, R7				;
			jl		isanT					;
			clrz							;
			ret								;
isanT:		setz							;
isanF:		ret								;

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
            
