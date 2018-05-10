#include<p18f4480.h>
#include"lcd_driver.c"


/*------------------------------------------*/
#pragma config OSC = IRCIO67
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON
/*--------------------------------------------------*/
#define CLEAR		0	
#define SET			1
#define NACK		1
#define ACK			0

#define SCL_DIR 	TRISCbits.TRISC3
#define SDA_DIR 	TRISCbits.TRISC4

#define SMP_DISABLE 0x80
#define SMP_ENABLE 	0x00	
#define SEN_DISABLE 0x00
#define I2C_MASTER_MODE 0x28

#define wait_mssp()		while(!PIR1bits.SSPIF);	PIR1bits.SSPIF = CLEAR	
	

#define SLAVE_WR(val)	((val << 1) + 0)	
#define SLAVE_RD(val)   ((val << 1) + 1)	
	
	
#define CHECK_ADDRESS 0x71
/*--------------------------------------------*/

void i2c_master_init(void);
void i2c_byte_write(unsigned char i2c_byte);
unsigned char i2c_byte_read(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_nack(void);
void i2c_ack(void);
void i2c_repeated_start(void);

/*--------------------------------------------*/

void delay(void)
{
int i,j;
for(i=0;i<=100;i++)
{
for(i=0;i<=1000;i++);
}
}
void main()
{
	unsigned char rx = 0;
	
	set_lcdport();
	lcd_init();
	lcd_goto(1);
	lcd_puts("I2C check");
	i2c_master_init();
	i2c_start();
	i2c_byte_write(0x70);
	i2c_byte_write(0xAA);
	i2c_stop();
	while(1)
	{
	i2c_start();
	i2c_byte_write(0x70);
	i2c_byte_write(0xAA);
	i2c_stop();
	delay();
	
	i2c_start();
	i2c_byte_write(0x70);
	i2c_byte_write(0x55);
	i2c_stop();
	delay();
//	i2c_start();
//	i2c_byte_write(0x90);
//	rx = i2c_byte_read();
//	i2c_ack();
//	i2c_stop();
//	lcd_goto(21);
//	lcd_putn(rx);
//	delay();
//	
	}
	
}

/*--------------------------------------------*/

void i2c_byte_write(unsigned char i2c_byte)
	{
	SSPBUF = i2c_byte;
	wait_mssp();
	
}
/*--------------------------------------------*/

unsigned char i2c_byte_read(void){	
	SSPCON2bits.RCEN = SET; 						
	wait_mssp();
	return SSPBUF;
}
/*--------------------------------------------*/

void i2c_start(void){
	SSPCON2bits.SEN = SET;		
	wait_mssp();
}
/*--------------------------------------------*/

void i2c_stop(void){
	SSPCON2bits.PEN = SET;	
	wait_mssp();	

}
/*--------------------------------------------*/

void i2c_nack(void){
	SSPCON2bits.ACKDT = NACK;
	SSPCON2bits.ACKEN = SET;

	wait_mssp();
}
/*--------------------------------------------*/

void i2c_ack(void){
	SSPCON2bits.ACKDT = ACK;
	SSPCON2bits.ACKEN = SET;

	wait_mssp();
}
/*--------------------------------------------*/

void i2c_repeated_start(void){
	SSPCON2bits.RSEN = SET;
	 
	wait_mssp();
}
/*--------------------------------------------*/

void i2c_master_init(void){
	SCL_DIR  = 1;	
	SDA_DIR  = 1;
	SSPCON1 = I2C_MASTER_MODE;					// Mode Select	
	SSPSTAT = SMP_DISABLE;						// Slew Rate Control 
	SSPADD  = 0x27;							// SCL Baud -> 100 Khz
}
/*--------------------------------------------*/
