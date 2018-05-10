#include<p18f4480.h>
#include"delay.h"
#include"servo_driver.c"
#include"adc_driver.c"
#include"lcd_driver.c"

#pragma config OSC = IRCIO7
#pragma config WDT = OFF
#pragma config MCLRE = ON 

void main()
{
int x;
OSCCON = 0b01100000;
adc_init();
servo_init();
while(1)
{
x= adc_result();
servo_angle(x);
}
}
