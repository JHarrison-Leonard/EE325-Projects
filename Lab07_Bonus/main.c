/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: Switches between 3 states.
 *              Initial State: Gradually increases the brightness of LED1
 *                             over the course of 3 seconds until full
 *                             brightness and then gradually decreases the
 *                             brightness of LED1 over the course of 3
 *                             seconds until off. This repeats.
 *              State 1: On the press of SW1, the gradual change of LED1
 *                       pauses. This state reverts to the initial state on
 *                       the press or release of SW2.
 *              State 2: On the press of SW1 if SW2 is being pressed,
 *                       the initial state is parralled with the period being
 *                       0.125 seconds instead 3. Exits to initial state on
 *                       release of either SW1 or SW2.
 *              State 3: On the press of SW2 if SW1 is being pressed, blinks
 *                       LED1 with its current brightness at 4 Hz. Exits to
 *                       initial state on release of either SW1 or SW2.
 * Input:       Takes inputs on SW1 and SW2 (P1.0,1)
 * Output:      Gives output on LED1 (P2.2)
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        February 27th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>

// Interrupt flag macros
#define SW1IFG (P1IFG & BIT0)
#define SW2IFG (P1IFG & BIT1)
// Falling edge macros
#define SW1FE (P1IES & BIT0)
#define SW2FE (P1IES & BIT1)

// blink_mode == 0, gradual change; blink_mode = 1, instant blink
unsigned char blink_mode = 0;
unsigned int blink_timer = 0;
unsigned char timer_max = 188;
unsigned char debounce = 0;


int main(void)
{
	// Peripheral setup
	WDTCTL = WDT_ADLY_16;		// WDT with 16 ms ACLK interval
	TB0CCTL1 = OUTMOD_7;		// Reset/Set output mode
	TB0CTL = TBSSEL_1 | MC_1;	// ACLK clock source and Up mode
	TB0CCR0 = timer_max;		// 32768 / 188 ~ 174 Hz
	TB0CCR1 = 0;				// Initial duty cycle of 0%;
	P1DIR &= ~(BIT0 | BIT1);	// Set SW1 and SW2 (P1.0,1) to input
	P2DIR |= BIT2;				// Set LED1 (P2.2) to output
	P2OUT &= ~BIT2;
	P2SEL |= BIT2;				// Set LED1 to special mode (TB1)
	
	// Interrupt setup
	_EINT();					// Enable global interrupts
	P1IE |= (BIT0 | BIT1);		// Enable interrupts for SW1 and SW2
	P1IES |= (BIT0 | BIT1);		// SW1 and SW2 interrupt from high to low
	IE1 |= WDTIE;				// Enable WDT interrupts
	
	for(;;)
	{
	    if(debounce)
	    {
	        _delay_cycles(2000);	// 20 ms debounce delay
	        P1IE |= (BIT0 | BIT1);	//Enable interrupts for SW1 and SW2
	    }
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
	static unsigned char SW1 = 0;
	static unsigned char SW2 = 0;
	
	if(SW1IFG)
	{
		P1IE &= ~BIT0;			// Disable interrupts for SW1
		if(SW1FE)
		{
			SW1 = 1;			// SW1 is pressed
			P1IES &= ~BIT0;		// SW1 interrupt from low to high
			if(!SW2)
				IE1 &= ~WDTIE;	// Disable WDT Interrupts
			else
				timer_max = 8;	// 4 Hz gradual change
		}
		else
		{
			SW1 = 0;			// SW1 is released
			P1IES |= BIT0;		// SW1 interrupt from high to low
			P2SEL |= BIT2;		// Enable timer control of LED2
			blink_mode = 0;		// Gradual change
			timer_max = 188;	// 3 s gradual change
		}
	}
	
	if(SW2IFG)					// SW2 enables WDT interrupts
	{
		P1IE &= ~BIT1;			// Disable interrupts for SW2
		if(SW2FE)
		{
			SW2 = 1;			// SW2 is pressed
			P1IES &= ~BIT1;		// SW2 interrupt from low to high
			IE1 |= WDTIE;		// Resuming duty cycle changes
			if(SW1)
			{
				blink_mode = 1;	// Instant blink
				blink_timer = TB0CCR1;
				timer_max = 8;  // 4 Hz blink
			}
		}
		else
		{
			SW2 = 0;			// SW2 is released
			P1IES |= BIT1;		// Sw2 interrupt from high to low
			P2SEL |= BIT2;		// Enable timer control of LED2
			blink_mode = 0;		// Gradual change
			timer_max = 188;	// 3 s gradual change
		}
	}
	
	debounce = 1;
	P1IFG &= ~(BIT0 | BIT1);	// Clear interrupt flag for SW1 and SW2
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
	static unsigned char direction = 1;	// 1 = increase, 0 = decrease
	
    if(direction)
    {
        if(!blink_mode)
        {                                // 16 ms / 3 s * 188 ~ 1
            TB0CCR1++;					// Or 1 / 16 ms / 8 Hz ~ 8
            if(TB0CCR1 >= timer_max)	// After duty cycle reaches 100%
                direction = 0;			// Reverse duty cycle change direction
        }
        else
        {
            blink_timer++;
            if(blink_timer >= timer_max)
            {
                direction = 0;
                P2SEL |= BIT2;
            }
        }
    }
    else
    {
        if(!blink_mode)
        {
            TB0CCR1--;					// Reverse of above
            if(!TB0CCR1)
                direction = 1;
        }
        else
        {
            blink_timer--;
            if(!blink_timer)
            {
                direction = 1;
                P2SEL &= ~BIT2;
            }
        }
    }
}


