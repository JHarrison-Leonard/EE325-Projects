/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Runs a chat bot over a serial connection that can calculate
 *              a simple math operation
 * Input:       Input taken over serial defined in serialIO.h
 * Output:      Output given over serial defined in serialIO.h
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 5th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "serialIO.h"


#define botPrompt() UART_sendString("\e[34mBot: \e[0m")
#define usrPrompt() UART_sendString("\e[31mMe: \e[0m")


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Peripherals setup
	UART_initialize();
	
	
	char buffer[256];
	
	enum operations operation;
	int output;
	for(;;)
	{
		// Wait until "Help me, CalcBot!" is entered
		do
		{
			botPrompt(); UART_sendString("Hi, I am CalcBot! Do you need help?\r");
			usrPrompt(); UART_getLine_echo(buffer, sizeof(buffer));
		}while(strcmp(buffer, "Help me, CalcBot!"));
		
		// Wait until a valid operation is entered
		botPrompt(); UART_sendString("Would you like to 'add', 'subtract' or 'multiply'?\r");
		usrPrompt(); UART_getLine_echo(buffer, sizeof(buffer));
		while((strcmp(buffer, "add") && strcmp(buffer, "subtract") && strcmp(buffer, "multiply")))
		{
			botPrompt(); UART_sendString(buffer); UART_sendString(" is not a valid operation. Try again!\r");
			usrPrompt(); UART_getLine_echo(buffer, sizeof(buffer));
		}
		
		// Determine which operation was entered
		if(!strcmp(buffer, "add"))
			operation = Add;
		else if(!strcmp(buffer, "subtract"))
			operation = Subtract;
		else
			operation = Multiply;
		
		// Store first operand to output and leave second operand in buffer
		botPrompt(); UART_sendString("What is your first operand?\r");
		usrPrompt(); UART_getLine_echo(buffer, sizeof(buffer));
		output = atoi(buffer);
		botPrompt(); UART_sendString("What is your second operand?\r");
		usrPrompt(); UART_getLine_echo(buffer, sizeof(buffer));
		
		// Apply operation to operands
		switch(operation)
		{
			case Add:
				output += atoi(buffer);
				break;
			case Subtract:
				output -= atoi(buffer);
				break;
			case Multiply:
				output *= atoi(buffer);
		}
		
		// Output
		botPrompt();
		snprintf(buffer, sizeof(buffer), "The answer is %d.\r", output);
		UART_sendString(buffer);
	}
}

void UART_getLine_echo(char * buf, int limit)
{
	int i = 0;
	char c;							// Buffer variable
	while((i < limit - 1) && ((c = UART_getCharacter()) != '\r'))
	{
		UART_sendCharacter(c);
		buf[i++] = c;				// Get characters until buffer limit or newline
	}
	UART_sendCharacter(c);
	buf[i] = '\0';					// Terminate with a null character
}
