#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
//3kHZ
void setup_ccp1(void) //75%
{
    TRISC2 = 1;
    TMR2 = 0;
    PR2 = 82;
    CCPR1L = 63;
    CCP1CON = 0x0C;
    DC1B1=1;DC1B0=0;
    TRISC2 = 0;
    T2CON = 0X05; //pre =4
    
}

void setup_ccp2(void) //25%
{
    TRISC1 = 1;
    TMR2 = 0;
    PR2 = 82;
    CCPR2L = 21;
    CCP2CON = 0x0C;
    DC2B1=1;DC2B0=0;
    TRISC1 = 0;
    //pre = 4
    T2CON = 0X05;
}


void main()
{
    ANSEL=ANSELH=0;
    TRISE0=0; //setup_motor
    RE0=1;
    TRISB = 0xFF;
    nRBPU = 0;
    WPUB = 0xFF;
    if(!RB0){
        __delay_ms(10);
        while(!RB0);
        __delay_ms(10);
        
    }
    setup_ccp1();
    
    while(1);
}




