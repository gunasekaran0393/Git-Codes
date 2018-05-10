/*---------------------------------------------------------------------------------
*
*								 UART DRIVER 
*
*	MCU		: 	PIC18F4480
*---------------------------------------------------------------------------------*/

#include <p18f4480.h>
#include "delay.h"

#pragma config OSC = IRCIO7 , WDT = OFF,BOREN = OFF ,MCLRE = ON ,XINST = OFF


#define OSC 16000000
#define BAUD_RATE 9600


void main(void) 
	{
	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)	
	DelayMs(50);
	TRISCbits.RC6= 0;
	TRISCbits.RC1= 1;
	SPBRG =25; //(((OSC/16)/BAUD_RATE) – 1);

	TXSTA = 0b00100100;	
	BAUDCON = 0x00;
	unsigned char data[10]="guna";

	while(!PIR1bits.TXIF);		
	TXREG = data;

		
	}




