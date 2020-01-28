/*---------------------------------------------------------------------------
 * File:        main.c
 * Description:Assignment 3
 *              Initializes LED1 to off and LED2 to on
 *              Switches between 4 states based off of button inputs
 *              State 1: SW1 is pressed but not switch 2
 *                       Turns off LED2 and blinks LED1 at 2 Hz
 *              State 2: SW2 is pressed but not switch 1
 *                       Turns on LED1 and blinks LED2 at 5 Hz
 *              State 3: SW1 and SW2 are pressed
 *                       Turns LED1 on, LED2 off, and blinks both at 8 Hz
 *                       When exiting state, turns LED1 off and LED2 on
 *              Default state: Nothing is pressed
 *                             Does nothing
 * Input:       Uses SW1 and SW2 macros on port 1 as inputs
 * Output:      Uses LED1 and LED2 macros on port 2 as outputs
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 21st, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include "main.h"
#define F_CPU 1000000UL // 1 MHz
#include "delay.h"


int main()
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Set SW1 and SW2 to 0 for input
	P1DIR &= ~(SW1 | SW2);
	// Set LED1 and LED2 to 1 for output
	P2DIR |= LED1 | LED2;
	
	// Initialize LED1 to off and LED2 to on
	P2OUT &= ~LED1;
	P2OUT |= LED2;
	
	
	for(;;)
	{
		// SW1 and not SW2
		while(!(P1IN & SW1) && (P1IN & SW2))
		{
			_delay_ms(20); // Enter debounce
			if(!(P1IN & SW1) && (P1IN & SW2)) P2OUT &= ~LED2; // Turn LED2 off
			while(!(P1IN & SW1) && (P1IN & SW2))
			{
				P2OUT ^= LED1; // Toggle LED1
				// Delay 0.25s
				// 0.25s on, 0.25s off => 0.5/1s = 2 Hz
				_delay_ms(250);
			}
		}
		
		// SW2 and not SW1
		while((P1IN & SW1) && !(P1IN & SW2))
		{
			_delay_ms(20); // Enter debounce
			if((P1IN & SW1) && !(P1IN & SW2)) P2OUT &= LED1; // Turn LED1 on
			while((P1IN & SW1) && !(P1IN & SW2))
			{
				P2OUT ^= LED2; //Toggle LED2
				// Delay 0.1s
				// 0.1s on, 0.1s off => 0.2/1s = 5 Hz
				_delay_ms(100);
			}
		}
		
		/* Bonus */
		// Both SW1 and SW2
		while(!((P1IN & SW1) || (P1IN & SW2)))
		{
			_delay_ms(20); // Enter debounce
			if(!((P1IN & SW1) || (P1IN & SW2)))
			{
				// Assuming "Alternatively" was supposed to mean alternating
			    P2OUT &= ~LED1;
			    P2OUT |= LED2;
			}
			while(!((P1IN & SW1) || (P1IN & SW2)))
			{
				P2OUT ^= LED1 | LED2; // Toggle both LED1 and LED2
				// Delay 0.0625s
				// 0.0625s on, 0.0625s off => 0.125/1s = 8 Hz
				_delay_ms(62.5);
			}
			_delay_ms(20); // Exit debounce
			if((P1IN & SW1) || (P1IN & SW2))
			{
				P2OUT &= ~LED1; // Return to original state, LED1 off
				P2OUT |= LED2;  // and LED2 on
			}
		}
	}
}
