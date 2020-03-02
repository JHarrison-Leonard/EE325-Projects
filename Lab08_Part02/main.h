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


int main(void);

/* Same functionality as UART_getCharacter with the added change of calling
 * UART_sendCharacter for the recieved character
 */
char UART_getCharacter_echo();

/* Copy of UART_getLine from serialIO.h, with the change of calling
 * UART_getCharacter_echo instead of UART_getCharacter
 */
void UART_getLine_echo(char * buf, int limit);

#endif
