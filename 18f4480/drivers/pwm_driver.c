
#include<p18f4480.h>

//#include "adc_driver.c"


//#pragma config OSC = IRCIO7
//#pragma config WDT = OFF
//#pragma config MCLRE = ON 



void set_pwm1_dutycycle(unsigned int);
void set_pwm2_dutycycle(unsigned int);
void pwm1_init(void);
void pwm2_init(void);

		/*void main()
		{
			int i;
			pwm2_init();
			adc_init();
			
			while (1)
				{
			adc_channel(0);
			 i =adc_result();
			 i/=4;
			set_pwm1_dutycycle(i);
			set_pwm2_dutycycle(i);
	}
	}*/
		
			/*
		TRISD = 0x00;
		LATD = 0x00;
		TRISCbits.RC2 = 0;
		LATCbits.LATC2 = 0;
		PR2=0b1111011;
		T2CON = 0b00000111 ;
		  
		  	 CCPR1L  = 0b00001100;
		  	 CCP1CON = 0b01001100;
		   
		   	 ECCPR1L  = 0b00001100;
		   	 ECCP1CON = 0b11111100;
		   	 */
		   	
		    
		
		void pwm1_init()
		{
					TRISCbits.RC2 = 0;
					LATCbits.LATC2 = 0;
					PR2			=	0b11110110;
					T2CON 		= 	0b00000111;
					CCPR1L 		= 	0b00000000;
					CCP1CON 	= 	0b01001100;
		}
		void pwm2_init()
		{
					TRISCbits.RC2 = 0;
					LATCbits.LATC2 = 0;
					TRISDbits.RD5 =0;
					LATDbits.LATD5 = 0;
					PR2			= 0b11110110;
					T2CON 		= 0b00000111;
					CCPR1L 		= 0b00000000;
					CCP1CON 	= 0b01001100;
					ECCPR1L 	= 0b00000000;
					ECCP1CON	= 0b11111100;
		
		
		}
		
		void set_pwm1_dutycycle(unsigned int x)
		{
			CCPR1L = x;
		
		}
		void set_pwm2_dutycycle(unsigned int x)
		{
			ECCPR1L = x;
		
		}
