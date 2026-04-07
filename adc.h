
#ifndef ADC_H
#define	ADC_H

#include <xc.h>   

void init_adc(void);
int read_adc_raw(unsigned char channel);
float read_adc_voltage(unsigned char channel);

#endif	

