/*---------------------------------------------------------------------------
 * File:        main.h
 * Description: Header file for the primary code file main.c.
 *              Contains documentation of functions defined in main.c.
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 7th, 2020
 *---------------------------------------------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_

/* Sets control parameters and runs both parts 1 and 2 of the assignment.
 *
 * Returns: An int of value 0
 * Outputs: To stdout, the seperated and labeled outputs of partOne() and partTwo()
 */
int main(void);

/*   For internally defined values, a and p, calculates a to the power of p and
 * stores that value to b.
 *
 * Outputs: To stdout, "a raised to the power p is b" replacing a, p, and b with
 *          their respective variables
 */
void partOne();

/*   For an internally defined string, count the number of words and sentences
 * that make up that string.
 *
 * Outputs: To stdout, the defined string and a string detailing the contents,
 *          both of which are labeled as "String" and "Contains" respectively
 */
void partTwo();

/*   Calculates value to the power of power. Accepts inputs of any kind for both
 * value and power, though everything is an int so powers of less than 0 are
 * guaranteed to be incorrect for any value that is not 1 or -1.
 *
 * Inputs:  value: the base number to be operated on
 *          power: the power of the operation
 * Returns: value to the power of power as a long int
 */
long int myPower(int value, int power);

#endif
