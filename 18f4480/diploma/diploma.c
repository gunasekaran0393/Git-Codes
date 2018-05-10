#include<p18f4480.h>
#include"delay.h"
#include"lcd_driver.c"
#include"adc_driver.c"
/*----------------- configuration bits---------------------------------*/
#pragma config OSC = IRCIO7
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON
/*---------------------------------------------------------------------*/


#define MOTOR    LATCbits.LATC0
#define BUZZER   LATCbits.LATC1
#define RF_GREEN LATCbits.LATC2
#define RF_RED   LATCbits.LATC3
#define ON       1
#define OFF      0

void main()
{
int IR;
TRISC = 0x00;
PORTC = 0x00;
set_lcdport();
lcd_init();
lcd_goto(1);
lcd_puts("hello guna");
adc_init();

 
while(1)
{
adc_channel(1);
IR = adc_result();
lcd_goto(21);
lcd_putn(IR);
lcd_goto(21);
lcd_puts("      ");

if(IR <= 200)
{

MOTOR    = ON;
BUZZER   = OFF;
RF_GREEN = OFF; // turn on Green led
RF_RED   = ON ; // turns off red led

}
else 
{

MOTOR    = OFF;
BUZZER   = ON;
RF_GREEN = ON; // turn off Green led
RF_RED   = OFF ; // turns on red led

}
}
}
