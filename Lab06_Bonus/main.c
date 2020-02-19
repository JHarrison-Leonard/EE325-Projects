/*---------------------------------------------------------------------------
 * File:        main.c
 * Description: [Does...
 * Input:       [Takes inputs...
 * Output:      [Gives output...
 * Author:      Justin H. Leonard
 * Lab Section: 04
 * Date:        February 20th, 2020
 *---------------------------------------------------------------------------*/
#include <msp430.h>
#define F_CPU 1000000UL // 1 MHz
#include <delay.h>

#define SW1 !(BIT0 & P1IN)
unsigned char SW1_debounce_counter_press;
unsigned char SW1_debounce_counter_release;
#define SW2 !(BIT1 & P1IN)
unsigned char SW2_debounce_counter_press;
unsigned char SW2_debounce_counter_release;


int main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// Setup peripherals
	P1DIR &= ~(BIT0 | BIT1);// Set P1.0 and P1.1 to input for SW1 and SW2
	P2DIR |= BIT1 | BIT2;	// Set P2.1 and P2.2 to output for LED2 and LED1
	WDTCTL = WDT_ADLY_1000;	// Set watchdog timer to 1s mode
	
	// Setup interrupts
	_EINT();				// Enable global interrupts
	P1IE |= BIT0 | BIT1;	// Enable P1.0 and P1.1 interrupt for SW1 and SW2
	P1IES |= BIT0 | BIT1;	// SW1 and SW2 interrupt from high to low
	P1IFG &= ~(BIT0 | BIT1);// Clear interrupt flag for SW1 and SW2
	IE1 |= WDTIE;			// Enable watchdog timer interrupts
	IFG1 &= WDTIFG;			// Clear interrupt flag for watchdog timer
	
	SW1_debounce_counter_press = 0;
	SW1_debounce_counter_release = 0;
    SW2_debounce_counter_press = 0;
    SW2_debounce_counter_release = 0;
	for(;;)
	{
		_delay_ms(1);                                   // 1 ms delay
		if(SW1_debounce_counter_press)
        {
            SW1_debounce_counter_press--;
            if(!SW1_debounce_counter_press)
                SW1_debounce_counter_release = 20;
        }
        else if(SW1_debounce_counter_release && !SW1)
        {
            SW1_debounce_counter_release--;
            if(!SW1_debounce_counter_release)
            {
                P1IFG &= ~BIT0;                         // Clear interrupt flag for SW2
                P1IE |= BIT0;                           // Enable interrupts for SW2
            }
        }
		if(SW2_debounce_counter_press)
		{
			SW2_debounce_counter_press--;
			if(!SW2_debounce_counter_press)
				SW2_debounce_counter_release = 20;
		}
		else if(SW2_debounce_counter_release && !SW2)
		{
			SW2_debounce_counter_release--;
			if(!SW2_debounce_counter_release)
			{
				P1IFG &= ~BIT1;                         // Clear interrupt flag for SW2
				P1IE |= BIT1;                           // Enable interrupts for SW2
			}
		}
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
    if(SW1)
    {
        P1IE &= ~BIT0;                  // Disable interrupts for SW2
        IFG1 &= ~WDTIFG;                // Clear WDT interrupt flag
        IE1 ^= WDTIE;                   // Toggle interrupt enable for WDT
        SW1_debounce_counter_press = 20;// Set SW1 debounce counter to 20 ms
    }
    if(SW2)
    {
        P1IE &= ~BIT1;                  // Disable interrupts for SW2
        P2OUT ^= BIT1;                  // Toggle LED2
        SW2_debounce_counter_press = 20;// Set SW2 debounce counter to 20 ms
    }
    P1IFG &= ~BIT0;                     // Clear interrupt flag for SW1
    P1IFG &= ~BIT1;                     // Clear interrupt flag for SW2
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
    P2OUT ^= BIT2;                  // Toggle LED1
}
