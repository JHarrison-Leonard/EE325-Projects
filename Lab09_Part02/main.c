/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: [Does...
 * Input:       [Takes inputs...
 * Output:      [Gives outputs...
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 12th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include "main.h"

#define LED_BLINKS_INIT 10


unsigned char command;
unsigned char LED_blinks = LED_BLINKS_INIT;

int main(void)
{
	// Peripheral setup
	WDTCTL = WDT_MDLY_32;			// WDT in 32 ms interval mode using MCLK
	SPI_initialize();
	P1DIR |= BIT0 | BIT4;			// LED3 and busy flag (P1.0,4) as output
	P1OUT |= BIT4;					// Busy flag initially on
	P1OUT &= ~BIT0;					// LED3 initially off
	
	unsigned char lastCount = LED_BLINKS_INIT;
	
	for(;;)
	{
		/* Enter sleep */
		
		// Reply with remaining blinks
		if(command == 0)
			USISRL = LED_blinks;
		
		// Blink N times
		else if(1 <= command && command <= 100)
			LED_blinks = command;
		
		// Repeat last blink count
		else if(command == 255)
			LED_blinks = 255;
		
		P1OUT &= ~BIT4;				// Clear busy flag
	}
	
	// Default return
	return 0;
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
	
	/* Exit sleep */
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
	if(counter >= 10)
		counter = -1;				// Loop around
	
	counter++;
}
