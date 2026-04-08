#ifndef DISPLAY_H
#define DISPLAY_H

const char* getModeText(void);
void displayTime(void);
void display_SP_HT(void);
void display_CT_CK(void);
void display_MD_CL(const char* modeText);
void uart_display_time(void);
void uart_display_status(void);

#endif