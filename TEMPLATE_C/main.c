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
#include <stdio.h>
#include "main.h"


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Main code
	
	// Default return
	return 0;
}
