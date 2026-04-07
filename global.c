#include "global.h"

float SP = 0;
float CT = 0;

unsigned char cooking_on = 0;
unsigned char heater_on = 0;
unsigned char cooler_on = 0;

unsigned long cooking_time_seconds = 0;

unsigned char flag_1s = 0;

volatile unsigned char mode = 0;   // 0=Sec, 1=10Sec, 2=Min, 3=10Min, 4=HR