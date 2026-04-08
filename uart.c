#include "uart.h"
#include "global.h"
#include "control.h"
#include <stdio.h> 

// ??? SETUP ????????????????????????????????
void setupSerial(void) {
    unsigned char dummy;
    BAUDCONbits.BRG16 = 0;
    TXSTA = 0;
    SPBRG = 25;
    SPBRGH = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    RCSTA = 0;
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
    dummy = RCREG;
    dummy = RCREG;
}

// ??? LOW LEVEL ????????????????????????????
unsigned char is_byte_available(void) {
    if (RCSTAbits.FERR || RCSTAbits.OERR) {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    return PIR1bits.RCIF ? 1 : 0;
}

unsigned char read_byte_no_lib(void) {
    return RCREG;
}

void send_byte_no_lib(unsigned char c) {
    while (!TXSTAbits.TRMT) { CLRWDT(); }
    TXREG = c;
}

void send_string_no_lib(unsigned char *p) {
    while (*p) {
        send_byte_no_lib(*p);
        p++;
    }
}

// ??? COMMANDS ?????????????????????????????
void uart_handle_commands(void)
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
        else if (ch == 't')
        {
            char buf[25];
            send_string_no_lib((unsigned char*)"\r\n"); 
            unsigned long temp = cookingTime;
            unsigned int hours   = temp / 3600;
            unsigned int minutes = (temp % 3600) / 60;
            unsigned int seconds = temp % 60;
            sprintf(buf, "Time: %02u:%02u:%02u\r\n", hours, minutes, seconds);
            send_string_no_lib((unsigned char*)buf);
        }
        else if (ch == 's')
        {
            char buf[25];
            send_string_no_lib((unsigned char*)"\r\n"); 
            unsigned long temp = cookingTime;
            unsigned int hours   = temp / 3600;
            unsigned int minutes = (temp % 3600) / 60;
            unsigned int seconds = temp % 60;
            
            sprintf(buf, "Time: %02u:%02u:%02u\r\n", hours, minutes, seconds);
            send_string_no_lib((unsigned char*)buf);
            
            sprintf(buf, "CT:%5.1fC CK:%s\r\n", CT, cooking_on ? "ON" : "OFF");
            send_string_no_lib((unsigned char*)buf);
            
            sprintf(buf, "SP:%5.1fC HT:%s\r\n", SP, heater_on ? "ON" : "OFF");
            send_string_no_lib((unsigned char*)buf);
            
            sprintf(buf, "MD:%-6s CL:%s\r\n",
                mode == 0 ? "Sec"   : mode == 1 ? "10Sec" :
                mode == 2 ? "Min"   : mode == 3 ? "10Min" : "HR",
                cooler_on ? "ON" : "OFF");
            send_string_no_lib((unsigned char*)buf);
        }
    }
}
