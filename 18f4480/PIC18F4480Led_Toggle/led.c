#include<p18f4480.h>
#include"adc_driver.c"


#pragma config OSC = IRCIO67

//#pragma config IESO = OFF                                 // OR this way

//#pragma config PWRT = OFF
//#pragma config LVP = OFF
//#pragma config BOREN = OFF
#pragma config WDT = OFF
//#pragma config MCLRE = ON


void delay(int);

int i,x;
 void main()
 {
	 
	 TRISBbits.RB0=0;
	 TRISAbits.RA5=0;
	 adc_init();
 	adc_channel(0);
 	while(1)
 	{
 	x = adc_result();
	
 
  LATAbits.LATA5=~LATAbits.LATA5;
  LATBbits.LATB0=~LATBbits.LATB0;
 
  	delay(x);
  }	
 }
 void delay(int y)
 {
for (i=0; i< y ;i++);	 
 }