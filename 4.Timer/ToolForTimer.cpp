#include <stdio.h>

#define _XTAL_FREQ 4000000  

unsigned char calculate_TMR0(float t_delay, unsigned char pre) {
    float f_osc = _XTAL_FREQ / 1000000.0;  
    unsigned char TMR0_val = 256 - (t_delay * f_osc) / (4 * pre);
    return TMR0_val;
}

int main() {
    unsigned char prescaler_values[] = {2, 4, 8, 16, 32, 64, 128, 256};  
    unsigned char i, TMR0_value;
    float t_delay = 1000.0;

    for(i = 0; i < 8; i++) {
        TMR0_value = calculate_TMR0(t_delay, prescaler_values[i]);
        if (TMR0_value <= 255) {
            printf("Pre = 1:%d, TMR0 = %d\n", prescaler_values[i], TMR0_value);
        } else {
            printf("Pre = 1:%d, TMR0 gia tri khong hop le\n", prescaler_values[i]);
        }
    }

    while(1); 
}

