/*
 * File:   timer0.c
 * Author: Lenovo
 *
 * Created on April 7, 2026, 2:47 PM
 */


#include <xc.h>
#include "timer0.h"

void reloadTimer0(void)
{
    TMR0H = 0xF0;
    TMR0L = 0xBE;
}

void setupTimer0(void)
{
    T0CONbits.TMR0ON = 0;   // stop timer first
    T0CONbits.T08BIT = 0;   // 16-bit mode
    T0CONbits.T0CS   = 0;   // internal instruction clock
    T0CONbits.PSA    = 0;   // enable prescaler
    T0CONbits.T0PS2  = 1;   // 1:256 prescaler
    T0CONbits.T0PS1  = 1;
    T0CONbits.T0PS0  = 1;

    reloadTimer0();

    INTCONbits.TMR0IF = 0;  // clear flag
    INTCONbits.TMR0IE = 1;  // enable Timer0 interrupt
    INTCONbits.GIE    = 1;  // global interrupt enable

    T0CONbits.TMR0ON = 1;   // start timer
}