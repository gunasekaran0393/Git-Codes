
#include<p18f4480.h>
#include "delay.h"
#include "lcd_diver.c"
#include "adc_driver.c"
#include "uart_driver.c"


/*****************Configuration************************/
#pragma config OSC = IRCIO7
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON

void main()
{
	int x,y,z;
	unsigned char c;
	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)	
	
TRISBbits.TRISB0 = 0;//a0
TRISBbits.TRISB1 = 0;//a1
TRISBbits.TRISB2 = 0;//a2
TRISBbits.TRISB3 = 0;//play

LATBbits.LATB0 = 0;
LATBbits.LATB1 = 0;
LATBbits.LATB2 = 0;
LATBbits.LATB3 = 1;

adc_init();
uart_init(9600);

set_lcdport();
lcd_init();
lcd_clrscr();
lcd_goto_pos(1);
lcd_puts("Hand talk");

while(1)
{




//lcd_goto_pos(1);
//lcd_putn(x);
//
//lcd_goto_pos(10);
//lcd_putn(y);
//
//lcd_goto_pos(17);
//lcd_putn(z);
//
//DelayMs(500);
//uart_putc('a');
if(PIR1bits.RCIF)
	{
		uart_putc('a');
		c = uart_getc();
		if(c == 'a')
		{
		lcd_goto_pos(17);
		lcd_puts("Hello");
		lcd_puts("        ");
	
		}
		else if(c == 'c')
		{
	    lcd_goto_pos(17);
		lcd_puts("Hai");
		lcd_puts("        ");
		}
		else if(c == 's')
		{
		lcd_goto_pos(17);
		lcd_puts("How r u");
		lcd_puts("        ");
		}
		else if(c == 'o')
		{
		lcd_goto_pos(17);
		lcd_puts("Good morning");
		lcd_puts("        ");
		}
		else if(c == 'p')
		{
		lcd_goto_pos(17);
		lcd_puts("Fine");
		lcd_puts("        ");
		}
		else if(c == 'q')
		{
		lcd_goto_pos(17);
		lcd_puts("Where r u");
		lcd_puts("        ");
		}
	
		
		
	}
else
{	
	DelayMs(10);

adc_channel(0);
x=adc_result(); //290

DelayMs(10);

adc_channel(1);
y = adc_result(); //313
DelayMs(10);

adc_channel(2);
z = adc_result(); //295

//lcd_goto_pos(1);
//lcd_putn(x);
//
//lcd_goto_pos(10);
//lcd_putn(y);
//
//lcd_goto_pos(17);
//lcd_putn(z);
//
//DelayMs(500);
//uart_putc('a');

  if((x <200)&&(y >200)&&(z >200))
 {
 
 LATBbits.LATB0 = 1;
 LATBbits.LATB1 = 0;
 LATBbits.LATB2 = 0;
 DelayMs(10);
 LATBbits.LATB3 = 0;
 DelayMs(250);
 LATBbits.LATB3 = 1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 
 }
  else if((x > 200)&&(y<200)&&(z>200))
 {
 
 LATBbits.LATB0 = 0;
 LATBbits.LATB1 = 1;
 LATBbits.LATB2 = 0;
 DelayMs(10);
 LATBbits.LATB3 = 0;
 DelayMs(250);
 LATBbits.LATB3 = 1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 
 }
  else if((x > 200)&&(y >200)&&(z <200))
 {
 
 LATBbits.LATB0 = 1;
 LATBbits.LATB1 = 1;
 LATBbits.LATB2 = 0;
 DelayMs(10);
 LATBbits.LATB3 = 0;
 DelayMs(250);
 LATBbits.LATB3 = 1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 }
 else if((x < 200)&&(y < 200)&&(z > 200))
 {
 
 LATBbits.LATB0 = 0;
 LATBbits.LATB1 = 0;
 LATBbits.LATB2 = 1;
 DelayMs(10);
 LATBbits.LATB3 = 0;
 DelayMs(250);
 LATBbits.LATB3 = 1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 
 }
  else if((x < 200)&&(y < 200)&&(z < 200))
 {
 
 LATBbits.LATB0 = 1;
 LATBbits.LATB1 = 0;
 LATBbits.LATB2 = 1;
 DelayMs(10);
 LATBbits.LATB3 = 0;
 DelayMs(250);
 LATBbits.LATB3 = 1;
 
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 }
else
{
 LATBbits.LATB0 = 0;
 LATBbits.LATB1 = 0;
 LATBbits.LATB2 = 0;
}
}
}
}
