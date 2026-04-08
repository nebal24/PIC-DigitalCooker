/*
 * File:   control.c
 * Author: Lenovo
 *
 * Created on April 8, 2026, 11:34 AM
 */


#include <xc.h>
#include "global.h"
#include "control.h"

void cancel_all(void)
{
    cooking_on = 0;
    heater_on = 0;
    cooler_on = 0;
    cookingTime = 0;
    
    PORTCbits.RC5 = 0;   // Heater OFF
    PORTCbits.RC2 = 0;   // Cooler OFF
}