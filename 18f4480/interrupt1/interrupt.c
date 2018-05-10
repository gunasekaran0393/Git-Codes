#include <p18f4480.h>


#pragma config OSC = IRCIO67
#pragma config WDT = OFF

//----------------------------------------------------------------------------


void InterruptServiceHigh(void);
void InterruptServiceLow(void);

void delay()
{
	int i,j;
for(i =0 ;i<100;i++)
{
for(j =0 ;j<100;j++);
}
}
//-----------------------------------------------------------------------------
void main()
{
TRISBbits.RB0 = 1;
TRISAbits.RA5 = 0;



INTCONbits.GIE = 1;
INTCONbits.INT0IE = 1;
INTCONbits.INT0IF = 0;
RCONbits.IPEN = 1;
ADCON1 = 6;
INTCON2bits.RBPU =0;
INTCON2bits.INTEDG0 = 0;

LATAbits.LATA5 = 0;


while(1)
{
	
if(INTCONbits.INT0IF)
{
LATAbits.LATA5 = 0; 
//delay();
//LATAbits.LATA5 = 1; 
INTCONbits.INT0IF = 0;

}
else
{
LATAbits.LATA5 = 1;
}

}

}





//#pragma code InterruptVectorHigh = 0x08
//void InterruptVectorHigh(void)
//{
//_asm
//goto InterruptServiceHigh
//_endasm
//}
//
//
//// Low priority interrupt vector
//
//#pragma code InterruptVectorLow = 0x18
//void InterruptVectorLow(void)
//{
//_asm
//goto InterruptServiceLow
//_endasm
//}
//
//
//
//
//
//#pragma code
//#pragma interrupt InterruptServiceHigh
//void InterruptServiceHigh()
//{
//if(INTCONbits.INT0IF)
//{
//
////LATDbits.LATD0 = ~LATDbits.LATD0;
//INTCONbits.INT0IF = 0;
//
//}
//
//// return from high priority interrupt
//
//}
//
//
//// Interrupt pragma for low priority
//
//#pragma code
//#pragma interrupt InterruptServiceLow
//void InterruptServiceLow()
//{
//// function statements
//
//// return from low priority interrupt
//
//}
//
