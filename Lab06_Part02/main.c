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

#define SW1 !(P1IN & BIT0)
#define SW2 !(P1IN & BIT1)


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Setup clock
	FLL_CTL0 |= DCOPLUS | XCAP18PF;	// Set capacitance and DCO multiply
	SCFI0 |= FN_2;      			// Set DCO range
	SCFI0 &= ~FLLD_8;               // Set divide value to 1
	SCFQCTL = 63;					// (64 + 1) * 32768 = 2097152 MHz
	
	// Setup parallel ports
	P1DIR &= ~(BIT0 | BIT1);// Set P1.0 and P1.1 to input for SW1 and SW2
	P2DIR |= BIT1;			// Set P2.1 to output for LED2
	
	// Setup interrupts
	_EINT();
	P1IE |= BIT0 | BIT1;	// Enable interrupts for P1.0 and P1.1 for SW1 and SW2
	P1IES |= BIT0 | BIT1;	// Set interrupts for high low edge
	P1IFG &= ~(BIT0 | BIT1);// Clear interrupt bit for SW1 and SW2
	
	// Main loop
	for(;;)
	{
		_delay_cycles(1048576);	// Delay for 1048576 cycles
		P2OUT ^= BIT1;			// Toggle LED2
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
	if(SW1)
	{
	    SCFI0 &= ~FLLD_8;
		SCFI0 |= FLLD_2;
	}
	if(SW2)
	{
	    SCFI0 &= ~FLLD_8;
        SCFI0 |= FLLD_4;
	}
	P1IFG &= ~BIT0;
    P1IFG &= ~BIT1;
}
