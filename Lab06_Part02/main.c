/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: [Does...
 * Input:       [Takes inputs...
 * Output:      [Gives outputs...
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        February 20th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include "main.h"


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Setup clock
	FLL_CTL0 |= XCAP18PF	// Set capacitance
	SCFI0 |= FN_2			// Set DCO range
	SCFQCTL = 64			// (64 + 1) * 32768 = 2097152 MHz
	
	// Setup parallel ports
	P1DIR &= ~(BIT0 | BIT1)	// Set P1.0 and P1.1 to input for SW1 and SW2
	P2DIR |= BIT1			// Set P2.1 to output for LED2
	
	// Main loop
	for(;;)
	{
		_delay_cycles(1048576);	// Delay for 1048576 cycles
		P2OUT ^= BIT1			// Toggle LED2
	}
	
	// Default return
	return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
	
}
