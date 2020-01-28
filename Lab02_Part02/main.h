/*---------------------------------------------------------------------------
 * File:        main.h
 * Description: Header file of primary code file main.c
 *              Contains documentation of functions defined in main.c
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 14th, 2020
 *---------------------------------------------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_


/* Sets control parameters and calculates the array product pairs
 *
 * Returns: An in value of 0
 * Outputs: To stdout, 3 formatted arrays
 */
int main(void);

/* Prints an array, formatting with spaces and brackets
 *
 * Inputs:  a: The array to print
 *          size: The length of the array
 * Outputs: To stdout, the formatted array
 */
void printArray(const int a[], unsigned int size);


#endif
