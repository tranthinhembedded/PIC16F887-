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

void main()
{
   
    lcd_init();//kh?i ??ng LCD
    while(1)
    {
        lcd_gotoxy(0,0);
        lcd_puts("TRAN DUC THINH");
        lcd_gotoxy(0,1);
        lcd_puts("MSSV: 21122091");
        __delay_ms(2000);
        lcd_puts("\f");
        
        lcd_gotoxy(0,0);
        lcd_puts("Ngay sinh: 10/03");
        lcd_gotoxy(0,1);
        lcd_puts("Noi sinh: KG");
        __delay_ms(2000);
        lcd_puts("\f");
        
        lcd_gotoxy(0,0);
        lcd_puts("HKTT: HCM");
        lcd_gotoxy(0,1);
        lcd_puts("Lop: DHDTMT17CTT");
        __delay_ms(2000);
        lcd_puts("\f");
    }
}




