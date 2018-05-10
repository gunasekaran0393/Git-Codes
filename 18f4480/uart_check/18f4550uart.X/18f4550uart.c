/* 
 * File:   18f4550uart.c
 * Author: Guna
 *
 * Created on July 25, 2015, 1:58 PM
 */
#define _XTAL_FREQ 8000000 //The speed of your internal(or)external oscillator
#define USE_AND_MASKS


#include<p18f45j11.h>
#include <usart.h>


unsigned char UART1Config = 0, baud = 0;
unsigned char MsgFromPIC[] = "\r\nYou typed :";
unsigned char MessageBuffer[200];

int i=0;
void SetupClock(void);
void Delay1Second(void);

void main(int argc, char** argv) {

    SetupClock(); // Internal Clock to 8MHz

    TRISCbits.RC6 = 0; //TX pin set as output
    TRISCbits.RC7 = 1; //RX pin set as input

    UART1Config = USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_HIGH ;
    baud = 51;
    OpenUSART(UART1Config,baud);

    //Compare with the table above

    PIR1bits.RCIF = 0; //reset RX pin flag
    RCIP = 0; //Not high priority
    RCIE = 1; //Enable RX interrupt
    PEIE = 1; //Enable pheripheral interrupt (serial port is a pheripheral)

    ei();       //remember the master switch for interrupt?

    while(1) //infinite loop
    {
	void  SerialRxPinInterrupt();
    }
}

void SetupClock()
{
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;




    OSCCONbits.IRCF2 = 1;
}

void  SerialRxPinInterrupt()
{
    //check if the interrupt is caused by RX pin
    if(PIR1bits.RCIF == 1)
    {
        if(i<200) //our buffer size
        {
            MessageBuffer[i] = ReadUSART(); //read the byte from rx register
            if(MessageBuffer[i] == 0x0D) //check for return key
            {
                putsUSART(MessageBuffer);
                for(;i>0;i--)
                    MessageBuffer[i] = 0x00; //clear the array
                i=0; //for sanity
                return;
            }
            i++;
            PIR1bits.RCIF = 0; // clear rx flag
        }
        else
        {
             putsUSART(MessageBuffer);
             for(;i>0;i--)
                    MessageBuffer[i] = 0x00; //clear the array
             i=0; //for sanity
             return;
        }
    }
}
