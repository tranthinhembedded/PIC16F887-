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

void choptat_Ab ()
{
        PORTC = 0x88;  
        PORTD = 0x83;
        __delay_ms(2000); 
        PORTC = 0xFF;
        PORTD = 0xFF;
        __delay_ms(2000);
}

void dem00_26()
{
    unsigned char i, j;
    unsigned char hangDonVi, hangChuc;
    for(i = 0; i<=26; i++)
        {
            hangDonVi = i % 10;
            hangChuc = i / 10;
            
            PORTC = MaLed[hangChuc];
            PORTD = MaLed[hangDonVi];
            __delay_ms(300);
        }
}

void dem99_00()
{
    unsigned char i, j;
    unsigned char hangDonVi, hangChuc;
    PORTD = MaLed7Seg_nghich[0];
    PORTC = MaLed7Seg_nghich[0];
    for(i = 0; i<=99; i++)
    {
        hangDonVi = i % 10;
        hangChuc = i / 10;
            
        PORTC = MaLed7Seg_nghich[hangChuc];
        PORTD = MaLed7Seg_nghich[hangDonVi];
        __delay_ms(300);
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
    
    TRISC = 0x00;  
    PORTC = 0xFF;
    TRISD = 0x00;  
    PORTD = 0xFF;
   
    while(1)
    {
        if(!RB0)
        {
            __delay_ms(5);
            while(!RB0);
            __delay_ms(5);
            choptat_Ab();
        }
        else if(!RB1)
        {
            __delay_ms(5);
            while(!RB1);
            __delay_ms(5);
            dem00_26();
         }
        else if(!RB2)
        {
            __delay_ms(5);
            while(!RB2);
            __delay_ms(5);
            dem99_00();
         }
    }
}