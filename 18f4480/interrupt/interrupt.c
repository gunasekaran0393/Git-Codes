#include<p18f4480.h>
#include <portb.h>

//#pragma config OSC = IRCIO67
//#pragma config WDT = OFF


#define LED3 PORTBbits.RB3 //output RB3
//#define BP PORTBbits.RB0 //interruption RBO input

unsigned char etat_led;
unsigned char flagIT_RB0;
static int ledstatut=0;

//declare fonction
void ISR(void);
void init(void);
void EnableHighInterrupts (void);

void init(void)
{ 
TRISBbits.TRISB0=1; // PORT RB0 Input
TRISBbits.TRISB3=0; //PORT RB3 Output
LATBbits.LATB3=0; //output
}

#pragma code HIGH_INTERRUPT_VECTOR = 0x08 // set address 0x08
void HighVector (void)
{
_asm // assembly code 
goto ISR // create vector to High interrupt service routine
_endasm // end asm code
}

#pragma code // return to the code section
#pragma interrupt ISR // tells compiler to add correct return instruction 

void ISR(void)
{ 
// clear external interrupt flag
//if (INTCONbits.INT0IF==1) //RB0 input

// flagIT_RB0=1; 
// LATBbits.LATB3=!LATBbits.LATB3;

if (INTCONbits.RBIF)
{
PORTC = PORTB;
INTCONbits.RBIF = 0;
}
INTCONbits.INT0IF = 0; 
if ( ledstatut = 0) 
{
LED3 = 1;
ledstatut = 1;
}
/* -fm - nous avons qu'une état possible */
else if (ledstatut == 1)
{
LED3=0;
ledstatut = 0;
}

INTCONbits.RBIF=0; 
}

void EnableHighInterrupts (void) // Initialisation - Enable interrupt code
{
RCONbits.IPEN = 0; // enable interrupts (RCON bit 7)
INTCONbits.GIEH = 1; // enable global interrupt
INTCONbits.GIEL=1;
INTCONbits.INT0IE=1; // push button
INTCON2bits.INTEDG0=0; //choix du front
INTCONbits.INT0IF=0; 
ADCON1=ADCON1| 0x0F;
}

void main (void)
{
init();
EnableHighInterrupts();

TRISB=0;
LED3=0;

for(;;)
{
if (INTCONbits.INT0IF==1) //RB0 input
//INTCONbits.INT0IF = 0;
{ 
//LED3=!LED3;
LATBbits.LATB3=!LATBbits.LATB3;
flagIT_RB0=0 ;
}

}

}
