/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: [Does...
 * Input:       [Takes inputs...
 * Output:      [Gives outputs...
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 5th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include "main.h"
#include "serialIO.h"


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	for(;;)
	{
		do
		{
			// "Hi, I am CalcBot!" Logic
		}while(/* "Help me..." */);
		// "Would you like to..."
		while(/* Invalid operation */)
		{
			// "...is not a valid operation..."
		}
		// Get first operand
		// Get second operand
		// Calc and out
	}
}
