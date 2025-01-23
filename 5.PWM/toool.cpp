#include <stdio.h>
#include <math.h>

int main()
{
	float a, b;
	printf("Nhap tan so f: ");
	scanf("%.2f", &a);
	printf("T_pwm: %.2f", (1.0/a)*1000000);
}
