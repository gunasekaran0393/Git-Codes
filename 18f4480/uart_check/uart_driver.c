/*---------------------------------------------------------------------------------
*
*								 UART DRIVER 
*
*	MCU		: 	PIC18F4480
*---------------------------------------------------------------------------------*/

#include <p18cxxx.h>

/*----------------------------------------------*/

void uart_puts(static const rom char *);
void uart_putstring(static const  char *data);
void uart_put_array(char *);
void uart_putn(unsigned int);
void uart_putc(unsigned char);
void uart_putc1(char data);
void uart_init(unsigned int baud);
unsigned char uart_getc(void);
void uart_getstring( char *, unsigned char len);

/*-------------------------------------------------*/

#ifndef DIG_MAX
#define DIG_MAX 6
#endif

/*----------------------------------------------------*/
/*void main(void) 
	{

	unsigned char c;
	unsigned char data[100]="hai";
	DelayMs(50);
	
	uart_init(9600);
	uart_puts("hello");
	//uart_putc('\r');
	uart_putstring(data);

	//while(1) 
		{
		//uart_getstring(data,10);
		//uart_putstring(data);
			
		}while(1) ;
}

/*-----------------------------------------------------------*/


void uart_init(unsigned int baud) { 	

		unsigned int fosc =16;
	TRISCbits.TRISC7 = 1;				//UART Rx
	TRISCbits.TRISC6 = 0;				//UART Tx	
	baud = (unsigned float)(baud/100);
	baud= (fosc*2502 )/(baud)- 1;
	SPBRG = baud;						//LOW_BYTE(baud);	
	SPBRGH = baud >> 8;					//HIGH_BYTE(baud);	

	TXSTA = 0b00100100;					// TX9=0, TXEN=1, SYNC=0, SENDB=0, BRGH=1
	RCSTA = 0b10010000;					// SPEN=1, RX9=0, CREN=1 
	BAUDCON = 0x08;						// ABDEN=0, WUE=0, BRG16=1
}

/*----------------------------*/

void uart_puts(static const rom char *p){
	 while(*p != '\0'){
		//uart_putc('\t');
	    uart_putc(*p);	
    	p++;     
	 }
	 
	 uart_putc('\r');	
}
/*----------------------------*/


/*--------------------------------------------------*/
void uart_putstring(static const  char *data)
{
  do
  {  // Transmit a byte
    while(!TXSTAbits.TRMT);
    uart_putc1('\t');
    uart_putc1(*data);
    if(data == '\0') break;
  } while( *data++ );
  uart_putc('\t');
  uart_putc('\r');
}
/*---------------------------------------------*/

void uart_put_array(char *pt){
	 while(*pt != '\0'){
	    uart_putc(*pt);
    	pt++;     
	 }	
}
/*----------------------------*/

void uart_putn(unsigned int n){
    unsigned int no;
	unsigned char dig=1;
	char array[DIG_MAX];
	
	if(n)
		for(no=n; no/=10; dig++);		
	array[dig] = '\0';			
	do{		
		array[--dig] = (n%10) + 48;			
	}while(n/=10);	

	uart_put_array(array);  
}
/*----------------------------*/


void uart_putc(unsigned char data){
	while(!PIR1bits.TXIF);		// set when register is empty
	TXREG = data;
}
/*----------------------------*/

unsigned char uart_getc(void){

	if(RCSTAbits.OERR){			// Clear overrun error	
		RCSTAbits.CREN = 0;		// Resetting the receive logic
		
		RCSTAbits.CREN = 1;
	}
	
	while(!PIR1bits.RCIF);		// Wait...
	return RCREG;
}
/*----------------------------*/


void uart_getstring( char *buffer, unsigned char len)
{
  char i;    // Length counter
  unsigned char data;

  for(i=0;i<len;i++)  // Only retrieve len characters
  {
    while(!PIR1bits.RCIF);// Wait for data to be received

    data = uart_getc();    // Get a character from the USART
        if(data=='\0')
        {
        break;
        }                   // and save in the string
    *buffer = data;
     buffer++;              // Increment the string pointer
  }
}
/*-------------------------------------------------------*/
void uart_putc1(char data)
{
    TXREG = data;      // Write the data byte to the USART
}
/*---------------------------------------------*/
