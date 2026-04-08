#ifndef UART_H
#define UART_H

#include <xc.h>

void setupSerial(void);
unsigned char is_byte_available(void);
unsigned char read_byte_no_lib(void);
void send_byte_no_lib(unsigned char c);
void send_string_no_lib(unsigned char *p);
void uart_handle_commands(void);

#endif