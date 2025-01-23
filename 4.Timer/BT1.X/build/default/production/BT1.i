# 1 "BT1.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "BT1.c" 2
TMR0 = 231;
        TMR0IF = 0;
        T0CS = 0;
        GIE=PEIE =TMR0IE = 0;
        PSA = 0; PS2 = 0; PS1 = 0; PS0 = 1;
        while(TMR0IF==0);
    }
}

void main() {
    unsigned char i, j;
    lcd_init();
    load_custom_characters(cgram_dat, 0);
    lcd_putc('\f');


    for(i = 0; i < 3; i++) {
        lcd_gotoxy(0, 0);
        for(j = 0; j <= 9; j++)
            lcd_putc(dat_line1[j]);
        lcd_gotoxy(0, 1);
        lcd_puts(dat_line2);
        delay100us(300);
        lcd_putc('\f');
        delay100us(300);
    }


    lcd_putc('\f');
    lcd_gotoxy(0, 0);
    for(i = 0; i <= 9; i++)
        lcd_putc(dat_line1[i]);
    lcd_gotoxy(0, 1);
    for(i = 0; i <= 14; i++)
        lcd_putc(dat_line2[i]);
    delay100us(30);

    for (int positionCounter = 0; positionCounter < 17; positionCounter++) {
        lcd_ShiftLeft();
        delay100us(30);
    }


    lcd_putc('\f');
    lcd_gotoxy(0, 0);
    for(i = 0; i <= 9; i++)
        lcd_putc(dat_line1[i]);
    lcd_gotoxy(0, 1);
    for(i = 0; i <= 14; i++)
        lcd_putc(dat_line2[i]);
    delay100us(30);

    for (int positionCounter = 0; positionCounter < 17; positionCounter++) {
        lcd_ShiftRight();
        delay100us(30);
    }

    lcd_putc('\f');
}
