;-------------------------------------------------------------------------------
; File:        main.asm
; Function:    Determines the number of words and sentences in a given string
; Description: Function performed by incrementing through string and
;              counting words as connected groups of alpha-numeric characters
;              and counting sentences as sentence terminators ('.', '!', and '?'
;              ) immediately following a word
; Input:       Input string hardcoded as inputStr
; Output:      Outputs given in RAM as sentCount and wordCount
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        Febuary 4th, 2020
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.

			.data							; Assemble into RAM
sentCount:	.word 0							; Sentence count
wordCount:	.word 0							; Word count

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

inputStr:	.cstring "Hello! Welcome to CPE325. It is a great day, is it not?"

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		mov.w	#inputStr, R4			; R4 points to inputStr
			mov.w	#sentCount, R5			; R5 points to sentCount
			mov.w	#wordCount, R6			; R6 points to wordCount
sLoopNW:	cmp.b	#0x00, 0(R4)			; Searching for first word: Is current character NULL
			jz		sLoopEnd				; If yes, end loop
			call	#isalnum				; Call isalnum to get and test next char
			jnz		sLoopNW					; If character is not alpha-numeric, continue searching
			inc.w	0(R6)					; Else, count a word
sLoopNNW:	call	#isalnum				; Searching for end of word: Call isalnum to get and test next char
			jz		sLoopNNW				; If character is alpha-numeric, continue searching
			cmp.b	#'.', -1(R4)			; Test for sentence terminators:
			jeq		incSent					; '.', '!', or '?'
			cmp.b	#'!', -1(R4)			; If yes, count a sentence
			jeq		incSent					;
			cmp.b	#'?', -1(R4)			;
			jeq		incSent					;
			jmp		sLoopNW					; After testing for sentence terminator
incSent:	inc.w	0(R5)					; Continue searching for next word
			jmp		sLoopNW					;

sLoopEnd:	jmp		sLoopEnd				; End of program

											; isalnum sub-process
											; Expects input of char pointer in R4
											; Sets Z bit to 0 if char is not alpha-numeric
											; Sets Z bit to 1 if char is alpha-numeric
											; Increments R4
isalnum:	mov.b	@R4+, R7				; Obtain next character in string
			cmp.b	#'0', R7				; c < '0'
			jl		isanF					; not alnum
			cmp.b	#'9'+1, R7				; '0' <= c <= '9'
			jl		isanT					; is alnum
			cmp.b	#'A', R7				; '9' < c < 'A'
			jl		isanF					; not alnum
			cmp.b	#'Z'+1, R7				; 'A' <= c <= 'Z'
			jl		isanT					; is alnum
			cmp.b	#'a', R7				; 'Z' < c < 'a'
			jl		isanF					; not alnum
			cmp.b	#'z'+1, R7				; 'a' <= c < = 'z'
			jl		isanT					; is alnum
			clrz							; Set Z to 0 as char could be 'z'+1
			ret								; Return
isanT:		setz							; Set Z to 1 as char might not be 1
isanF:		ret								; Return, jl ensures that Z is 0 already

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
            
