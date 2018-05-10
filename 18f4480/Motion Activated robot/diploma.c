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
int pir,exp,s;
TRISC = 0x00;
PORTC = 0x00;
set_lcdport();
lcd_init();
lcd_goto(1);
lcd_puts("ROBOT");
lcd_goto(21);
lcd_puts("Human:");
lcd_goto(41);
lcd_puts("Explosive:");
lcd_goto(61);
lcd_puts("Sound:");
adc_init();

 
while(1)
{
adc_channel(1);
pir = adc_result();
lcd_goto(28);
lcd_putn(pir);
lcd_puts("    ");
/*-----------------------------------*/
adc_channel(2);
exp = adc_result();
lcd_goto(52);
lcd_putn(exp);
lcd_puts("    ");
/*-----------------------------------*/
adc_channel(3);
s = adc_result();
lcd_goto(67);
lcd_putn(s);
lcd_puts("    ");
/*----------------------------------*/

if(pir>500)
{
BUZZER = ON;
DelayMs(50);
BUZZER = OFF;
DelayMs(50);
}
else if(exp>500)
{
BUZZER = ON;
DelayMs(50);
BUZZER = OFF;
DelayMs(50);
BUZZER = ON;
DelayMs(50);
BUZZER = OFF;
DelayMs(50);
}
else if(s>500)
{
BUZZER = ON;
DelayMs(50);
BUZZER = OFF;
DelayMs(50);
BUZZER = ON;
DelayMs(50);
BUZZER = OFF;
DelayMs(50);
}
else
BUZZER = OFF;
}
}
