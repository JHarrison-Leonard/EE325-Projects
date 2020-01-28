/*---------------------------------------------------------------------------
 * File:        main.h
 * Description: Header file for primary code file, main.c
 *              Contains documentation for functions defined in main.c
 *              Contains pin macro definitions
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 21st, 2020
 *---------------------------------------------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_
#include <msp430.h>


// Macros to define which bits SW1 and SW2 are for more readable code
#define SW1 BIT0
#define SW2 BIT1

// Macros to define which bits LED1 and LED2 are for more readable code
#define LED1 BIT2
#define LED2 BIT1

/*  Sets control parameters and changes blinks LEDs depending on which
 * buttons are pressed
 *
 * Controls: P1.0, P1.1, P2.1, P2.2
 * Inputs:  Buttons SW1 and SW2
 * Outputs: LED1 and LED2
 */
int main();


#endif
