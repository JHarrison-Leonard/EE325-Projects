/*---------------------------------------------------------------------------
 * File:        serialIO.h
 * Description: Documentation for functions defined in serialIO.c
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 5th, 2020
 *---------------------------------------------------------------------------*/
#ifndef SERIALIO_H_
#define SERIALIO_H_

/* "Configures UCI to work in UART mode at the baud rate as follows: if your
 * first name has an even number of letters use 19200, otherwise use 115200."
 * My first name is "Justin" so the baud rate is set to 19200
 *
 * Modifies: UCA0CTL1
 *           P2SEL
 *           UCA0BR0
 *           UCA0BR1
 *           UCA0MCTL
 */
void UART_initialize();

/* "Sends a character via UART"
 *
 * Inputs:   c: The character to be sent via UART
 * Modifies: UCA0TXBUF
 */
void UART_sendCharacter(char c);

/* "Waits for a character from UART and returns it."
 *
 * Outputs: The first character recieved via UART
 */
char UART_getCharacter();

/* "Sends a string via UART using UART_sendCharacter(char c)"
 * Does not send the null character.
 *
 * Inputs: str: The string to be sent via UART
 */
void UART_sendString(char * str);

/* "Receives characters via UART using UART_getCharacter() until it finds the
 * new line character or until the limit of characters is exceeded. Write that
 * string (excluding the new line character) to the buffer allocated outside of
 * the function. Terminates the string with the null character."
 *
 * Inputs:   buf: The location in memory to store the recieved characters
 *           limit: The limit to recieve which is to be at most equal to the
 *                  size of buf
 * Modifies: buf
 */
void UART_getLine(char * buf, int limit);

void UART_getLine_echo(char * buf, int limit);

#endif
