/*
 * File:   control.c
 * Author: Lenovo
 *
 * Created on April 8, 2026, 11:34 AM
 */


#include <xc.h>
#include "global.h"
#include "control.h"
#include "delay.h"
#define BUZZER PORTDbits.RD0
void cancel_all(void)
{
    cooking_on = 0;
    heater_on = 0;
    cooler_on = 0;
    cookingTime = 0;
    
    PORTCbits.RC5 = 0;   // physically turns heater output off
    PORTCbits.RC2 = 0;   // physically turns cooler output off
}

void start_cooking(void)
{
    if (cookingTime > 0)
    {
        cooking_on = 1;
    }
}

void stop_cooking(void)
{
    cooking_on = 0;
}

void finish_cooking(void)
{
    cooking_on = 0;
    heater_on = 0;

    PORTCbits.RC5 = 0;   // Heater OFF
    cooking_done_flag = 1;
}

void beep_buzzer(void)
{
    for (int i = 0; i < 5; i++)
    {
        BUZZER = 1;
        delay_ms(1000);

        BUZZER = 0;
        delay_ms(1000);
    }
}