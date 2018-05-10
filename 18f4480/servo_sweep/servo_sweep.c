#include<p18f4480.h>
#include "delay.h"
#include "lcd_diver.c"
#include "adc_driver.c"
#include "servo_driver.c"

/*****************Configuration************************/
//#pragma config OSC = IRCIO7
//#pragma config WDT = OFF
//#pragma config MCLRE = ON 

void main()
{
	int i;

	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	//OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)
	
	


servo_init();
adc_init();
set_lcdport();
lcd_init();
lcd_goto(1);
lcd_puts("Sensor Values");
while(1)
{
int x;
//adc_channel(1);
//x=adc_result();
//x= x/5.68;
//lcd_goto(21);
//lcd_puts("Accelerometer:");
//lcd_goto(36);
//lcd_putn(x);
//lcd_puts("   ");
for(x =0;x <=180;x +=1 )
{
servo_angle(x);
//DelayMs(5);
}

for(x =180;x >=0;x -= 1 )
{
servo_angle(x);
//DelayMs(5);
}

}
//adc_channel(1);
//y=adc_result();
//lcd_goto(41);
//lcd_puts("Humidity     :");
//lcd_goto(56);
//lcd_putn(y);
//lcd_puts("   ");
//
//if( x>=370)
//{
//lcd_goto(1);
//lcd_puts("Sensor Values");
//lcd_goto(61);
//lcd_puts("Accelerometer Alert");
//lcd_puts("                    ");
//}
//else if( y < 800)
//{
//lcd_goto(1);
//lcd_puts("Sensor Values");
//lcd_goto(61);
//lcd_puts("Humidity Alert");
//lcd_puts("                    ");
//}
//else 
//{
//lcd_goto(1);
//lcd_puts("Sensor Values");	
//lcd_goto(61);
//lcd_puts("                    ");
//
//}


//}

}
