#include<p18f4480.h>
#include<delays.h>
#include<sw_uart.h>
#include<usart.h>
/*************************************************/
#pragma config OSC = IRCIO7
#pragma config WDT = OFF
#pragma config MCLRE = ON 




void main(void)
{             
                unsigned char data[]="Hello World!";
                unsigned char readcode;
                unsigned char data1[100] ;
                
                //unsigned char int i = (((((2*FOSC)/(4*BAUD_RATE))+1)/2)-12);   
                                   
                OSCCON=0b01100000;
                OSCTUNEbits.PLLEN = 1;
    			ADCON1=0x0F;
    			
                OpenUART();
                putsUART(data);
                while(1)
                                {
	                               getsUART(data1,5) ;
                              //  readcode=ReadUART();
                                //putcUART(readcode);
                                putsUART(data1);
                                }
}             
 

/****************************************************************/
//  DelayTXBitUART     =((((2*FOSC)/(4*baud))+1)/2)-12 cycles
//                                                                   =((((2*4Mhz)/(4*4800))+1)/2)-12 cycles
//                                                                               =(((8Mhz/19200)+1)/2)-12 cycles
//                                                                               =((416.66+1)/2)-12 cycles
//                                                                               =(417.66/2)-12 cycles
//                                                                               =208.83-12 cycles
//                                                                               =196.83~197 cycles
/****************************************************************/
 
void DelayTXBitUART()
{
Delay10TCYx(40);
_asm NOP _endasm
_asm NOP _endasm
_asm NOP _endasm
_asm NOP _endasm
_asm NOP _endasm

}
 
/****************************************************************/
//  DelayRXHalfBitUART  =((((2*FOSC)/(8*baud))+1)/2)-9 cycles
//                                                                            =((((2*4Mhz)/(8*4800)+1)/2)-9 cycles
//                                                                                            =((8Mhz/38400)+1)/2)-9 cycles
//                                                                                            =(208.33+1)/2)-9 cycles
//                                                                                            =(209.33/2)-9 cycles
//                                                                                            =104.66-9 cycles
//                                                                                            =95.66~96 cycles
/****************************************************************/
void DelayRXHalfBitUART(void)
{
 
Delay10TCYx(20);

}
 
/****************************************************************/
//  DelayRXBitUART  =((((2*FOSC)/(4*baud))+1)/2)-14 cycles
//                                                                            =(((2*4Mhz)/(4*4800)+1)/2)-14 cycles
//                                                                            =208.83-14 cycles
//                                                                            =194.83~195 cycles
/****************************************************************/
 
void DelayRXBitUART(void)
{
Delay10TCYx(40);
_asm NOP _endasm
_asm NOP _endasm
_asm NOP _endasm


}
