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
	WDTCTL = WDT_ADLY_16;		// WDT with 16 ms ACLK interval
	TB0CCTL1 = OUTMOD_7;		// Reset/Set output mode
	TB0CTL = TBSSEL_1 | MC_1;	// ACLK clock source and Up mode
	TB0CCR0 = 188;				// 32768 / 188 ~ 174 Hz
	TB0CCR1 = 0;				// Initial duty cycle of 0%;
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
	_BIS_SR(LPM3);
	
	// Default return if it exits sleep for some reason
	return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
	P1IFG &= ~(BIT0 | BIT1);
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
	static unsigned char direction = 1; // 1 = increase, 0 = decrease
	if(direction)
	{
		TB0CCR1++;				// 16 ms / 3 s * 188 ~ 1
		if(TB0CCR1 == 188)		// After 3 s, duty cucle reaches 100%
			direction = 0;		// Reverse duty cycle change direction
	}
	else
	{
		TB0CCR1--;				// Reverse of above
		if(!TB0CCR1)
			direction = 1;
	}
}


