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
unsigned char push_count;

void __interrupt() ISR(void)
{
    char data[4]; 
    __delay_ms(150);
    push_count++;
    if (push_count > 20){
        push_count = 0;
    }
    sprintf(data, "%.2d", push_count); //chuyen tu so sang char
    lcd_gotoxy(8, 1); 
    lcd_puts(data); 
    INTF = 0; 
}

void main()
{
    ANSEL = ANSELH = 0x00;

    TRISB0 = 1;
    nRBPU = 0;
    WPUB0 = 1;
    
    INTF = 0; // c? ngat
    GIE = 1; //ngat toan cuc
    INTE = 1; //cho phep ngat ngoai
    INTEDG = 1; //canh len
    
    push_count = 0;
    lcd_init();
    lcd_gotoxy(0, 0);
    lcd_puts("TRAN THINH dem");
    lcd_gotoxy(8, 1); 
    lcd_puts("00"); 
    while(1);
}




