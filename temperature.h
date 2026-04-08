#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "global.h"
#include "adc.h"

float read_SP(void);      // read & scale potentiometer AN0 ? 0-200°C
float read_CT(void);     // read sensor 
void control_heater(void);

#endif