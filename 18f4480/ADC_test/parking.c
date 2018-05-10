
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <htc.h>
#include "pic18f4480.h"
#include "delay.h"
#include "lcd_diver.c"
#include "adc_driver.c"
#include "uart_driver.c"


/*****************Configuration************************/
#pragma config OSC = IRCIO7
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON




#define BUZZER LATBbits.LATB0
#define BUZZER_GND LATBbits.LATB1
#define MOTOR  LATBbits.LATB2
#define MOTOR_GND LATBbits.LATB3



int main()
{
	int x,y,z;
	
	int ir_1,ir_2,ir_3,ir_4,flag=0,count =0;
	
	
	unsigned char c;
	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)	
	
	
	TRISB =0;
	
MOTOR =0;
MOTOR_GND =0;
adc_init();
uart_init(9600);

set_lcdport();
lcd_init();
lcd_clrscr();
lcd_goto_pos(1);
lcd_puts("Smart Parking");

while(1)
	{
		//lcd_clrscr();
		
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
//			
//			
//			
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
			flag =0;
			
		if(PIR1bits.RCIF)
		{
			PIR1bits.RCIF =0;
			flag =1;
			count++;
			
			lcd_goto_pos(1);
			lcd_puts("LOT1:");
			
			lcd_goto_pos(9);
			lcd_puts("LOT2:");
			
			lcd_goto_pos(17);
			lcd_puts("LOT3:");
			
			lcd_goto_pos(25);
			lcd_puts("LOT4:");
			
		}

		
		
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
			lcd_puts("  ");
			
			}
			else 
			{
			lcd_goto_pos(6);
			lcd_puts("NA");
			lcd_puts("  ");
			
			}
			
			if(ir_2>500)
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
			
			if((ir_1<700)&&(ir_2<650)&&(ir_3<700)&&(ir_4<700))
			{
			BUZZER=1;
			}
			else 
			BUZZER = 0;
			
			if(((ir_1>700)||(ir_2>650)||(ir_3>700)||(ir_4>700))&&(count==1))
			{
				lcd_goto(41);
				lcd_puts("Gate opening");
				
			MOTOR =1;
			MOTOR_GND =0;
			
			DelayMs(250);DelayMs(250);
			
			MOTOR =0;
			MOTOR_GND =0;
			
			DelayMs(250);DelayMs(250);
			DelayMs(250);DelayMs(250);
			DelayMs(250);DelayMs(250);
			DelayMs(250);DelayMs(250);
			
			lcd_goto(41);
				lcd_puts("Gate closing ");  
				
			MOTOR =0;
			MOTOR_GND =1;
			
			DelayMs(250);DelayMs(250);
			
			MOTOR =0;
			MOTOR_GND =0;
			DelayMs(250);DelayMs(250);
			DelayMs(250);
			DelayMs(250);
					lcd_goto(41);
				lcd_puts("               ");  
			}
			
	
			
		}
//		else 
//		{
//			
//		lcd_goto_pos(1);
//		lcd_puts("Smart Parking");
//		}*/
	}
   return (EXIT_SUCCESS);
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

 * re
}
*/
