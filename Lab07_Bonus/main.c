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

// Interrupt flag macros
#define SW1IFG (P1IFG & BIT0)
#define SW2IFG (P1IFG & BIT1)
// Falling edge macros
#define SW1FE (P1IES & BIT0)
#define SW2FE (P1IES & BIT1)


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
	IE1 |= WDTIE;				// Enable WDT interrupts
	
	for(;;)
	{
		LPM3;					// Enter deep (ACLK only) sleep
		_delay_cycles(20000);	// 20 ms debounce delay
		P1IE |= (BIT0 | BIT1);	//Enable interrupts for SW1 and SW2
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
	static unsigned char SW1 = 0;
	static unsigned char SW2 = 0;
	
	if(SW1IFG)
	{
		P1IE &= ~BIT0;			// Disable interrupts for SW1
		if(SW1FE)
		{
			SW1 = 1;			// SW1 is pressed
			P1IES &= ~BIT0;		// SW1 interrupt from low to high
			if(!SW2)
				IE1 &= ~WDTIE;	// Disable WDT Interrupts
		}
		else
		{
			SW1 = 0;			// SW1 is released
			P1IES |= BIT0;		// SW1 interrupt from high to low
		}
	}
	
	if(SW2IFG)					// SW2 enables WDT interrupts
	{
		P1IE &= ~BIT1;			// Disable interrupts for SW2
		if(SW2FE)
		{
			SW2 = 1;			// SW2 is pressed
			P1IES &= ~BIT1;		// SW2 interrupt from low to high
			if(!SW1)
				IE1 |= WDTIE;	// Resuming duty cycle changes
		}
		else
		{
			SW2 = 0;			// SW2 is released
			P1IES |= BIT1;		// Sw2 interrupt from high to low
		}
	}
	
	LPM3_EXIT;					// Exit sleep for debounce
	P1IFG &= ~(BIT0 | BIT1);	// Clear interrupt flag for SW1 and SW2
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


