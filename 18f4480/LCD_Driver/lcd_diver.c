// Program to interface 16x2 LCD with PIC18F44850 Microcontroller using 4-bit mode


#include<p18f4480.h>
/*****************Configuration************************/
#pragma config OSC = IRCIO7
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON

//LCD Control pins


#ifndef DIG_MAX
#define DIG_MAX 	6
#endif



#define rs LATDbits.LATD3
#define en LATDbits.LATD2

//LCD Data pins
#define lcdport LATD
////////////////////////////////////
void Delay_ms(int);
void lcd_init(void);
void dis_cmd(unsigned char);
void dis_data(unsigned char);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcd_puts(static const rom char *);
void lcd_putc(unsigned char);
void lcd_put_array(char *);
void lcd_putn(unsigned int );
void lcd_clrscr(void);
void lcd_goto_pos(unsigned char);
void lcd_goto(unsigned char );
//--------------------------------------------------------/
void main()
{

	TRISD=0;			// Configure Port B as output port
	LATD=0;
	
	lcd_init();				// LCD initialization
//	lcd_clrscr();
	
	while(1){
		lcd_goto(1);
	lcd_puts("hello world  ");
	}
}

//---------------------------------------------------------/
void lcd_init()	                    
{
	dis_cmd(0x02);		// To initialize LCD in 4-bit mode.
	dis_cmd(0x28);		// To initialize LCD in 2 lines, 5x7 dots and 4bit mode.
	dis_cmd(0x01);
	dis_cmd(0x17);
	dis_cmd(0x0C);
	dis_cmd(0x06);
	dis_cmd(0x83);
}
//---------------------------------------------------------/
void dis_cmd(unsigned char cmd_value)
{
	unsigned char cmd_value1;
	cmd_value1 = (cmd_value & 0xF0);	// Mask lower nibble because RB4-RB7 pins are being used
	lcdcmd(cmd_value1);			// Send to LCD
	cmd_value1 = ((cmd_value<<4) & 0xF0);	// Shift 4-bit and mask
	lcdcmd(cmd_value1);			// Send to LCD
}

//-----------------------------------------------------------------------/

void dis_data(unsigned char data_value)
{
	unsigned char data_value1;
	data_value1=(data_value&0xF0);
	lcddata(data_value1);
	data_value1=((data_value<<4)&0xF0);
	lcddata(data_value1);
}
//-----------------------------------------------------------------------/
void lcdcmd(unsigned char cmdout)
{
	lcdport=cmdout;		//Send command to lcdport=PORTB
	rs=0;						
	en=1;
	Delay_ms(10);
	en=0;
}
//---------------------------------------------------------------------/
void lcddata(unsigned char dataout)
{
	lcdport=dataout;	//Send data to lcdport=PORTB
	rs=1;
	en=1;
	Delay_ms(10);
	en=0;

}
//------------------------------------------------------------------------------/
//----------------------------------------------------------------------/

void Delay_ms(int x) 
{
int i,j;
for (i=0;i<=5;i++)
{
	for(j=0;j<x;j++);
}
}
//-------------------------------------------------------------------------------------/*/
void lcd_puts(static const rom char *p){
	
	 while(*p != '\0'){
	    dis_data(*p);	
    	p++;     
	 }	
}
void lcd_putc(unsigned char c)
	{
   dis_data(c);	
}
//------------------------------------------------------------------------------------------/

void lcd_putn(unsigned int n){
    unsigned int no;
	unsigned char dig=1;
	char array[DIG_MAX];	
	if(n)
		for(no=n; no/=10; dig++);		
	array[dig] = '\0';			
	do{		
		array[--dig] = (n%10) + 48;			
	}while(n/=10);	

	lcd_put_array(array);    
}
//--------------------------------------------------------------------------/
void lcd_put_array(char *pt){
	 while(*pt != '\0'){
	    dis_data(*pt);	
    	pt++;     
	 }	
}
void lcd_goto(unsigned char cnt)		//( 1 ... 80)
{
	if(cnt > 60)
		dis_cmd(0xD4+(cnt-61));
	else if(cnt > 40)
		dis_cmd(0x94+(cnt-41));
	else if(cnt >20)
		dis_cmd(0xC0+(cnt-21));
	else
		dis_cmd(0x80+(cnt-1));
}
/*-----------------------------------------------*/	

void lcd_goto_pos(unsigned char cnt){		//cnt = (1 ... 32) for 16*2 LCD
	if(cnt>16)
		dis_cmd(0xC0+(cnt-17));
	else
		dis_cmd(0x80+(cnt-1));
}	
void lcd_clrscr(void)
	{
	dis_cmd(0x01);
	dis_cmd(0x80);
	}