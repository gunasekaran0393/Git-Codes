#include <p18f4480.h>


//#pragma config OSC = IRCIO67
//#pragma config WDT = OFF

//----------------------------------------------------------------------------


void high_isr(void);

//-----------------------------------------------------------------------------
void main()
{
TRISBbits.RB7=1;
TRISDbits.RD0=0;

INTCON2bits.INTEDG0 = 0;
INTCONbits.RBIF = 1;
INTCONbits.RBIE = 1;
INTCONbits.RBIF = 0;
//INTCONbits.GIE	  = 1;
INTCONbits.GIEH = 1;

INTCON2bits.RBIP = 1;
RCONbits.IPEN = 1;

while(1)
{
//LATDbits.LATD0 = 1; 
}

}


/*#pragma interrupt high_isr
void high_isr(void)
{
if(INTCONbits.RBIF)
{
LATDbits.LATD0 = 0;
}
}*/

#pragma code high_vector = 0x08

void high_vector(void)

{
_asm

GOTO high_isr
_endasm

}
#pragma code

#pragma interrupt high_isr //save=PROD

void high_isr(void)
{

if(INTCONbits.RBIF)
{
	
	LATDbits.LATD0=~LATDbits.LATD0;
	INTCONbits.RBIF = 0;
	//INTCONbits.RBIE = 0;
}
}
