/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Part 1: Calculate a to the power of p
 *              Part 2: Count words and sentences in a string
 * Input:       None
 * Output:      Part 1: A string detailing a to the power of p
 *              Part 2: The string worked on and a string detailing the
 *                      number of words and sentences in that string
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 7th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include <ctype.h>
#include "main.h"


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Run parts 1 and 2 of assignment
	printf("Part one:\n");
	partOne();
	printf("\nPart two:\n");
	partTwo();
	
	// Default return, assumes execution success
	return 0;
}

void partOne()
{
	// Define input values and output placeholder variable
	const int a = 11;
	const int p = 4;
	long int b;
	
	// Calculate a to the power of p
	b = myPower(a, p);
	
	// Print output
	printf("%d raised to the power %d is %ld\n", a, p, b);
	
	// Default return, normally unnecessary but I don't trust the compiler
	return;
}

void partTwo()
{
	// Define input string and output placeholder variables
	const char * inputStr = "Hello! Welcome to CPE325. It is a great day, is it not?";
	int words = 0;
	int sentences = 0;
	
	// Iterate through inputStr, incrementing words and sentences appropriately
	// Words are assumed to be any alphanumeric grouping of characters, separated by non-alphanumeric characters
	// Sentences are assumed to always be terminated with a '.', '!', or '?' and to contain at least one word
	for(unsigned int i = 0; inputStr[i];)
	{
		while(inputStr[i] && !isalnum(inputStr[i])) // Skip to next word/end of string
			i++;
		if(inputStr[i]) // If not end of string, count a word
			words++;
		while(isalnum(inputStr[i])) //Skip to next non alpha-numeric character
			i++;
		if(inputStr[i] == '.' || inputStr[i] == '!' || inputStr[i] == '?') // If a sentence terminator, count a sentence
			sentences++;
	}
	
	// Print output
	printf("String: %s\nContains: The string contains %d words and %d sentences.\n", inputStr, words, sentences);
	
	// Default return, still unnecessary and still not trusting the compiler
	return;
}

long int myPower(int value, int power)
{
	// Default output given input power = 0
	long int output = 1;
	
	if(power < 0)                      // If power is negative,
		for(int i = 0; i > power; i--) // divide power number of times
			output /= value;
	else if(power > 0)                 // If power is positive
		for(int i = 0; i < power; i++) // multiply power number of times
			output *= value;
	
	// Default return
	return output;
}
