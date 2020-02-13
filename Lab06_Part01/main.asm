;-------------------------------------------------------------------------------
; File:        main.asm
; Function:    [Does...
; Description: [Does that by...
; Input:       [Takes inputs...
; Output:      [Gives outputs...
; Author:      Justin H. Leonard
; Lab section: 04
; Date:        [Due...
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

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main
;-------------------------------------------------------------------------------
main:		bic.b	#BIT1, &P1DIR			; Set P1.1 to input for SW2
			bis.b	#BIT1&BIT2, &P2DIR		; Set P2.1 and P2.2 to output for LED1 and LED2
			mov.w	#WDT_ADLY_1000, &WDTCTL	; Set watchdog timer to 1s timer mode
			nop
			bis.w	#GIE, SR				; Enable global interrupts
			nop
			bis.b	#BIT1, &P1IE			; Enable P1.1 interrupt for SW2
			bis.b	#BIT1, &P1IES			; P1.1 interrupt from high to low
			bic.b	#BIT1, &P1IFG			; Clear interrupt flag for P1.1
			bis.b	#WDTIE, &IE1			; Enable watchdog timer interrupts
			bic.b	#WDTIFG, &IFG1			; Clear interrupt flag for watchdog timer

mLoop:		call	msDelay					; Delay for 1 ms
			; logic
			jmp		mLoop					; Loop forever


msDelay:	ret


;-------------------------------------------------------------------------------
; P1.X interrupt service routine
;-------------------------------------------------------------------------------
P1_ISR:
			bic.b	#BIT1, &P1IE			; Disable interrupts for P1.1
			bic.b	#BIT1, &P1IFG			; Clear interrupt flag
			xor.b	#BIT1, &P2OUT			; Toggle LED2
			; Debounce logic
			reti


;-------------------------------------------------------------------------------
; WDT interrupt service routine
;-------------------------------------------------------------------------------
WDT_ISR:
			bic.b	#WDTIFG, &IFG1			; Clear interrupt flag
			xor.b	#BIT2, &P2OUT			; Toggle LED1
			reti


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
            .sect	".int20"				; P1.X vector
            .short	P1_ISR
            .sect	".int26"				; Watchdog timer vector
            .short	WDT_ISR
            .end
