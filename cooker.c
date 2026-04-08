
// PIC18F4620 Configuration Bit Settings

// 'C' source line config statements
#define _XTAL_FREQ   4000000UL 
// CONFIG1H
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include "global.h"
#include "interrupt_handlers.h"
#include "display.h"
#include "buttons.h"
#include "delay.h"
#include "control.h"
#include "uart.h"
#include "temperature.h"
#include "adc.h"
#include "lcd.h"
#include "timer0.h"

void setupPorts(void)
{
//initialize ADCON1
     ADCON1 = 0x0C;
//configure TRISX : direction
    //INPUTS 
    TRISBbits.TRISB0 = 1;  // INT0
    TRISBbits.TRISB1 = 1;  // INT1
    TRISBbits.TRISB2 = 1;  // INT2
    TRISBbits.TRISB3 = 1;  // increment
    TRISBbits.TRISB4 = 1;  // decrement
    TRISBbits.TRISB5 = 1;  // cancel
    
    TRISAbits.TRISA5 = 1;  // cooler button
    
    TRISCbits.TRISC7 = 1;  // RX
    
    //OUTPUTS
    TRISCbits.TRISC2 = 0;  // cooler
    TRISCbits.TRISC5 = 0;  // heater
    
    TRISCbits.TRISC6 = 0;  // TX
    
    
// Initial states
    PORTCbits.RC2 = 0;
    PORTCbits.RC5 = 0;


TRISD = 0x00;              // LCD data bus on PORTD -> output
TRISEbits.TRISE1 = 0;      // LCD E  -> output
TRISEbits.TRISE2 = 0;      // LCD RS -> output

PORTD = 0x00;
PORTEbits.RE1 = 0;
PORTEbits.RE2 = 0;

TRISCbits.TRISC1 = 0;
PORTCbits.RC1 = 0;
}



void main(void)
{
    // ?? INIT ??????????????????????????
    setupPorts();
    setupINT0();
    setupINT1();
    setupINT2();
    setupTimer0();
    lcd_init();
    init_adc();
    setupSerial();

    // ?? MAIN LOOP ?????????????????????
    while(1)
    {
        check_cancel_button();
        uart_handle_commands();
        handleIncrementButton();
        handleDecrementButton();
        handleCoolerButton();

        read_SP();
        read_CT();

        displayTime();
        display_CT_CK();
        display_SP_HT();
        display_MD_CL(getModeText());

        control_heater();

        if (cooking_done_flag)
        {
            cooking_done_flag = 0;
            beep_buzzer();
        }
    }
}


