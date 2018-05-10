#include <p18f4480.h>
#include<Delays.h>


#pragma config OSC = IRCIO67
#pragma config WDT = OFF

//void myisr(void);
//----------------------------------------------------------------------------


//myvoid high_isr(void);

//-----------------------------------------------------------------------------
void main()
{
TRISBbits.RB0=1;
TRISAbits.RA5=0;


INTCONbits.RBIF = 1;
INTCONbits.RBIE = 1;
INTCONbits.RBIF = 0;
INTCONbits.GIEH	= 1;
INTCONbits.PEIE = 1;

INTCON2bits.RBIP = 1;
INTCON2bits.RBPU = 0;
RCONbits.IPEN = 0;
LATAbits.LATA5 = 0;

while(1)
{

if(INTCONbits.INT0IF)
{

INTCONbits.INT0IF =0;
LATAbits.LATA5 = 0;

}
else
{
LATAbits.LATA5 = 1;
}
}

}






/*void interrupt myisr(void)
{

if(INTCONbits.RBIF ==1)
{
	
	LATAbits.LATA5=~LATAbits.LATA5;
	INTCONbits.RBIF = 0;
        //Delay1KTCYx(10);
       // break;
       return ;
}
       

if (PORTB) {
        asm("nop");
    }
    
}
*/
