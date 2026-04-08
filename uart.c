/*
 * File:   uart.c
 * Author: Lenovo
 *
 * Created on April 7, 2026, 2:47 PM
 */


#include <xc.h>
#include "control.h"
#include "uart.h"

void uart_check_cancel(void)
{
    if (RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    if (PIR1bits.RCIF)
    {
        char ch = RCREG;

        if (ch == 'c' || ch == 'C')
        {
            cancel_all();
        }
    }
}