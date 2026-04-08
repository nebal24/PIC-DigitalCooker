
#include <xc.h>
#define _XTAL_FREQ 4000000UL 
#include "global.h"
#include "delay.h"
#include "control.h"
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
                    cookingTime = 0;
                }

                holdTime = 0;
            }

            delay_ms(50);
        }
    }

    lastState = currentState;
}
void check_cancel_button(void)
{
    if (PORTBbits.RB5 == 0)
    {
        __delay_ms(20);

        if (PORTBbits.RB5 == 0)
        {
            cancel_all();
            while (PORTBbits.RB5 == 0);
        }
    }
}

void handleCoolerButton(void) 
{
    if (PORTAbits.RA5 == 0) 
    {
        delay_ms(150);                        // debounce
        
        if (cooler_on == 0) {
            cooler_on = 1;
            PORTCbits.RC2 = 1;   // cooler ON
            heater_on = 0;
            cooking_on = 0;
            PORTCbits.RC5 = 0;   // heater OFF
        } else {
            cooler_on = 0;
            PORTCbits.RC2 = 0;   // cooler OFF
        }
        
        while(PORTAbits.RA5 == 0) {CLRWDT();}  // wait release
    }
}