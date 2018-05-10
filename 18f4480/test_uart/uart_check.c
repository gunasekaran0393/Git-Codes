/*---------------------------------------------------------------------------------
*
*								 UART CHECK 
*
*	
*---------------------------------------------------------------------------------*/

#include <p18cxxx.h>
#include <string.h>
#include "delay.h"
#include "uart_driver.c"
#include "lcd_driver.c"

/*----------------------------*/


//#pragma config OSC=IRCIO67, WDT = OFF ,MCLRE =ON


/*----------------------------*/
unsigned char *data;
	unsigned char c;
void main(void) 
	{
	volatile int flag,rbuf;
	int i;
	unsigned char data[];
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
	INTCONbits.RBIE = 1;


	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)	
	TRISCbits.RC6 = 0;
	TRISCbits.RC7 = 1;
	TRISBbits.RB0 = 1;
		
	DelayMs(50);
	uart_init(9600);

	set_lcdport();
	lcd_init();
	lcd_goto(1);
	lcd_puts("UART_CHECK");
	uart_puts("UART_CHECK");
	
	while(1)
	{
		
		for(i=0;data[i]!='\0';i++)
		{
			
		data[i]=uart_getc();
			
		}
		//lcd_goto(21);
		//lcd_puts(data);
		uart_puts(data);
	}


}


