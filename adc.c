
#include "adc.h"

void init_adc(void) 
{
    ADCON0 = 0;
    ADCON0bits.ADON = 1; // turn adc on 
    ADCON2 = 0b10001001;
}

int read_adc_raw(unsigned char channel) 
{
    int raw_value; //0--1023, or short raw_value, need 16 bit value  
     ADCON0bits.CHS = channel ;// better use channel & 0x0F;    // select the channel, 4 bit value , &0x0F is not eeded
    ADCON0bits.GO = 1;// start conversion
    while (ADCON0bits.GO) {CLRWDT();}; // wait until conversion is done, you can put CLRWDT() in the loop, but not necessary
    raw_value = ADRESH << 8 | ADRESL;  // 10 bit, need to shift the bits right, this puts the result in one 16 bit variable
    return raw_value; // 16 bit , it is actually 10 bit 0 ---1023
}

float read_adc_voltage(unsigned char channel) {
    int raw_value;
    float voltage;
    raw_value = read_adc_raw(channel);
    voltage = (raw_value * 5) / 1023.0;
    return voltage;
    //suppose in the above we had a temperature with sensor range -10 ---50C
    // Then we will convert as follows
    // float temp ;
    // temp = (raw_value * ( 50 - (-10)) /1023.0  + (-10.0); // parentheses used to illustrate max  and min range
    //return temp 
 
/**   
 In General we map 0? 5 to  0?1023 (raw and if we map it to a range Say Tmin to Tmax 
 Then T = raw-value * (Tmax-Tmin)/1023.0 + Tmin.
 In the Above Temp is T, Tmax = 50 , Tmin = -10.0   
 Here we are reading a sensor in the range 0?5 corresponding to -10C ---- 50C
 */
}

