/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Part 2 of assignment 2
 *              Multiplies the elements of two defined arrays in pairs and
 *              stores them in a third array
 * Input:       Two integer arrays, hard-coded
 * Output:      The 2 input arrays and the output array
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 14th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Input array definitions
	const unsigned int arraySize = 6;
	const int x[] = {-1, 2, 5, 3, -5, 6};
	const int y[] = {-7, 8, 23, 13, 23, 28};
	// I'm only doing this with C11 to prove that it can be done
	int z[arraySize];
	
	// Calculate product of x y pairs and store to z
	for(unsigned int i = 0; i < arraySize; i++)
		z[i] = x[i] * y[i];
	
	// Print input and output arrays
	printf("Input Array x: "); printArray(x, arraySize); putc('\n', stdout);
	printf("Input Array y: "); printArray(y, arraySize); putc('\n', stdout);
	printf("Output Array z: "); printArray(z, arraySize); putc('\n', stdout);
	
	// Default return
	return 0;
}

void printArray(const int a[], unsigned int size)
{
    // Beginning of array [
	putc('[', stdout);
	for(unsigned int i = 0; i < size - 1; i++)
		printf("%d ", a[i]); // Each element of array, separated by spaces
	printf("%d]", a[size - 1]); // No space after final element, end of row [
}
