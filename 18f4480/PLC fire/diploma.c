#include<p18f4480.h>
#include"delay.h"
#include"lcd_driver.c"
#include"adc_driver.c"
/*----------------- configuration bits---------------------------------*/
#pragma config OSC = IRCIO67
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON
/*---------------------------------------------------------------------*/


#define MOTOR1    LATCbits.LATC0
#define MOTOR2    LATCbits.LATC1
#define BUZZER    LATCbits.LATC2

#define ON       1
#define OFF      0

void main()
{
int Distance;
TRISC = 0x00;
PORTC = 0x00;
set_lcdport();
lcd_init();
lcd_goto_pos(1);
lcd_puts("Coastal Network");
lcd_goto_pos(17);
lcd_puts("DISTANCE:");
adc_init();
MOTOR1    = ON;
MOTOR2    = OFF;
 
while(1)
{
adc_channel(1);
Distance = adc_result();
lcd_goto_pos(26);
lcd_putn(Distance);
lcd_goto_pos(26);
lcd_puts("      ");

if((Distance  < 200))
{

MOTOR1    = ON;
MOTOR2    = ON;

BUZZER   = ON ; // turns off red led

}
else 
{

MOTOR1    = ON;
BUZZER    = OFF;
MOTOR2    = OFF;

}
}
}
