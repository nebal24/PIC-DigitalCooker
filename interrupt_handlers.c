/*
 * File:   interrupt_handlers.c
 * Author: Lenovo
 *
 * Created on April 7, 2026, 4:46 PM
 */



#include <xc.h>
#include "global.h"
#include "interrupt_handlers.h"
#define _XTAL_FREQ 4000000UL


void __interrupt() highISR(void)
{
    if (INTCONbits.INT0IF)
        INT0_ISR_Handler();
}
void __interrupt(low_priority) lowISR(void)
{
    
}


void setupINT0(void)
{
    INTCONbits.INT0IE = 0;    // disable INT0 first
    INTCONbits.INT0IF = 0;    // clear old flag

    INTCON2bits.INTEDG0 = 0;  // falling edge trigger

    INTCONbits.INT0IE = 1;    // enable INT0
    INTCONbits.GIE = 1;       // global interrupt enable
}

void INT0_ISR_Handler(void)
{
    __delay_ms(120);   // debounce delay

    if (PORTBbits.RB0 == 0)   // still pressed
    {
        mode++;
        if (mode > 4)
        {
            mode = 0;
        }

        while (PORTBbits.RB0 == 0);  // wait until release
    }

    INTCONbits.INT0IF = 0;
}