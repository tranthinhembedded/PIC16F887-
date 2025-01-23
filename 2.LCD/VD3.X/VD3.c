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

const char dat_line1[] = "KHOA"; // Noi dung hien thi Hang 1.
const char dat_line2[] = {0x43,0X4E,' ',0x00,0X69,0X01,0X6E,' ',0X54,0X02}; // Noi dung hien thi -Hang 2.
const char cgram_dat[] = { 
0X0E,0X09,0X09,0X1D,0X09,0X09,0X0E,0X00, // Ð
0x0C,0x12,0x0C,0x1E,0X10,0x1E,0x04,0x00, // ?
0X0C,0X02,0X05,0X12,0X12,0X12,0X0C,0X00, // ?
0x99 }; // Ma ket thuc chuoi la 99H 
void main()
{
unsigned char i;
lcd_init(); // Khoi dong LCD 
// Xu ly nap ma ky tu dac biet vao CGRAM.
i = 0;
lcd_put_byte(0,0x40); // Lenh = 40H - Dat CGRAM co dia chi bat dau la 00H.
while(lcd_busy()); // Kiem tra LCD bao ban.
while(cgram_dat[i]!=0x99) // Kiem tra nap xong du lieu cho cac ky tu dac biet,
{ // ky tu ket thuc chuoi la 99H.
lcd_put_byte(1,cgram_dat[i]); // Ghi cac ma ky tu dac biet vao CGRAM theo dia chi.
while(lcd_busy()); // Kiem tra LCD bao ban.
i++;
} 
lcd_putc('\f'); // xóa màn hình
lcd_gotoxy(5,0); // Xac dinh toa do bat dau hien thi cho hang 1.
lcd_puts(dat_line1); 
lcd_gotoxy(2,1); // Xac dinh toa do bat dau hien thi cho hang 2.
for(i=0;i<=9;i++)
lcd_putc(dat_line2[i]); 
while(1);}




