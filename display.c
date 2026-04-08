#include "display.h"
#include "global.h"
#include "lcd.h"
#include "uart.h"
#include <stdio.h>

const char* getModeText(void)
{
    switch(mode)
    {
        case 0: return "MD:Sec";
        case 1: return "MD:10Sec";
        case 2: return "MD:Min";
        case 3: return "MD:10Min";
        case 4: return "MD:HR";
        default: return "MD:Sec";
    }
}
void displayTime(void)
{
    unsigned long temp;
    unsigned int hours, minutes, seconds;
    char buffer[17];

    temp = cookingTime;

    hours   = temp / 3600;
    temp    = temp % 3600;
    minutes = temp / 60;
    seconds = temp % 60;

    sprintf(buffer, "%01u:%02u:%02u", hours, minutes, seconds);

    lcd_gotoxy(1, 1);
    lcd_puts(buffer);
}

void display_SP_HT(void) 
{
    char buf[16];
    lcd_gotoxy(1, 3);                  // Line 3, column 1
    sprintf(buf, "SP:%5.1fC HT:%s", SP, heater_on ? "ON " : "OFF");
    lcd_puts(buf);
}

void display_CT_CK(void)
{
    char buf[16];
    lcd_gotoxy(1, 2);
    sprintf(buf, "CT:%5.1fC CK:%s", CT, cooking_on ? "ON " : "OFF");
    lcd_puts(buf);
}

void display_MD_CL(const char* modeText) 
{
    char buf[17];
     sprintf(buf, "%-10sCL:%s", modeText, cooler_on ? "ON " : "OFF");
    lcd_gotoxy(1, 4);
    lcd_puts(buf);
}

void uart_display_time(void)
{
    char buf[25];
    unsigned long temp = cookingTime;
    unsigned int hours   = temp / 3600;
    unsigned int minutes = (temp % 3600) / 60;
    unsigned int seconds = temp % 60;
    sprintf(buf, "Time: %02u:%02u:%02u\r\n", hours, minutes, seconds);
    send_string_no_lib((unsigned char*)buf);
}

void uart_display_status(void)
{
    char buf[25];
    uart_display_time();

    sprintf(buf, "CT:%5.1fC CK:%s\r\n", CT, cooking_on ? "ON " : "OFF");
    send_string_no_lib((unsigned char*)buf);

    sprintf(buf, "SP:%5.1fC HT:%s\r\n", SP, heater_on ? "ON " : "OFF");
    send_string_no_lib((unsigned char*)buf);

    sprintf(buf, "MD:%-6s CL:%s\r\n",
        mode == 0 ? "Sec"   : mode == 1 ? "10Sec" :
        mode == 2 ? "Min"   : mode == 3 ? "10Min" : "HR",
        cooler_on ? "ON" : "OFF");
    send_string_no_lib((unsigned char*)buf);
}