/*
 * File:   delay.c
 * Author: Lenovo
 *
 * Created on April 7, 2026, 2:48 PM
 */

#include <xc.h>
#include "delay.h"
#define _XTAL_FREQ 4000000UL
void delay_ms(unsigned int n)
{
    unsigned int i;
    for(i = 0; i < n; i++)
    {
        __delay_ms(1);
    }
}