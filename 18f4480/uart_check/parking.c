#include <p18cxxx.h>

#include "delay.h"
#include "adc_driver.c"
#include "uart_driver.c"
#include "lcd_driver.c"

#pragma config OSC = IRCIO7 , WDT = OFF,BOREN = OFF ,MCLRE = ON ,XINST = OFF



#define BUZZER LATCbits.LATC0
#define BUZZER_GND LATCbits.LATC1
#define MOTOR  LATDbits.LATD6
#define MOTOR_GND LATDbits.LATD7


/*-------------------------------------*/

void compare(unsigned char data[]);


void main()
	{
int ir_1,ir_2,ir_3,ir_4,flag=1;

OSCCON = 0b01100000;		// 4 MHz internal oscillator
OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)	


	TRISC =0;
	TRISD =0;
	BUZZER = 0;
	BUZZER_GND=0;
	
	uart_init(9600);
	adc_init();


	
	DelayMs(100);
	lcd_init();
	lcd_clrscr();
	
	lcd_goto_pos(1);
	lcd_puts("Smart Parking");
	
	while(1)
	{
		//lcd_clrscr();
//		
//			adc_channel(0);
//			ir_1=adc_result();
//			DelayMs(2);
//			
//			adc_channel(1);
//			ir_2=adc_result();
//			DelayMs(2);
//			
//			adc_channel(2);
//			ir_3=adc_result();
//			DelayMs(2);
//			
//			adc_channel(3);
//			ir_4=adc_result();
//			DelayMs(2);
			
			
			
//			lcd_goto_pos(1);
//			lcd_putn(ir_1);
//			lcd_puts("    ");
//			
//			lcd_goto_pos(9);
//			lcd_putn(ir_2);
//			lcd_puts("    ");
//			
//			lcd_goto_pos(17);
//			lcd_putn(ir_3);
//			lcd_puts("    ");
//			
//			lcd_goto_pos(25);
//			lcd_putn(ir_4);
//			lcd_puts("    ");
			
			//DelayMs(250);//DelayMs(250);DelayMs(250);DelayMs(250);
			
			
		if(PIR1bits.RCIF==1)
		{
			PIR1bits.RCIF =0;
			flag =1;
			
			lcd_goto_pos(1);
			lcd_puts("LOT1:");
			
			lcd_goto_pos(9);
			lcd_puts("LOT2:");
			
			lcd_goto_pos(17);
			lcd_puts("LOT3:");
			
			lcd_goto_pos(25);
			lcd_puts("LOT4:");
			
		}
		else 
		flag=0;
		
		if(flag==1){
		
			//lcd_clrscr();
		
		
			
			adc_channel(0);
			ir_1=adc_result();
			DelayMs(2);
			
			adc_channel(1);
			ir_2=adc_result();
			DelayMs(2);
			
			adc_channel(2);
			ir_3=adc_result();
			DelayMs(2);
			
			adc_channel(3);
			ir_4=adc_result();
			DelayMs(2);
			
			
			if(ir_1>700)
			{
			lcd_goto_pos(6);
			lcd_puts("A");
			lcd_puts(" ");
			
			}
			else 
			{
			lcd_goto_pos(6);
			lcd_puts("NA");
			lcd_puts(" ");
			
			}
			
			if(ir_2>700)
			{
			lcd_goto_pos(14);
			lcd_puts("A");
			lcd_puts(" ");
			
			}
			else 
			{
			lcd_goto_pos(14);
			lcd_puts("NA");
			lcd_puts(" ");
			}
			if(ir_3>700)
			{
			lcd_goto_pos(22);
			lcd_puts("A");
			lcd_puts(" ");
			
			}
			else 
			{
			lcd_goto_pos(22);
			lcd_puts("NA");
			lcd_puts(" ");
			}
			if(ir_4>700)
			{
			lcd_goto_pos(30);
			lcd_puts("A");
			lcd_puts(" ");
			
			}
			else 
			{
			lcd_goto_pos(30);
			lcd_puts("NA");
			lcd_puts(" ");
			}
			
			if((ir_1<700)&&(ir_2<700)&&(ir_3<700)&&(ir_4<700))
			{
			BUZZER=1;
			}
			else 
			BUZZER = 0;
			
			if((ir_1>700)||(ir_2>700)||(ir_3>700)||(ir_4>700))
			{
			MOTOR =1;
			MOTOR_GND =0;
			
			DelayMs(250);DelayMs(250);
			
			MOTOR =0;
			MOTOR_GND =0;
			
			DelayMs(250);DelayMs(250);
			DelayMs(250);DelayMs(250);
			DelayMs(250);DelayMs(250);
			DelayMs(250);DelayMs(250);
			
			MOTOR =0;
			MOTOR_GND =1;
			
			DelayMs(250);DelayMs(250);
			
			MOTOR =0;
			MOTOR_GND =0;
					
			}
			else 
			BUZZER = 0;
		//	flag=0;
	
			
		}
//		else 
//		{
//			
//		lcd_goto_pos(1);
//		lcd_puts("Smart Parking");
//		}
	}

	}
	
/*void compare(unsigned char data[])

{
int i,j,count=0;
for(i=0;i<4;i++)
{
	for(j=0;j<12;j++)

	{
		if(card[i][j]==data[j])
		{

			if((i==0)&&(j==11))
				{
					tag_1 = 1;
					//lcd_goto_pos(17);
					//lcd_puts("card_1");
				}
				
			else if((i==1)&&(j==11))
				{
					tag_2 = 1;
					//lcd_goto_pos(17);
					//lcd_puts("card_2");
					
				}
			else if((i==2)&&(j==11))
				{
					tag_3 = 1;
					//lcd_goto_pos(17);
				//	lcd_puts("card_3");

				}
			else if((i==3)&&(j==11))
				{
					tag_4 = 1;
				//	lcd_goto_pos(17);
				//	lcd_puts("card_4");
				
				}
	    
		
		}
		
	else
	{
					
					tag_1 = 0;
					tag_2 = 0;
					tag_3 = 0;
					tag_4 = 0;
					break;
				
	}

		
	}
	
	if(tag_1==1)
	{
	card_no=1;
	}
	else if(tag_2==1)
	{
	card_no=2;
	
	}
	else if(tag_3==1)
	{
	card_no=3;
	}
	else if(tag_4 ==1)
	{
	card_no=4;
	}
}


}
*/
