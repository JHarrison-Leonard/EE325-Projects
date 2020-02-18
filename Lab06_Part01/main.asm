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
			bis.b	#BIT1|BIT2, &P2DIR		; Set P2.1 and P2.2 to output for LED1 and LED2
			mov.w	#WDT_ADLY_1000, &WDTCTL	; Set watchdog timer to 1s timer mode

			nop
			bis.w	#GIE, SR				; Enable global interrupts
			nop
			bis.b	#BIT1, &P1IE			; Enable P1.1 interrupt for SW2
			bis.b	#BIT1, &P1IES			; SW2 interrupt from high to low
			bic.b	#BIT1, &P1IFG			; Clear interrupt flag for SW2
			bis.b	#WDTIE, &IE1			; Enable watchdog timer interrupts
			bic.b	#WDTIFG, &IFG1			; Clear interrupt flag for watchdog timer

			clr		R4						; Clear debounce press counter
			clr		R5						; Clear debounce release counter
mLoop:		call	#msDelay				; Delay for 1 ms
			cmp.w	#0, R4					; Test if press counter is not zero
			jz		pSkip					; Skip press debounce logic otherwise
			dec.w	R4						; Decrement pressed counter
			jnz		mLoop					; Relooping if not zero
			mov.w	#20, R5					; Set release counter to 20
			jmp		mLoop					; Relooping
pSkip:		cmp.w	#0, R5					; Test if release counter is not zero
			jz		mLoop					; Relooping otherwise
			bit.b	#BIT1, &P1IN			; Test if SW2 is released
			jz		mLoop					; Relooping otherwise
			dec.w	R5						; Decrement release counter
			jnz		mLoop					; Relooping if not zero
			bic.b	#BIT1, &P1IFG			; Clear interrupt flags for SW2
			bis.b	#BIT1, &P1IE			; Enable interrupts for SW2
			jmp		mLoop					; Relooping


msDelay:	mov.w	#100, R6				; Software delay (100*10cc/F_CPU ~ 1 ms)
MSDLoop		nop								; 1cc x 7
			nop
			nop
			nop
			nop
			nop
			nop
			dec.w	R6						; 1cc
			jnz		MSDLoop					; 2cc
			ret								; Return


;-------------------------------------------------------------------------------
; P1.X interrupt service routine
;-------------------------------------------------------------------------------
P1_ISR:
			bic.b	#BIT1, &P1IE			; Disable interrupts for SW2
			bic.b	#BIT1, &P1IFG			; Clear interrupt flag
			xor.b	#BIT1, &P2OUT			; Toggle LED2
			mov.w	#20, R4					; Set pressed counter to 20
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
