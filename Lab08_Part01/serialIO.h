/*---------------------------------------------------------------------------
 * File:        serialIO.h
 * Description: [Does...
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        [Due...
 *---------------------------------------------------------------------------*/
#ifndef SERIALIO_H_
#define SERIALIO_H_
#include <msp430.h>
#include <stdio.h>

//FILE out_UART;
//FILE in_UART;

void UART_initialize();

void UART_sendCharacter(char c);

char UART_getCharacter();

void UART_sendString(char * str);

void UART_getLine(char * buf, int limit);

#endif
