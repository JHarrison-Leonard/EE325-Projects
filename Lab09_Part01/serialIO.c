/*---------------------------------------------------------------------------
 * File:        serialIO.c
 * Description: Code logic for rudimentary serial I/O
 * Input:       UART0
 * Output:      UART0
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Serial:      2020031100
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include "serialIO.h"


void UART_initialize()
{
	UCA0CTL1 |= UCSWRST;		// Set software reset during initialization
	P2SEL |= BIT4 | BIT5;		// UCA0 TX and RX mode (P2.4,5)
	UCA0CTL1 |= UCSSEL_2;		// BRCLK = SMCLK = 1048576 Hz
	UCA0BR0 = (char) 1048576 / SIO_UART_BR;
	UCA0BR1 = (char) 1048576 / (256 * SIO_UART_BR);
	UCA0CTL1 &= ~UCSWRST;		// Initialized, unset software reset
}

void UART_sendCharacter(char c)
{
	if(c == '\n')				// Carriage returns before newlines
		UART_sendCharacter('\r');
	
	while(!(IFG2 & UCA0TXIFG));	// Wait until TXBUF is empty
	UCA0TXBUF = c;				// Send c
}

char UART_getCharacter()
{
	while(!(IFG2 & UCA0RXIFG));	// Wait for character receive
	return UCA0RXBUF;
}

void UART_sendString(char * str)
{
	while(*str)					// Send characters from str until null
		UART_sendCharacter(*(str++));
}

void UART_getLine(char * buf, int limit)
{
	unsigned int i = 0;
	char c;
	while((i < limit - 1) && ((c = UART_getCharacter()) != '\n'))
		buf[i++] = c;			// Get characters until limit buffer limit or newline
	buf[i] = '\0';				// Terminate with a null character
}

void UART_getLine_echo(char * buf, int limit)
{
	int i = 0;
	char c;						// Buffer variable
	while((i < limit - 1) && ((c = UART_getCharacter()) != SIO_UART_NEWLINE))
	{
		if((i > 0) || (c != SIO_UART_BACKSPACE))
		{
			UART_sendCharacter(c);
			if(c == SIO_UART_BACKSPACE)
				i--;
			else
				buf[i++] = c;	// Get characters until buffer limit or newline
		}
	}
	if(i < limit - 1)
		UART_sendCharacter('\n');
	buf[i] = '\0';				// Terminate with a null character
}
