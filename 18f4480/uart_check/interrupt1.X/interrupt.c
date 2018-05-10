/* 
 * File:   interrupt.c
 * Author: Guna
 *
 * Created on July 25, 2015, 6:09 PM
 */
//#define _XTAL_FREQ 8000000
#include<pic18f45j11.h>
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


#define GREEN_LED PORTDbits.RD7
#define RED_LED   PORTDbits.RD6
#define ON 1
#define OFF 0

int main(int argc, char** argv)
{
	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)


		TRISAbits.TRISA5 = 0;
		PORTAbits.RA5	= OFF;
		TRISDbits.TRISD7 = 0;
		TRISDbits.TRISD6 = 0;
		TRISDbits.TRISD5 = 0;
		TRISB0              = 1;
		

		GREEN_LED		 =	OFF;
		RED_LED			 = 	OFF;

		INTCONbits.GIE          =   1;
		INTCONbits.PEIE         =   1;
		INTCON2bits.RBPU        =   0;
		INTCONbits.RBIE         =   1;
		INTCONbits.RBIF         =   0;
		INTCON2bits.RBIP        =   1;
		TRISD	=	0x00;
		PORTD 	= 	0x00;
		TRISB 	= 	0xFF;
		TRISAbits.TRISA5 = 0;

				while(1)
		{
		/*GREEN_LED = ON;
		RED_LED   = OFF;


		DelayMs(500);
		DelayMs(500);

		GREEN_LED = OFF;
		RED_LED   = ON;

		DelayMs(500);
		DelayMs(500);
		*/
                  GREEN_LED	 =	ON;
                    RED_LED	= 	ON;
			PORTAbits.RA5= ON;
                        DelayMs(500);
                         DelayMs(500);
                         PORTAbits.RA5= OFF;
                          GREEN_LED	 =	OFF;
                    RED_LED	= 	OFF;
		}





 return (EXIT_SUCCESS);
}



#pragma code isr = 0x08 // Store the below code at address 0x08
#pragma interrupt isr  // let the compiler know that the function isr() is an interrupt handler

void isr(void) {

    //if (INT0IF) //If External Edge INT Interrupt
    {
        LATAbits.LATA5	= OFF;
        //INT0IF = 0; // clear the interrupt
    }
}
#pragma code

