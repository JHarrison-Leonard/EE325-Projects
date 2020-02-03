;-------------------------------------------------------------------------------
; File:        main.asm
; Function:    Converts a multiplcation string "a*b" to a byte and outputs it
;              to port 2
; Description: Performs the function by obtaining the two values, a and b, and
;              stores them to R5 and R6 ensuring that R5 is less than R6.
;              Multiplation is performed by adding R6 to an initally empty
;              register R5 number of times.
; Input:       Input str is hardcoded as inputStr
; Output:      Outputs a single byte to port 2
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

inputStr:	.cstring "6*9"

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		bis.b	#0xFF, &P2DIR			; Set Port 2 to output
			mov.w	#inputStr, R4			; Point R4 to inputStr
			mov.b	#0xFF, R7				; Set failure output to 0xFF
			call	#getNum					; Call getNum
			jnz		#strFail				; If string was invalid, go to strFail
			mov.b	#'*', R10				; Test last character
			cmp.b	R10, R9					; If last character wasn't '*'
			jne		#strFail				; Then string invalid, go to strFail
			mov.w	R6, R5					; move getNum output to R5
			call	#getNum					; Call getNum
			jz		#strFail				; If string was invalid, go to strFail
			mov.b	#0x00, R10				; Test last character
			cmp.b	R10, R9					; If last character wasn't NULL
			jne		#strFail				; Then string invalid, go to strFail
			cmp.w	R5, R6					; Move R5 and R6 to ensure R5 < R6
			jge		#multiply				; ^
			mov.w	R5, R7					; ^
			mov.w	R6, R5					; ^
			mov.w	R7, R6					; ^
multiply:	clr.w	R7						; output = R5 * R6
mLoop:		add.w	R6, R7					; By adding R5 to output
			dec.w	R5						; R5 number of times
			jnz		#mLoop					; ^
strFail:									; If str was invalid, then output is already 0xFF
output:		bis.b	R7,	&P2OUT				; Output R7 to port 2

done:		jmp		#done					; End of process

											; getNum sub-process
											; Expects char pointer in R4
											;   Stores numeric value of string
											; up until NULL or '*' into R8
											; Increments R4
											; Sets Z to 0 if string is invalid
											; Sets Z to 1 if string is valid
											; Volatilely uses R10
getNum:		clr		R8						; Clear output register
gnLoop:		call	#isNum					; Call isNum
			jnz		#gnExit					; If next char isn't numeric, exit gnLoop
			mov.w	#10, R9					; Multiply output register by 10
			clr		R10						; ^
gnMLoop:	add.w	R8, R10					; ^
			dec.w	R9						; ^
			jnz		#gnMLoop				; ^
			mov.w	R10, R8					; ^
			sub.b	#'0', R9				; Convert numeric char to integer
			add.w	R9, R8					; Add next digit to output
			jmp		#gnLoop					; Continue gnLoop until non-numeric number
gnExit:		cmp.b	#'*', R9				; If last char was either '*' or NULL
			jeq		#gnSucc					; then return success as Z is 1
			cmp.b	#0x00, R9				; else, Z will be 0
gnSucc	:	ret								; Return

											; isNum sub-process
											; Expects char pointer in R4
											; Stores next char to R9, incrementing R4
											; Sets Z to 0 if char isn't numeric
											; Sets Z to 1 if char is numeric
isNum:		mov.b	@R4+, R9				; Stores next char from R4 into R9
			cmp.b	#'0', R9				; R9 < '0'
			jl		#inF					; not numeric
			cmp.b	#'9'+1, R9				; '0' <= R9 <= '9'
			jl		#inT					; is numeric
			clrz							; Clear Z as char could be '9'+1
			ret								; Return
inT:		setz							; Set Z for is numeric
inF:		ret								; Return, Z is already 0 if jl ran

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
