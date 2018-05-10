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


#define BUZZER    LATCbits.LATC0
#define LIGHT     LATCbits.LATC1


#define ON       1
#define OFF      0

void buzzer(int count)
{
for(;count!=0;)
{
BUZZER = ON;
DelayMs(100);
BUZZER = OFF;
DelayMs(100);
count--;
}
}
void main()
{
unsigned int obs,pir,gas,light;
TRISC = 0x00;
PORTC = 0x00;
set_lcdport();
lcd_init();
lcd_goto(1);
lcd_puts("Smoke Diving Helmet");
lcd_goto(21);
lcd_puts("OBJ:");
lcd_goto(32);
lcd_puts("GAS:");
lcd_goto(41);
lcd_puts("LIG:");
lcd_goto(52);
lcd_puts("PIR:");

adc_init();

 
while(1)
{
/*-----------------------------------------*/
adc_channel(0);
gas = adc_result();
lcd_goto(36);
lcd_putn(gas);
lcd_puts("   ");
/*-----------------------------------------*/
adc_channel(1);
light = adc_result();
lcd_goto(45);
lcd_putn(light);
lcd_puts("    ");
/*-------------------------------------------------*/
adc_channel(2);
obs = adc_result();
lcd_goto(25);
lcd_putn(obs);
lcd_puts("    ");
/*----------------------------------*/
adc_channel(3);
pir = adc_result();
lcd_goto(56);
lcd_putn(pir);
lcd_puts("      ");
/*-----------------------------------*/
if(gas >600)
{
buzzer(1);
}
else if(light < 600)
{
LIGHT = ON;
}
else if(obs > 600)
{
buzzer(2);
}
else if(pir > 600)
{
buzzer(3);
}
else 
{
LIGHT = OFF;
BUZZER = OFF;
}

}
}
