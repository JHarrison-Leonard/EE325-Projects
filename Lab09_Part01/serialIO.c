/*---------------------------------------------------------------------------
 * File:        serialIO.c
 * Description: Code logic for rudimentary serial I/O
 * Input:       UART0
 * Output:      UART0
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 5th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include "serialIO.h"


void UART_initialize()
{
	UCA0CTL1 |= UCSWRST;		// Set software reset during initialization
	P2SEL |= BIT4 | BIT5;		// UCA0 TX and RX mode (P2.4,5)
	UCA0CTL1 |= UCSSEL_2;		// BRCLK = SMCLK = 1048576 Hz
	UCA0BR0 = 0x09;				// Baud rate = 115200
	UCA0BR1 = 0x00;				// BRCLK / baud rate = 1048576 / 19200 = 9
	UCA0CTL1 &= ~UCSWRST;		// Initialized, unset software reset
}

void UART_sendCharacter(char c)
{
	if(c == '\r')				// Carriage return before newlines
		UART_sendCharacter('\n');
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
    char c;                         // Buffer variable
    while((i < limit - 1) && ((c = UART_getCharacter()) != '\r'))
    {
        if((i > 0) || (c != '\x7f'))
        {
            UART_sendCharacter(c);
            if(c == '\x7f')
                i--;
            else
                buf[i++] = c;       // Get characters until buffer limit or newline
        }
    }
    UART_sendCharacter(c);
    buf[i] = '\0';                  // Terminate with a null character
}
