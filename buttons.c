/*
 * File:   buttons.c
 * Author: Lenovo
 *
 * Created on April 7, 2026, 2:48 PM
 */



#include <xc.h>
#include "global.h"
#include "delay.h"
#include "lcd.h"
unsigned long getModeIncrement(void)
{
    switch(mode)
    {
        case 0: return 1;       // Sec
        case 1: return 10;      // 10Sec
        case 2: return 60;      // Min
        case 3: return 600;     // 10Min
        case 4: return 3600;    // HR
        default: return 1;
    }
}


void handleIncrementButton(void)
{
    static unsigned char lastState = 1;
    static unsigned int holdTime = 0;
    unsigned long step = getModeIncrement();
    unsigned char currentState = PORTBbits.RB3;

    if (currentState == 0)
    {
        if (lastState == 1)
        {
            cookingTime += step;
            if (cookingTime > 18000)
            {
                cookingTime = 18000;
            }

            holdTime = 0;
            delay_ms(150);
        }
        else
        {
            holdTime += 50;

            if (holdTime >= 500)
            {
                cookingTime += step;
                if (cookingTime > 18000)
                {
                    cookingTime = 18000;
                }

                holdTime = 0;
            }

            delay_ms(50);
        }
    }

    lastState = currentState;
}
void handleDecrementButton(void)
{
    static unsigned char lastState = 1;
    static unsigned int holdTime = 0;
    unsigned long step = getModeIncrement();
    unsigned char currentState = PORTBbits.RB4;

    if (currentState == 0)
    {
        if (lastState == 1)
        {
            if (cookingTime >= step)
            {
                cookingTime -= step;
            }
            else
            {
                cookingTime = 0;
            }

            holdTime = 0;
            delay_ms(150);
        }
        else
        {
            holdTime += 50;

            if (holdTime >= 500)
            {
                if (cookingTime >= step)
                {
                    cookingTime -= step;
                }
                else
                {
                    cookingTime = 18000;
                }

                holdTime = 0;
            }

            delay_ms(50);
        }
    }

    lastState = currentState;
}