/*---------------------------------------------------------------------------
 * File:        main.h
 * Description: Header file for the primary code file main.c.
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        March 12th, 2020
 *---------------------------------------------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_


int main(void);

/* Initializes the SPI interface as the master interface.
 *
 * Modifies: UCB0CTL0
 *           UCB0CTL1
 *           UCB0BR0
 *           UCB0BR1
 *           P3SEL
 */
void SPI_initialize();

/* Sends a single byte over SPI.
 *
 * Input:    b: The byte to be sent
 * Modifies: UCB0TXBUF
 */
void SPI_sendByte(unsigned char b);

/* Sends a dummy value of 0x00 over SPI and returns the response.
 *
 * Output:   The response from the slave
 * Modifies: UCB0TXBUF
 */
unsigned char SPI_getByte();

#endif
