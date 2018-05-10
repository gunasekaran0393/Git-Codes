
#include<p18f4480.h>

#include "adc_driver.c"
#include "pwm_driver.c"

#pragma config OSC = IRCIO7
#pragma config WDT = OFF
#pragma config MCLRE = ON 



	void main()
		{
			int i;
			pwm2_init();
			adc_init();
			
			while (1)
				{
			adc_channel(1);
			 i =adc_result();
			 i/=4;
			set_pwm1_dutycycle(i);
			set_pwm2_dutycycle(i);
	}
	}
		
