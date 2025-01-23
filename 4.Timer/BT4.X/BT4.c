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
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))


const char dat_line1[] = {0x54,0x00,0x01,0x6E,' ',0x02,0x03,0x63,' ',0x54,0x68,0x04,0x6E,0x68}; //Tran Duc Thinh
const char dat_line2[] = {'B', 0x06, 'i',' ','T',0x07,'p',' ','T','i','m','e','r','1'};


const char cgram_dat[] = 
{
    0x00, 0x00, 0x00, 0x18, 0x14, 0x10, 0x10, 0x00, //r 0
    2, 9, 20, 0, 28, 20, 30, 0, // aa huyen 1
    0X0E, 0X09, 0X09, 0X1D, 0X09, 0X09, 0X0E, 0X00, // Ð 2
    0x04, 0x08, 0x12, 0x01, 0x12, 0x12, 0x1E, 0x00, //uu sac 3
    0, 4, 0, 12, 4, 0, 4, 0, //i nang 4
    0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00, 0x04, // o nang 5
    8, 4, 0, 12, 20, 20, 30, 0, // a huyen 6
    8, 20, 8, 20, 28, 20, 8, 0, // aa nang 7
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
void delay100us(unsigned int n)
{ while(n--)
{
TMR1 = 65511;
TMR1H=TMR1/256; TMR1L=TMR1%256;
TMR1IF=0; //xóa c? ng?t
TMR1CS=0; //ch? ?? ??nh th?i
GIE=PEIE =TMR0IE = 0;//c?m ng?t 
T1CKPS1=1; T1CKPS0=0; //pre 4
T1SYNC=0;
TMR1ON=1;
while(TMR1IF==0); } }//ki?m tra c? TMR0IF=1?

void delay200ms(void)
{
delay100us(2000);
}
void shift_left_screen(int times)
{
    for(int i = 0; i < times; i++) {
        lcd_ShiftLeft();  
        delay200ms(); 
    }
}
void shift_right_screen(int times)
{
    for(int i = 0; i < times; i++) {
        lcd_ShiftRight();  
        delay200ms();  
    }
}

void in_chu()
{
        lcd_gotoxy(0, 0); 
        for(int j = 0; j <= sizeof(dat_line1)-1; j++) 
            lcd_putc(dat_line1[j]); 
        lcd_gotoxy(0, 1); 
        for(int j = 0; j <= sizeof(dat_line2)-1; j++) 
            lcd_putc(dat_line2[j]);
 
}

void chop_tat(unsigned times)
{
    for(int i = 0; i < times; i++) {
        lcd_gotoxy(0, 0); 
        for(int j = 0; j <= sizeof(dat_line1)-1; j++) 
            lcd_putc(dat_line1[j]); 
        lcd_gotoxy(0, 1); 
        for(int j = 0; j <= sizeof(dat_line2)-1; j++) 
            lcd_putc(dat_line2[j]);
        delay200ms();
        lcd_puts("\f");
        delay200ms();
    }
}

void main()
{
    lcd_init(); 
    load_custom_characters(cgram_dat, 0);  
    lcd_putc('\f');  
    
    chop_tat(3);
    lcd_puts("\f");
    
    for(int i = 0; i< 2; i++){
        in_chu();
        delay200ms();
        shift_left_screen(16);
        lcd_puts("\f");
    }
    
    for(int i = 0; i< 2; i++){
        in_chu();
        delay200ms();
        shift_right_screen(16);
        lcd_puts("\f");
    }
    
    in_chu();
            
    
    while(1);  
}



    

