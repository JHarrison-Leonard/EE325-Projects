/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Blinks LED3 a number of times as commanded through SPI.
 * Input:       Takes inputs over SPI
 * Output:      Gives outputs on SPI and LED3
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 12th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include "main.h"

#define LED_BLINKS_INIT 10


volatile unsigned char command;
volatile unsigned char LED_blinks = LED_BLINKS_INIT;

int main()
{
	// Peripheral setup
	WDTCTL = WDT_MDLY_32;			// WDT in 32 ms interval mode using MCLK
	P1DIR |= BIT0 | BIT4;			// LED3 and busy flag (P1.0,4) as output
	P1OUT |= BIT4;					// Busy flag initially on
	P1OUT &= ~BIT0;					// LED3 initially off
	SPI_initialize();
	USICNT = 8;
	
	// Interrupt setup
	IE1 |= WDTIE;
	IFG1 &= ~WDTIFG;
	
	unsigned char lastCount = LED_BLINKS_INIT;
	
	P1OUT &= ~BIT4;
	for(;;)
	{
		// Enter sleep with global interrupts
		__bis_SR_register(LPM0_bits | GIE);
		
		// Reply with remaining blinks
		USISRL = LED_blinks;
		
		// Blink N times
		if(1 <= command && command <= 100)
		{
			LED_blinks = command;
			lastCount = command;
		}
		
		// Repeat last blink count
		else if(command == 255)
			LED_blinks = lastCount;
		
		P1OUT &= ~BIT4;				// Clear busy flag
	}
}

void SPI_initialize()
{
	USICTL0 |= USISWRST;			// Software reset
	
	// SCLK, SDO, SDI (P1.5,6,7), and enable output
	USICTL0 |= USIPE5 | USIPE6 | USIPE7 | USIOE;
	// Slave mode, most significant bit first
	USICTL0 &= ~(USIMST | USILSB);
	
	USICTL1 = USIIE;				// USI Interrupt enable
	USICTL0 &= ~USISWRST;			// Exit software reset
}

#pragma vector = USI_VECTOR
__interrupt void USI_ISR()
{
	P1OUT |= BIT4;					// Set busy flag
	command = USISRL;				// Read command from SPI
	USICNT = 8;						// Bit counter for next communication
	
	LPM0_EXIT;
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
	static int counter = 0;
	
	
	if(!counter && (LED_blinks > 0))
	{
		P1OUT |= BIT0;				// Turn LED1 on
		LED_blinks--;				// Subtracts a blink
	}
	if(counter == 1)
	    P1OUT &= ~BIT0;             // Turn LED1 off
	if(counter >= 10)
		counter = -1;				// Loop around
	
	counter++;
}
