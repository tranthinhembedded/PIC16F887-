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

const char dat_line1[] = {0x54,0x00,0x01,0x6E,' ',0x02,0x03,0x63,' ',0x54,0x68,0x04,0x6E,0x68}; //Tran Duc Th?nh co dau
const char dat_line2[] = {'B',0x06,'i',' ','t',0x01,'p',' ','n','g',0x05,'t'}; 

const char cgram_dat[] = 
{
    0x00, 0x00, 0x00, 0x18, 0x14, 0x10, 0x10, 0x00, //r 0
    8, 20, 0, 28, 20, 30, 8, 0, // aa nang 1
    0X0E, 0X09, 0X09, 0X1D, 0X09, 0X09, 0X0E, 0X00, // Ð 2
    0x04, 0x08, 0x12, 0x01, 0x12, 0x12, 0x1E, 0x00, //uu sac 3
    0, 4, 0, 12, 4, 0, 4, 0, //i nang 4
    4, 8, 20, 8, 28, 20, 30, 0, // aw sac 5
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
void sangDuoi()
{
    ANSEL = ANSELH = 0x00;
    TRISB3 = TRISB4 = TRISB5 = 1;

    TRISB3 = TRISB4 = 0;
    TRISB5 = 1;
    RB3 = 1;
    RB4 = 0;
    __delay_ms(500);
    TRISB3 = TRISB4 = 0;
    TRISB5 = 1;
    RB3 = 0;
    RB4 = 1;
    __delay_ms(500);
    TRISB4 = TRISB5 = 0;
    TRISB3 = 1;
    RB4 = 1;
    RB5 = 0;
    __delay_ms(500);
    TRISB4 = TRISB5 = 0;
    TRISB3 = 1;
    RB4 = 0;
    RB5 = 1;
    __delay_ms(500);
    TRISB3 = TRISB5 = 0;
    TRISB4 = 1;
    RB3 = 0;
    RB5 = 1;
    __delay_ms(500);
    TRISB3 = TRISB5 = 0;
    TRISB4 = 1;
    RB3 = 1;
    RB5 = 0;
    __delay_ms(500);
    RB3 = 0;
    RB5 = 0;
    
   
    
    }
    

void __interrupt() ISR(void)
{ 
    __delay_ms(250);
    INTF = 0; 
    sangDuoi();
    
}


void main()
{
    unsigned char i, j;
    ANSEL = ANSELH = 0x00;
    TRISD = 0x00;  
    PORTD = 0x00;
    
    TRISB0 = 1;
    nRBPU = 0;
    WPUB0 = 1;
    
    INTF = 0; // tat c? ngat
    GIE = 1; //ngat toan cuc
    INTE = 1; //cho phep ngat ngoai
    INTEDG = 1; //canh len
    
    lcd_init(); 
    load_custom_characters(cgram_dat, 0);
    lcd_putc('\f');
    
    while(1){
    lcd_gotoxy(0, 1); 
    for(j = 0; j <= 13; j++) 
        lcd_putc(dat_line1[j]); 
    lcd_gotoxy(0, 0);
    
    for(i = 0; i<= 11; i++)
        lcd_putc(dat_line2[i]);
    __delay_ms(500);
    lcd_putc('\f');
    __delay_ms(500);
    }
    
}
