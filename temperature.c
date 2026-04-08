#include "temperature.h"
#include "lcd.h"
#include <stdio.h>    // for sprintf

float read_SP(void) 
{
    int raw = read_adc_raw(0);         // AN0 - potentiometer
    SP = (raw * MAX_TEMP) / 1023.0f;  // scale to 0?200°C
    return SP;
}

float read_CT(void)
{
    float voltage = read_adc_voltage(2);  // AN2
    CT = voltage * MAX_TEMP;              // * 200
    return CT;
}

void control_heater(void)
{
    if (!cooking_on) 
    {
        PORTCbits.RC5 = 0;
        heater_on = 0;
        return;
    }
        
    if (CT < (SP - H))
    {
        PORTCbits.RC5 = 1;
        heater_on = 1;
    }
    else if (CT > (SP + H))
    {
        PORTCbits.RC5 = 0;
        heater_on = 0;
    }
    // else ? No Change
}