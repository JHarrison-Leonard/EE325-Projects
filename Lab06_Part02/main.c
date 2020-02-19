/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Flashes LED2 at 3 different rates: 1 Hz initially, 2 Hz after
 *              SW1 is pressed, and 4 Hz after SW2 is pressed.
 * Input:       Takes inputs SW1 and SW2
 * Output:      Gives output on LED2
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        February 21st, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>

#define SW1 !(P1IN & BIT0)
#define SW2 !(P1IN & BIT1)
#define SW1IFG (P1IFG & BIT0)
#define SW2IFG (P1IFG & BIT1)


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Setup clock
	FLL_CTL0 |= DCOPLUS | XCAP18PF;	// Set capacitance and DCO multiply
	SCFI0 |= FN_2;      			// Set DCO range
	SCFI0 &= ~FLLD_8;               // Set divide value to 1
	SCFQCTL = 63;					// (63 + 1) * 1 * 32768 = 2097152 Hz ~ 2 MHz
	
	// Setup parallel ports
	P1DIR &= ~(BIT0 | BIT1);		// Set P1.0 and P1.1 to input for SW1 and SW2
	P2DIR |= BIT1;					// Set P2.1 to output for LED2
	
	// Setup interrupts
	_EINT();						// Enable global interrupts
	P1IE |= BIT0 | BIT1;			// Enable interrupts for P1.0 and P1.1 for SW1 and SW2
	P1IES |= BIT0 | BIT1;			// Set interrupts for high low edge
	P1IFG &= ~(BIT0 | BIT1);		// Clear interrupt bit for SW1 and SW2
	
	// Main loop
	for(;;)
	{
		_delay_cycles(1048576);		// Delay for 1048576 cycles
		P2OUT ^= BIT1;				// Toggle LED2
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
	if(SW1IFG)
	{
		SCFI0 &= ~FLLD_8;			// Clear divide value (set to 1)
		SCFI0 |= FLLD_2;			// Set divide value to 2
	}								// (63 + 1) * 2 * 32768 = 4194304 Hz ~ 4 MHz
	if(SW2IFG)
	{
		SCFI0 &= ~FLLD_8;			// Clear divide value (set to 1)
		SCFI0 |= FLLD_4;			// Set divide value to 4
	}								// (63 + 1) * 4 * 32768 = 8388608 Hz ~ 8 MHz
	P1IFG &= ~(BIT0 | BIT1);		// Clear interrupt flag for SW1 and SW2
}
