#include <p18f4480.h>
#include <delays.h>
#include <portb.h>

#pragma config OSC = IRCIO67
#pragma config WDT = OFF

void InterruptServiceHigh(void);
void InterruptServiceLow(void);

int x;

void main(void)
{

INTCONbits.INT0IF = 0;
INTCONbits.INT0IE = 1;
INTCON2bits.INTEDG0 = 1;

INTCON2bits.RBPU = 0;//EnablePullups();
ADCON1bits.PCFG0 = 6;

TRISD = 0;
TRISBbits.TRISB0 = 1;
LATD =0;
RCONbits.IPEN = 1;
INTCONbits.GIE = 1;
INTCONbits.PEIE = 1;

while(1)	
{
//PORTE = 0x01;
}

}


// High priority interrupt vector

#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void)
{
_asm
goto InterruptServiceHigh
_endasm
}


// Low priority interrupt vector

#pragma code InterruptVectorLow = 0x18
void InterruptVectorLow(void)
{
_asm
goto InterruptServiceLow
_endasm
}



// Interrupt Service Routine

// Interrupt pragma for high priority

#pragma code
#pragma interrupt InterruptServiceHigh
void InterruptServiceHigh()
{
// function statements

if(INTCONbits.INT0IF)
{
LATD =1;
INTCONbits.INT0IF = 0;
}

// return from high priority interrupt

}


// Interrupt pragma for low priority

#pragma code
#pragma interrupt InterruptServiceLow
void InterruptServiceLow()
{
// function statements

// return from low priority interrupt

}
