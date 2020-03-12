/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Acts as an interface between a human on the UART interface
 *              and a blinker program on the SPI interface.
 * Input:       Takes inputs on UART and SPI
 * Output:      Gives outputs on UART and SPI
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 12th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "serialIO.h"

#define SPI_BUSY (P3IN & BIT0)


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Peripheral setup
	UART_initialize();
	SPI_initialize();
	P3DIR &= ~BIT0;
	
	
	char buffer[256];
	int command;
	
	for(;;)
	{
		// Prompt user
		UART_sendString("Blinker count: ");
		UART_getLine_echo(buffer, sizeof(buffer)/sizeof(char));
		
		// Get remaining blinks command
		if(buffer[0] == '?' && buffer[1] == '\0')
		{
			SPI_sendByte(0);
			snprintf(buffer, sizeof(buffer)/sizeof(char), "Blinks left: %u\n", SPI_getByte());
			UART_sendString(buffer);
		}
		
		// Repeat command
		else if(buffer[0] == 'r' && buffer[1] == '\0')
			SPI_sendByte(255);
		
		else
		{
			command = atoi(buffer);
			// If command number is 1 through 100, send command
			if( 1 <= command && command <= 100)
				SPI_sendByte((char) command);
			else // Otherwise, invalid
				UART_sendString("Invalid count entered\n");
		}
	}
}

void SPI_initialize()
{
	UCB0CTL1 = UCSSEL_2 | UCSWRST;      // Use SMCLK, software reset
	UCB0CTL0 = UCMSB | UCMST | UCSYNC;	// Most significant bit, master, sync
	UCB0BR0 = 0x02;						// UCB0CLK speed divider = 2
	UCB0BR1 = 0x00;						// 1048576 / 2 = 524288 Hz
	P3SEL |= BIT1 | BIT2 | BIT3;		// UCB0SIMO, UCB0MISO, UCB0CLK (P3.1,2,3)
	UCB0CTL1 &= ~UCSWRST;				// Exit software reset to initialize
}

void SPI_sendByte(unsigned char b)
{
	while(SPI_BUSY);					// Wait until slave is ready
	IFG2 &= ~UCB0RXIFG;
	UCB0TXBUF = b;						// Send byte
	while(!(IFG2 & UCB0RXIFG));
}

unsigned char SPI_getByte()
{
	while(SPI_BUSY);					// Wait until slave is ready
	IFG2 &= ~UCB0RXIFG;
	UCB0TXBUF = 0x00;					// Arbitrary write for receive
	while(!(IFG2 & UCB0RXIFG));
	return UCB0RXBUF;
}
