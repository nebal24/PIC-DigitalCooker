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