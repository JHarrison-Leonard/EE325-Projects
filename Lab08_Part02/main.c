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
#include <string.h>
#include "main.h"
#include "serialIO.h"


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Peripherals setup
	UART_initialize();
	
	
	char buffer[80];
	
	for(;;)
	{
		do
		{
			UART_sendString("Hi, I am CalcBot! Do you need help?\n");
			UART_getLine_echo(buffer, sizeof(buffer));
		}while(!strcmp(buffer, "Help me, CalcBot!"));
		UART_sendString("Would you like to 'add', 'subtract' or 'multiply'?\n");
		UART_getLine_echo(buffer, sizeof(buffer));
		while(!(strcmp(buffer, "add") || strcmp(buffer, "subtract") || strcmp(buffer, "multiply")))
		{
			UART_sendString(buffer);
			UART_sendString("is not a valid operation. Try again!");
			UART_getLine_echo(buffer, sizeof(buffer));
		}
		// Get first operand
		// Get second operand
		// Calc and out
	}
}

char UART_getCharacter_echo()
{
	char c;							// Buffer variable
	while(!(IFG2 & UCA0RXIFG));		// Wait for character recieve
	c = UCA0RXBUF;					// Store recieved character to c
	UART_sendCharacter(c);			// Echo recieved character
	return c;						// Return recieved character
}

void UART_getLine_echo(char * buf, int limit)
{
	int i = 0;
	char c;							// Buffer variable
	while((i < limit - 1) && ((c = UART_getCharacter_echo()) != '\n'))
		buf[i++] = c;				// Get characters until buffer limit or newline
	c[i] = '\0';					// Terminate with a null character
}
