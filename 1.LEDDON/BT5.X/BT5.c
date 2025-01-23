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
void sangDuoiPORTCD()
{
    for(int i = 0; i < 16; i++) {  // Sáng d?n t?ng LED
            if(i < 8) {
                PORTC = (1 << i);  // ?i?u khi?n 8 LED ? PORTC
                PORTD = 0x00;      // T?t 8 LED ? PORTD
            } else {
                PORTD = (1 << (i - 8));  // ?i?u khi?n 8 LED ? PORTD
                PORTC = 0x00;            // T?t 8 LED ? PORTC
            }
            __delay_ms(300);
        }
        PORTC = 0x00;  // T?t t?t c? LED ? PORTC
        PORTD = 0x00;  // T?t t?t c? LED ? PORTD
        __delay_ms(300);
    
}

void sangDanPORTCD()
{
        for(int i = 0; i < 16; i++) {  // Sáng d?n t?ng LED
            if(i < 8) {
                PORTC |= (1 << i);  // ?i?u khi?n 8 LED ? PORTC
                PORTD = 0x00;      // T?t 8 LED ? PORTD
            } else {
                PORTC = 0xFF;// T?t 8 LED ? PORTC
                PORTD |= (1 << (i-8));  // ?i?u khi?n 8 LED ? PORTD
                            
            }
            __delay_ms(300);
        }
        PORTC = 0x00;  // T?t t?t c? LED ? PORTC
        PORTD = 0x00;  // T?t t?t c? LED ? PORTD
        __delay_ms(300);
        
    
        
}

void ledChopTat()
{
    PORTD = 0x00;
    PORTC = 0x00;
    __delay_ms(500);
    PORTD = 0xFF;
    PORTC = 0xFF;
    __delay_ms(500);
}

void main(void) 
{
    unsigned char i, j;
    ANSEL = 0;   
    ANSELH = 0;  
    
    TRISD = 0x00;  
    PORTD = 0x00;
    TRISC = 0x00;  
    PORTC = 0x00;
    
   
        for(i = 0; i < 2; i++)
        {
        for(j = 0; j < 4; j++)
        {
            ledChopTat();
            PORTD = 0x00;
            PORTC = 0x00;
        }
        __delay_ms(300);
        
        for(j = 0; j < 2; j++)
        {
            
            sangDuoiPORTCD();
            
        }
        __delay_ms(300);
        
        for(j = 0; j < 3; j++)
        {
            sangDanPORTCD();
           
        }
        __delay_ms(300);
        
        }    
    
      
     PORTD = 0xFF; PORTC = 0xFF;
     while(1);
    
}
