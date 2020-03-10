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


int main(void)
{
	// Peripheral setup
	WDTCTL = 0x00;			// Some interval mode non aclk timing
	SPI_initialize();
	
	// Default return
	return 0;
}

void SPI_initialize()
{
	USICTL0 |= USISWRST;	// Software reset
	USICTL0 |= USIPE5 | USIPE6 | USIPE7 | USIOE;
	USICTL1 = USIIE;		// USI Interrupt enable
	USICTL0 &= ~USISWRST;	// Exit software reset
}
