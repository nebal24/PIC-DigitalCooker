#ifndef GLOBAL_H
#define GLOBAL_H

#define H 1
#define MAX_TEMP 200.0

extern float SP;        // Setpoint
extern float CT;        // Cooking Temperature

extern unsigned char cooking_on;
extern unsigned char heater_on;
extern unsigned char cooler_on;

extern unsigned long cooking_time_seconds;

extern unsigned char flag_1s;

extern volatile unsigned char mode;

#endif