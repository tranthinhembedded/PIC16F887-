#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = OFF      
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = OFF      
#pragma config IESO = ON        
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        

#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF        

#include <xc.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#define _XTAL_FREQ 4000000

const char dat_line1[] = {0x54,0x00,0x01,0x6E,' ',0x02,0x03,0x63,' ',0x54,0x68,0x04,0x6E,0x68}; 
const char dat_line2[] = "MSSV: 21122091"; 

const char dat_line3[] = {'N','g',0x06,'y',' ','S','i','n','h',':','1','0','/','0','3'}; 
const char dat_line4[] = {'N',0x07,'i',' ','S','i','n','h',':','K','i',0x01,'n','G','i','a'}; 

const char dat_line5[] = {'H','K','T','T',':','H',0x07,'n',' ',0x02,0x06,'t'}; 
const char dat_line6[] = {'L',0x04,'p',':',0x02,'H','V','T','1','5','A'}; 

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
const char cgram_dat_e[] = 
{
    8, 20, 0, 12, 20, 24, 12, 0, // ê 8
    
0x99};

const char cgram_dat_aa[] = 
{
    1, 10, 20, 0, 28, 20, 30, 0, //aa sac
0x99};

const char cgram_dat_ows[] = 
{
    2, 4, 1, 15, 10, 10, 14, 0, //ow sac
    
0x99};
const char cgram_dat_0hn[] = 
{
    8, 4, 0, 14, 10, 10, 14, 0, // o huyen
    
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
    unsigned char i, j;
    lcd_init(); 
    load_custom_characters(cgram_dat, 0);
    lcd_putc('\f');
    
    for(i = 0; i < 3; i++) {
        lcd_gotoxy(0, 0); 
        for(j = 0; j <= 13; j++) 
            lcd_putc(dat_line1[j]); 
        lcd_gotoxy(0, 1); 
        lcd_puts(dat_line2);
        __delay_ms(1000);
        lcd_puts("\f");
        __delay_ms(1000);
    }
    lcd_puts("\f");
    //noi dung 2
    load_custom_characters(cgram_dat_e,1);
    lcd_gotoxy(0,0); 
    for(i=0;i<=14;i++)
    lcd_putc(dat_line3[i]); 
    lcd_gotoxy(0,1); 
    for(i=0;i<=16;i++)
    lcd_putc(dat_line4[i]);
    __delay_ms(2000);
    for (int positionCounter = 0; positionCounter < 17; positionCounter++) {
        // Cu?n 1 v? trí sang trái:
        lcd_ShiftLeft();
        // delay:
        __delay_ms(200);
    }
    lcd_puts("\f");
    //noi dung 3
    load_custom_characters(cgram_dat_aa,6);
    load_custom_characters(cgram_dat_0hn,7);
    load_custom_characters(cgram_dat_ows,4);
    lcd_gotoxy(0,0); 
    for(i=0;i<=11;i++)
    lcd_putc(dat_line5[i]); 
    lcd_gotoxy(0,1); 
    for(i=0;i<=10;i++)
        lcd_putc(dat_line6[i]);
    __delay_ms(2000);
    for (int positionCounter = 0; positionCounter < 17; positionCounter++) {
        // Cu?n 1 v? trí sang trái:
        lcd_ShiftRight();
        // delay:
        __delay_ms(200);
    }
    lcd_puts("\f");
    
}
