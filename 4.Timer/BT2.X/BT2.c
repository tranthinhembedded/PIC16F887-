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

const char dat_line1[] = {0x54,0x68,0x04,0x6E,0x68,' ','C','o','u','n','t','e','r',' ','1'}; 

const char cgram_dat[] = 
{
    0x00, 0x00, 0x00, 0x18, 0x14, 0x10, 0x10, 0x00, //r 0
    2, 9, 20, 0, 28, 20, 30, 0, // aa huyen 1
    0X0E, 0X09, 0X09, 0X1D, 0X09, 0X09, 0X0E, 0X00, // Ð 2
    0x04, 0x08, 0x12, 0x01, 0x12, 0x12, 0x1E, 0x00, //uu sac 3
    0, 4, 0, 12, 4, 0, 4, 0, //i nang 4
    0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00, 0x04, // o nang 5
    8, 4, 0, 12, 20, 20, 30, 0, // a huyen 6
    0, 0, 6, 2, 28, 20, 28, 0, // o huyen 7
  
    
0x99};


void load_custom_characters(const char* custom_data, unsigned char start_address) {
    unsigned char i = 0;
    lcd_put_byte(0, 0x40 + (start_address * 8)); // Set CGRAM address 
    while(lcd_busy());
    while(custom_data[i] != 0x99) {
        lcd_put_byte(1, custom_data[i]);
        while(lcd_busy());
        i++;
    }
}

void main()
{
    ANSEL = ANSELH = 0x00;
    
    TRISC0 = 1;
    char data[4];
    TMR1=0;
    TMR1IF=0;
    TMR1CS=1;
    T1OSCEN=0;
    GIE=PEIE=TMR1IE=0;
    T1CKPS1=0; T1CKPS0=0;
    T1SYNC=0;
    TMR1ON=1;
    


    lcd_init(); 
    load_custom_characters(cgram_dat, 0);  
    lcd_putc('\f'); 
    lcd_gotoxy(0, 0);
    for(int i = 0 ;i <= sizeof(dat_line1)-1; i++)
    {
        lcd_putc(dat_line1[i]);
    }
    lcd_gotoxy(8, 1); 
    lcd_puts("00"); 
    while(1){
        if(TMR1 > 30) TMR1 = 0;
        sprintf(data, "%.2d", TMR1);
        lcd_gotoxy(8, 1); 
        lcd_puts(data); 
    }
    
}




