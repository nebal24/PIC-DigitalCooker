/*
 * File:   interrupt_handlers.c
 * Author: Lenovo
 *
 * Created on April 7, 2026, 4:46 PM
 */


#include <xc.h>
#include "global.h"
#include "interrupt_handlers.h"

void INT0_ISR_Handler(void)
{
    mode++;
    if (mode > 4)
    {
        mode = 0;
    }

    INTCONbits.INT0IF = 0;
}