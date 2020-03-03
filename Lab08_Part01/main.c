/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Echos character entered into serial terminal.
 * Input:       Serial
 * Output:      Serial
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 5th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include "serialIO.h"


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	UART_initialize();

	for(;;)
	{
	    UART_sendCharacter(UART_getCharacter());
	}
}
