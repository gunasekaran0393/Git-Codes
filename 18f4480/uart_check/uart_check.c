/*---------------------------------------------------------------------------------
*
*								 UART DRIVER 
*
*	MCU		: 	PIC18F4480
*---------------------------------------------------------------------------------*/

#include <p18f4480.h>
#include "uart_driver.c"
#include "delay.h"
#include "lcd_driver.c"
#pragma config OSC = IRCIO7 , WDT = OFF,BOREN = OFF ,MCLRE = ON ,XINST = OFF



void uart_puts(static const rom char *);
void uart_put_array(char *);
void uart_putn(unsigned int);
void uart_putc(unsigned char);
void uart_init(unsigned int baud);
unsigned char uart_getc(void);
unsigned char uart_gets(int );
/*----------------------------*/

#ifndef DIG_MAX
#define DIG_MAX 6
#endif


#define UART_RCIF		PIR1bits.RCIF

/*----------------------------*/


//void main(){}


/*----------------------------*/
//unsigned char c;
unsigned int i=0;
unsigned char data[];
char *dat=&data[0];
void main(void) {

	
				
	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)
	
	
	
	DelayMs(10);
	
	uart_init(416);
	
	set_lcdport();
	lcd_init();
	lcd_clrscr();
	lcd_goto(1);
	lcd_puts("hello");
	uart_puts("hello");


	while(1) 
		{
				uart_puts("LAT:12.87,LON80.09");
				uart_putc('\r');
				DelayMs(250);
//			if(PIR1bits.RCIF)
//			{
//				getsUSART(dat,10);
//			
//			}
	
	
		}
}

/*----------------------------*/


void uart_init(unsigned int baud) { 	

	
	TRISCbits.TRISC7 = 1;				//UART Rx
	TRISCbits.TRISC6 = 0;				//UART Tx	
//	baud = ((FOSC1/ baud )/64) – 1;
	SPBRG = baud;						//LOW_BYTE(baud);	
	SPBRGH = baud >> 8;					//HIGH_BYTE(baud);	

	TXSTA = 0b00100100;					// TX9=0, TXEN=1, SYNC=0, SENDB=0, BRGH=1
	RCSTA = 0b10010000;					// SPEN=1, RX9=0, CREN=1 
	BAUDCON = 0x08;						// ABDEN=0, WUE=0, BRG16=1
}

/*----------------------------*/

void uart_puts(static const rom char *p){
	 while(*p != '\0'){
	    uart_putc(*p);	
    	p++;     
	 }	
}
/*----------------------------*/

void uart_put_array(char *pt){
	 while(*pt != '\0'){
	    uart_putc(*pt);
    	pt++;     
	 }	
}
/*----------------------------*/

void uart_putn(unsigned int n){
    unsigned int no;
	unsigned char dig=1;
	char array[DIG_MAX];
	
	if(n)
		for(no=n; no/=10; dig++);		
	array[dig] = '\0';			
	do{		
		array[--dig] = (n%10) + 48;			
	}while(n/=10);	

	uart_put_array(array);  
}
/*----------------------------*/


void uart_putc(unsigned char data){
	while(!PIR1bits.TXIF);		// set when register is empty
	TXREG = data;
}
/*----------------------------*/

unsigned char uart_getc(void){

	if(RCSTAbits.OERR){			// Clear overrun error	
		RCSTAbits.CREN = 0;		// Resetting the receive logic
		DelayUs(100);
		RCSTAbits.CREN = 1;
	}
	
	while(!PIR1bits.RCIF);		// Wait...
	return RCREG;
}
/*----------------------------*/
unsigned char uart_gets(int x)
{
	if(PIR1bits.RCIF == 1)
	{
	if(i<x)
	{
		data[i] = ReadUSART();
		if(data[i]==0X0D)
		{
		putsUSART(data);
		for(;i>0;i--)
		{
			data[i]=0X00;
			i = 0;
		}
		i++;
		PIR1bits.RCIF = 0;
		}
	}
	}
return data;
}
