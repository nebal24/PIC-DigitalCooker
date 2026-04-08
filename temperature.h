#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "global.h"
#include "adc.h"

float read_SP(void);      // read & scale potentiometer AN0 ? 0-200°C
void  display_SP(void);   // display SP on LCD Line 3

float read_CT(void);     // read sensor 
void display_CT(void);   //display CT on LCD Line 2

void control_heater(void);

void display_MD_CL(const char* modeText);

#endif