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
void shift_left_screen(int times)
{
    for(int i = 0; i < times; i++) {
        lcd_ShiftLeft();  // Cu?n trái toàn b? màn hình
        __delay_ms(200);  // ?? tr? cho hi?u ?ng cu?n
    }
}

void chaychu_1line(const char *line_data, int line_size, int line_number)
{
    for(int k = 15; k >= 0; k--) {
        lcd_gotoxy(k, line_number);  
        
        for(int j = 0; j <= 15 - k; j++) {   
            if(j < line_size) {
                lcd_putc(line_data[j]);  
            } else {
                lcd_putc(' ');  
            }
        }
        __delay_ms(200);  
    }
}

void chaychu_2line(const char *line_data1, const char *line_data2, int line_size1, int line_size2, int line_number1, int line_number2)
{
    for(int k = 15; k >= 0; k--) {
        lcd_gotoxy(k, line_number1);  
        
        for(int j = 0; j <= 15 - k; j++) {   
            if(j < line_size1) {
                lcd_putc(line_data1[j]);  
            } else {
                lcd_putc(' ');  
            }
        }
        
        lcd_gotoxy(k, line_number2);  
        
        for(int j = 0; j <= 15 - k; j++) {   
            if(j < line_size2) {
                lcd_putc(line_data2[j]);  
            } else {
                lcd_putc(' ');  
            }
        }
        __delay_ms(200);  
    }
}


void main()
{
    unsigned char j;
    lcd_init(); 
    load_custom_characters(cgram_dat, 0);  
    lcd_putc('\f');  

    int size_line1 = ARRAY_SIZE(dat_line1);  
    int size_line3 = ARRAY_SIZE(dat_line3);  
    
 
    for (int repeat = 0; repeat < 2; repeat++) {
        chaychu_2line(dat_line1, dat_line3, size_line1, size_line3, 0, 1); 
        shift_left_screen(16);  
        lcd_putc('\f'); 
    }

    while(1);  
}



    

