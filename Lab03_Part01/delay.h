/*---------------------------------------------------------------------------
 * File:        delay.h
 * Description: Quick and dirty header file with macro definitions for
 *              various delay functions. This was created without
 *              knowledge of the built-in _delay_cycles() function nor
 *              how to use the timer as both were out of scope of the
 *              original assignment, assignment 3
 * Input:       N/A
 * Output:      N/A
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        January 21st, 2020
 *---------------------------------------------------------------------------*/
#ifndef DELAY_H_
#define DELAY_H_

// Given by tutorial as the number of clock cycles to perform one empty loop
#define _DELAY_BASIC_CYCLES 10


/*   Most basic possible delay loop. Number of clock cycles used per loop is
 * defined by _DELAY_BASIC_CYCLES
 *
 * Input: n: an unsigned int to be the number of times the loops runs
 */
#define _delay_basic(n) for(unsigned int _delay_i = 0; _delay_i < n; _delay_i++)

/*   Macros that allow for delay_basic to be used with more meaningful
 * units, ms and us. All of the conversion math is handled by the compiler as
 * to mitigate overhead
 *
 * Input: ms/us: the desired delay in ms/us
 */
#define _delay_ms(ms) _delay_basic((unsigned int) ((ms * F_CPU) / (_DELAY_BASIC_CYCLES * 1000)))
#define _delay_us(us) _delay_basic((unsigned int) ((us * F_CPU) / (_DELAY_BASIC_CYCLES * 1000000)))

#endif
