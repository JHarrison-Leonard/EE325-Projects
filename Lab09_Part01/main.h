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

void SPI_initialize();

void SPI_sendByte(unsigned char b);

unsigned char SPI_getByte();

#endif
