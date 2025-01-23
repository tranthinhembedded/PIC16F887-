#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
unsigned char MaLed[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char MaLed7Seg_nghich[] = {0x90,0x80,0xF8,0x82,0x92,0x99,0xB0,0xA4,0xF9,0xC0};

void choptat (unsigned char n)
{ 
    while(n--){
        PORTD = 0xFF;
        __delay_ms(300);
        PORTD = 0x00;
        __delay_ms(300);
    }
}

void sangDuoi(unsigned char n)
{
    while(n--){
        unsigned char  j, temp;
        PORTD = 0x00;  
        __delay_ms(300);

        temp = 0x80; 
        for(j = 0; j < 8; j++) {
            PORTD = temp; 
            __delay_ms(300);  
            temp = temp >> 1;  
        }
    }
    
}

void sangDan(unsigned char n)
{
    while(n--){
    unsigned char a = 0x80;
    unsigned char i;
    PORTD = 0x00;
    __delay_ms(300);
    PORTD = a;
    __delay_ms(300);
    for(i = 0; i < 8; i++)
    {
        a |= a >> 1;
        PORTD = a;
        __delay_ms(300);
    }
    }
}

void main(void) 
{
    unsigned char i, j;
 
    ANSEL = 0;   
    ANSELH = 0; 
    
    TRISB0 = TRISB1 = TRISB2 = 1;
    nRBPU = 0;
    WPUB0 = WPUB1 = WPUB2 = 1;
    
    TRISD = 0x00;  
    PORTD = 0x00;
   
    while(1)
    {
        if(!RB0)
        {
            __delay_ms(5);
            while(!RB0);
            __delay_ms(5);
            choptat(4);
         }
        else if(!RB1)
        {
            __delay_ms(5);
            while(!RB1);
            __delay_ms(5);
            sangDuoi(2);
         }
        else if(!RB2)
        {
            __delay_ms(5);
            while(!RB2);
            __delay_ms(5);
            sangDan(2);
         }
    }
}