#include<p18f4480.h>
#pragma config OSC = IRCIO7
#pragma config WDT = OFF
#pragma config MCLRE = ON 

void main()
{
TRISD = 0x00;
LATD = 0x00;
TRISCbits.RC2 = 0;
LATCbits.LATC2 = 0;
PR2=0XF0;
T2CON = 0b00000100 ;
  
  	 CCPR1L  = 0b00001100;
  	 CCP1CON = 0b01001100;
   
   	 ECCPR1L  = 0b00001100;
   	 ECCP1CON = 0b11111100;
   	 while(1);
    
}
