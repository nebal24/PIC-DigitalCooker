#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "global.h"
#include "adc.h"

float read_SP(void);      // read & scale potentiometer AN0 ? 0-200°C
void  display_SP(void);   // display SP on LCD Line 3

#endif