/*---------------------------------------------------------------------------------
*
*								 UART DRIVER 
*
*
*---------------------------------------------------------------------------------*/

#include <p18cxxx.h>
#include "delay.h"
#include "lcd_driver.c"

#pragma config OSC = IRCIO67 , WDT = OFF,BOREN = OFF ,MCLRE = ON ,XINST = OFF

/*----------------------------*/
//#define FOSC 16000000
 
/*----------------------------*/

void uart_puts(static const rom char *);
void uart_put_array(char *);
void uart_putn(unsigned int);
void uart_putc(unsigned char);
void uart_init(unsigned int baud_rate);
unsigned char uart_getc();

/*----------------------------*/

#ifndef DIG_MAX
#define DIG_MAX 6
#endif

//#define unsigned int FOSC 16

#define UART_RCIF		PIR1bits.RCIF

/*----------------------------*/


//void main(){}


/*----------------------------*/

void main(void) {

	unsigned  char c;
	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)

	DelayMs(50);
	uart_init(9600);
	set_lcdport();
	lcd_init();
	lcd_goto(1);
	lcd_puts("hello");

	uart_puts("Hello");


	
	while(1)
	{
		c = uart_getc();
		uart_puts("guna ");
		uart_putc(c);
		lcd_goto(21);
		lcd_putc(c);
		//uart_putc('\0');		
	} 
}

/*----------------------------*/


void uart_init(unsigned int baud_rate) 
	{ 
	
	unsigned char fosc =16;
	
	TRISCbits.TRISC7 = 1;				//UART Rx
	TRISCbits.TRISC6 = 0;				//UART Tx	
	PIE1bits.RCIE =1;
	PIE1bits.TXIE =0;
	baud_rate = (unsigned float)(baud_rate/100);
	baud_rate= (fosc*2502 )/(baud_rate)- 1;	// Baud rate set to desired bits per second

	SPBRG = baud_rate;						//LOW_BYTE(baud);	
	SPBRGH = baud_rate >> 8;					//HIGH_BYTE(baud);	

	//TXSTA = 0b00100100;
	TXSTAbits.SYNC =0;
	TXSTAbits.TXEN =1;	
	TXSTAbits.TXEN =0;				// TX9=0, TXEN=1, SYNC=0, SENDB=0, BRGH=1
	TXSTAbits.BRGH =1;
	TXSTAbits.TX9=0;
	TXSTAbits.SENDB = 0;
	RCSTA = 0b10010000;					// SPEN=1, RX9=0, CREN=1 
	RCSTAbits.SPEN=1;
	RCSTAbits.RX9=0;
	RCSTAbits.CREN=1 ;
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

unsigned char uart_getc()
	{
	if(RCSTAbits.OERR)			// Clear overrun error
	{	
		RCSTAbits.CREN = 0;		// Resetting the receive logic
		DelayUs(100);
		RCSTAbits.CREN = 1;
	}
	
	if(!PIR1bits.RCIF);		// Wait...
	{
	
	
	return RCREG;
}
}
/*----------------------------*/


