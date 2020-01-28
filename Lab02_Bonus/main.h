/*---------------------------------------------------------------------------
 * File:        main.h
 * Description: Header file for the primary code file, main.c
 *              Contains documentation of functions defined in main.c as
 *              well as matrix dimensions for matrices X, Y, and ZED
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 14th, 2020
 *---------------------------------------------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_


// Dimension definitions for matrices X, Y, and Z
// The height of Y is requied to be the width of X
// The dimensions of ZED are "calculated" here
#define MATRIX_X_HEIGHT 8
#define MATRIX_X_WIDTH 8
#define MATRIX_Y_HEIGHT MATRIX_X_WIDTH
#define MATRIX_Y_WIDTH 8
#define MATRIX_ZED_HEIGHT MATRIX_X_HEIGHT
#define MATRIX_ZED_WIDTH MATRIX_Y_WIDTH

/* Calculates the product of two internally defined matrices and outputs them
 *
 * Returns: An int value of 0
 * Outputs: To stdout, 3 formatted matrices
 */
int main(void);

/*   Prints a matrix. Has 3 different definitions as array structure based
 * matrices have to have their second dimension be explicitly defined
 *
 * Inputs:  An array structure based matrix of on of 3 types
 * Outputs: To stdout, the input matrix with | on both sides
 */
void printMatX(const int A[][MATRIX_X_WIDTH]);
void printMatY(const int A[][MATRIX_Y_WIDTH]);
void printMatZED(int A[][MATRIX_ZED_WIDTH]);


#endif
