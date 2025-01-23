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
const char dat_line1[] = {0x54,0x00,0x01,0x6E,' ',0x02,0x03,0x63,' ',0x54,0x68,0x04,0x6E,0x68}; //Tran Duc Th?nh co dau
const char dat_line2[] = {'T',0x05,'m',' ','b','i',0x06,'t'}; 

const char cgram_dat[] = 
{
    0x00, 0x00, 0x00, 0x18, 0x14, 0x10, 0x10, 0x00, //r 0
    2, 9, 20, 0, 28, 20, 14, 0, // aa huyen
    0X0E, 0X09, 0X09, 0X1D, 0X09, 0X09, 0X0E, 0X00, // Ð 2
    0x04, 0x08, 0x12, 0x01, 0x12, 0x12, 0x1E, 0x00, //uu sac 3
    0, 4, 0, 12, 4, 0, 4, 0, //i nang 4
    0, 0, 28, 20, 30, 0, 8, 0, // a nang
    8, 20, 8, 20, 24, 12, 8, 0, // ee nang
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
void nhan_nha_SW4()//1khz ccp1
{
    if(!RB0)
    {
        __delay_ms(50);
        while(!RB0);
        __delay_ms(50);
        //tao xung PWM
        lcd_init();
        lcd_gotoxy(6, 0);
        lcd_puts("f = 1kHz");
        lcd_gotoxy(6, 1);
        lcd_puts("D = 30%");
        
        TRISC2 = 1;
        TMR2 = 0;
        PR2 = 249;
        CCPR1L = 75;
        CCP1CON = 0x0C;
        DC1B1=0;DC1B0=0;
        TRISC2 = 0;
        TRISC1 = 0; RC1 = 0;
        T2CON = 0X05; //pre =4        

        }
}

void nhan_nha_SW5()//2khz ccp2
{
    if(!RB1)
    {
        __delay_ms(50);
        while(!RB1);
        __delay_ms(50);
        //tao xung PWM
        lcd_init();
        lcd_puts("\f");

        lcd_gotoxy(6, 0);
        lcd_puts("f = 2kHz");
        lcd_gotoxy(6, 1);
        lcd_puts("D = 80%");
        
        TRISC1 = 1;
       
        TMR2 = 0;
        PR2 = 124;
        CCPR2L = 100;
        CCP2CON = 0x0C;
        DC2B1=0;DC2B0=0;
        TRISC1 = 0;
        
        //c?m xu?t xung
        
        //pre = 4
        T2CON = 0X05;   
        
        TRISC2 = 0; RC2 = 0;

        }
}

void nhan_nha_SW6()//dung
{
    if(!RB2)
    {
        __delay_ms(50);
        while(!RB2);
        __delay_ms(50);
        //tao xung PWM
        lcd_init();
        load_custom_characters(cgram_dat, 0);
        lcd_putc('\f');
        
        lcd_gotoxy(0, 0); 
        for(int j = 0; j <= 13; j++) 
            lcd_putc(dat_line1[j]); 
        lcd_gotoxy(4, 1);
        for(int i = 0; i<= 7; i++)
            lcd_putc(dat_line2[i]);
        TRISC2 = TRISC1 = 1;
        RE0 = 0;
    }
    
        
}


void main()
{
    ANSEL = ANSELH = 0x00;
   
    TRISB = 0xFF;
    nRBPU = 0;
    WPUB = 0xFF;
    
    TRISE0=0; //setup_motor
    RE0=1;

    nhan_nha_SW4();
    nhan_nha_SW5();
    nhan_nha_SW6();
    
}




