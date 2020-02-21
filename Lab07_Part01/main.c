/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: [Does...
 * Input:       [Takes inputs...
 * Output:      [Gives outputs...
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        [Due...
 *---------------------------------------------------------------------------*/
#include <msp430.h>

#define SW1IFG (P1IFG & BIT0)
#define SW2IFG (P1IFG & BIT1)


int main(void)
{
	// Peripheral setup
	WDTCTL = WDT_XXX;			// WDT with XXX interval
	TB1CCTL0 = OUTMOD_7;		//
	TB1CTL = TBSSEL_1 + MC_1;	//
	TB1CCR0
	P1DIR &= ~(BIT0 | BIT1);	// Set SW1 and SW2 (P1.0,1) to input
	P2DIR |= BIT2;				// Set LED1 (P2.2) to output
	P2SEL |= BIT2;				// Set LED1 to special mode (TB1)
	
	// Interrupt setup
	_EINT();					// Enable global interrupts
	P1IE |= (BIT0 | BIT1);		// Enable interrupts for SW1 and SW2
	P1IES |= (BIT0 | BIT1);		// SW1 and SW2 interrupt from high to low
	P1IFG &= ~(BIT0 | BIT1);	// Clear interrupt flag for SW1 and SW2
	IE1 |= WDTIE;				// Enable WDT interrupts
	IFG1 &= WDTIFG;				// Clear interrupt flag for WDT
	
	// Enter sleep
	_BIS_SR(LPM0_bits + GIE);
	
	// Default return if it exits sleep for some reason
	return 0;
}

#pragma vecotr = PORT1_VECTOR
__interrupt void Port1_ISR()
{
	
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
	
}


