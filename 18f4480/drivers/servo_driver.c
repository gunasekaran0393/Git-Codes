//#include<p18fcxxx.h>
#include "delay.h"

//#pragma config OSC = IRCIO7
//#pragma config WDT = OFF
//#pragma config MCLRE = ON 

void servo_init(void);
void servo_angle(int);

/*void main()
{
	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	//OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)

servo_init();

while(1)
{
//LATDbits.LATD0 = 1;
//DelayUs(600);
//LATDbits.LATD0 = 0;
//DelayUs(600);
 servo_angle(10);
}
	
}
*/
void servo_init()
{
TRISBbits.TRISB0 = 0;
LATBbits.LATB0 = 0;
}
void servo_angle(int x)
{
int y;
if(x == 0)
{
y = 600;
LATBbits.LATB0 = 1;
DelayUs(y);
LATBbits.LATB0 = 0;
DelayMs(20);

}
else if(x>0)
{
y = (x*10)+600;

LATBbits.LATB0 = 1;
DelayUs(y);
LATBbits.LATB0 = 0;
DelayMs(20);
}
}

