#include "uart.h"
#include "global.h"
#include "control.h"
#include "display.h"
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
    send_string_no_lib((unsigned char*)"\r\n");
    uart_display_time();
}
else if (ch == 's')
{
    send_string_no_lib((unsigned char*)"\r\n");
    uart_display_status();
}
        
    }
}
