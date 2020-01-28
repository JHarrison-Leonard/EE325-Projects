/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Bonus part of assignment 2
 *              Calculates the product of 2 matrices and outputs all matrices
 * Input:       Two matrices and their dimensions, hard-coded
 * Output:      The two input matrices as well as their multiple to stdout
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
	
	// Instantiate arbitrary matrices X and Y
	const int X[MATRIX_X_HEIGHT][MATRIX_X_WIDTH] =
	{	{0,  1,  2,  3,  4,  5,  6,  7},
		{8,  9,  10, 11, 12, 13, 14, 15},
		{16, 17, 18, 19, 20, 21, 22, 23},
		{24, 25, 26, 27, 28, 29, 30, 31},
		{32, 33, 34, 35, 36, 37, 38, 39},
		{40, 41, 42, 43, 44, 45, 46, 47},
		{48, 49, 50, 51, 52, 53, 54, 55},
		{56, 57, 58, 59, 60, 61, 62, 63}};
	const int Y[MATRIX_Y_HEIGHT][MATRIX_Y_WIDTH] =
	{	{1, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 1}};
	// Placeholder matrix ZED with proper dimensions and 0 filled
	// (ZED instead of Z because Z is an MSP430 macro for some ungodly reason)
	int ZED[MATRIX_ZED_HEIGHT][MATRIX_ZED_WIDTH] = {{0}};
	
	// Generate multiplied matrix XY and set to ZED
	// Iterate through each element in matrix ZED
	for(unsigned int i = 0; i < MATRIX_ZED_HEIGHT; i++)
	        for(unsigned int j = 0; j < MATRIX_ZED_WIDTH; j++)
	        {
	            // Set the element of ZED to the be the dot product of the
	            // associated row of X and column of Y
	            for(unsigned int k = 0; k < MATRIX_X_WIDTH; k++)
	            {
	                ZED[i][j] += X[i][k] * Y[k][j];
	            }
	        }
	
	// Print input and output matrices
	printf("Input Matrix X:\n"); printMatX(X); putc('\n', stdout);
	printf("Input Matrix Y:\n"); printMatY(Y); putc('\n', stdout);
	printf("Output Matrix Z:\n"); printMatZED(ZED); putc('\n', stdout);
	
	// Default return
	return 0;
}

void printMatX(const int A[][MATRIX_X_WIDTH])
{
    // Loop through each row of A
	for(unsigned int i = 0; i < MATRIX_X_HEIGHT; i++)
	{
		putc('|', stdout); // Beginning of row |
		for(unsigned int j = 0; j < MATRIX_X_WIDTH - 1; j++)
			printf("%-3d ", A[i][j]); // Each character of row, separated by spaces
		printf("%-3d|\n", A[i][MATRIX_X_WIDTH - 1]); // No space after final element, end of row |
	}
}

void printMatY(const int A[][MATRIX_Y_WIDTH])
{
    // Structured same as printMatX
    for(int i = 0; i < MATRIX_Y_HEIGHT; i++)
        {
            putc('|', stdout);
            for(int j = 0; j < MATRIX_Y_WIDTH - 1; j++)
                printf("%-3d ", A[i][j]);
            printf("%-3d|\n", A[i][MATRIX_Y_WIDTH - 1]);
        }
}

void printMatZED(int A[][MATRIX_ZED_WIDTH])
{
    // Structured same as printMatX
    for(int i = 0; i < MATRIX_ZED_HEIGHT; i++)
    {
        putc('|', stdout);
        for(int j = 0; j < MATRIX_ZED_WIDTH - 1; j++)
            printf("%-3d ", A[i][j]);
        printf("%-3d|\n", A[i][MATRIX_ZED_WIDTH - 1]);
    }
}
