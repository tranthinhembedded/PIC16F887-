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
#include "lcd.h"
#define _XTAL_FREQ 4000000
unsigned char demS0, demS1, demS2;

void __interrupt()ISR(void)
{

    PORTB;
    __delay_ms(300);
    char dataS0[4];
    char dataS1[4];
    char dataS2[4];
    if(!RB0){ 
        demS0++;  
        if(demS0 == 11){
            demS0 = 0; 
        }
        sprintf(dataS0, "%.2d", demS0);
        lcd_gotoxy(0, 1); 
        lcd_puts(dataS0); 
    }
    else if(!RB1){ 
        demS1++;  
        if(demS1 == 11){
            demS1 = 0; 
        }
        sprintf(dataS1, "%.2d", demS1);
        lcd_gotoxy(7, 1); 
        lcd_puts(dataS1);
    }
    else if(!RB2){ 
        demS2++;  
        if(demS2 == 11){
            demS2 = 0; 
        }
        sprintf(dataS2, "%.2d", demS2);
        lcd_gotoxy(14, 1); 
        lcd_puts(dataS2);
    }
    
    RBIF = 0;
    
 
}

void main()
{
    ANSEL = ANSELH = 0x00;
    // dien tro keo len
    TRISB = 0xFF;
    nRBPU = 0;
    WPUB = 0xFF;
    // ngat PORTB
    RBIF = 0;
    RBIE = 1;
    GIE = 1; // cho phep ngat toan cuc
    
    IOCB = 0xFF; // cho phép ng?t ngoài c? PORT
    
    demS0 = 0;
    demS1 = 0;
    demS2 = 0;
    PORTB;
    
   
    lcd_init();
    lcd_gotoxy(0, 0);
    lcd_puts("S1");
    
    lcd_gotoxy(7, 0);
    lcd_puts("S2");
    
    lcd_gotoxy(14, 0);
    lcd_puts("S3");
    
    lcd_gotoxy(0, 1); 
    lcd_puts("00"); 
    
    lcd_gotoxy(7, 1); 
    lcd_puts("00"); 
    
    lcd_gotoxy(14, 1); 
    lcd_puts("00"); 
    while(1);
}




