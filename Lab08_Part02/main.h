/*---------------------------------------------------------------------------
 * File:        main.h
 * Description: Header file for the primary code file main.c.
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 5th, 2020
 *---------------------------------------------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_


enum operations {Add, Subtract, Multiply};

int main(void);

/* Copy of UART_getLine from serialIO.h, with the change of calling
 * UART_sendCharacter for each character recieved
 */
void UART_getLine_echo(char * buf, int limit);

#endif
