#include "temperature.h"
#include "lcd.h"
#include <stdio.h>    // for sprintf

float read_SP(void) 
{
    int raw = read_adc_raw(0);         // AN0 - potentiometer
    SP = (raw * MAX_TEMP) / 1023.0f;  // scale to 0?200°C
    return SP;
}

void display_SP(void) 
{
    char buf[16];
    lcd_gotoxy(1, 3);                  // Line 3, column 1
    sprintf(buf, "SP:%5.1fC HT:%s", SP, heater_on ? "ON " : "OFF");
    lcd_puts(buf);
}

float read_CT(void)
{
    float voltage = read_adc_voltage(2);  // AN2
    CT = voltage * MAX_TEMP;              // * 200
    return CT;
}

void display_CT(void)
{
    char buf[16];
    lcd_gotoxy(1, 2);
    sprintf(buf, "CT:%5.1fC CK:%s", CT, cooking_on ? "ON " : "OFF");
    lcd_puts(buf);
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