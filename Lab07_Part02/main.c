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

// Timer max, 50% duty cycle, LED, ...
const unsigned int config[] = {0, 0, 0, 16, 8, BIT2, 33, 16, BIT1, 66, 33, (BIT1 | BIT2)};


int main(void)
{
	// Peripheral setup
	WDTCTL = WDT_ADLY_1000;		// WDT: 1 s ACLK interval
	TB0CTL = TBSSEL_1 | MC_1;	// Timer B: ACLK and Up mode
	TB0CCTL4 = OUTMOD_7;		// TB4: Reset/set output mode
	P2DIR |= (BIT1 | BIT2);		// LED1 and LED2 (P2.2,1): Output
	P2OUT &= ~(BIT1 | BIT2);	// LED1 and LED2: Off
	P3DIR |= BIT5;				// Buzzer (P3.5): Output
	P3SEL |= BIT5;				// Buzzer: Special mode (TB4);
	
	// Interrupt setup
	_EINT();					// Enable global interrupts
	IE1 |= WDTIE;				// Enable WDT interrupts
	IFG1 &= ~WDTIFG;			// Clear interrupt flag for WDT
	
	// Enter sleep
	_BIS_SR(LPM3);
	
	// Default return
	return 0;
}


#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
	static unsigned char configSelect = 0;
	TB0CCR0 = config[configSelect++];
	TB0CCR4 = config[configSelect++];
	P2OUT &= ~(BIT1 | BIT2);
	P2OUT |= config[configSelect++];
	if(configSelect >= sizeof(config) / 2)
		configSelect = 0;
}
