/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Part 1 of assignment 2
 *              Prints a table of byte sizes, minimums, and maximums using
 *              compiler functions and header files
 * Input:       None
 * Output:      Table of identifier byte sizes, minimums, and maximums
 *              using printf to stdout
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 14th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>


int main(void)
{
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	printf("------------------------------------------------------------------------------------------\n");
	printf("| Data type              | Size (in bytes) | Minimum              | Maximum              |\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("| %-23s| %-16d| %-21d| %-21d|\n", "char", sizeof(char), CHAR_MIN, CHAR_MAX);
	printf("| %-23s| %-16d| %-21d| %-21d|\n", "short int", sizeof(short int), SHRT_MIN, SHRT_MAX);
	printf("| %-23s| %-16d| %-21d| %-21d|\n", "int", sizeof(int), INT_MIN, INT_MAX);
	printf("| %-23s| %-16d| %-21ld| %-21ld|\n", "long int", sizeof(long int), LONG_MIN, LONG_MAX);
	printf("| %-23s| %-16d| %-21lld| %-21lld|\n", "long long int", sizeof(long long int), LLONG_MIN, LLONG_MAX);
	printf("| %-23s| %-16d| %-21u| %-21u|\n", "unsigned char", sizeof(unsigned char), 0, UCHAR_MAX);
	printf("| %-23s| %-16d| %-21u| %-21u|\n", "unsigned short int", sizeof(unsigned short int), 0, USHRT_MAX);
	printf("| %-23s| %-16d| %-21u| %-21u|\n", "unsigned int", sizeof(unsigned int), 0, UINT_MAX);
	printf("| %-23s| %-16d| %-21u| %-21lu|\n", "unsigned long int", sizeof(unsigned long int), 0, ULONG_MAX);
	printf("| %-23s| %-16d| %-21u| %-21llu|\n", "unsigned long long int", sizeof(unsigned long long int), 0, ULLONG_MAX);
	printf("| %-23s| %-16d| %-21e| %-21e|\n", "float", sizeof(float), FLT_TRUE_MIN, FLT_MAX);
	// Using DBL_MIN instead DBL_TRUE_MIN because DBL_TRUE_MIN causes the whole thing to stall
	printf("| %-23s| %-16d| %-21e| %-21e|\n", "double", sizeof(double), DBL_MIN, DBL_MAX);
	printf("-------------------------------------------------------------------------------------------\n");
	
	return 0;
}
