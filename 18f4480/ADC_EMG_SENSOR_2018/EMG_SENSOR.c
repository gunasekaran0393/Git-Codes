
#include<p18f4480.h>
#include "delay.h"
#include "lcd_diver.c"
#include "adc_driver.c"
#include "uart_driver.c"
#include<String.h>

/*****************Configuration************************/
#pragma config OSC = IRCIO7
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON

#define NUMREADINGS 30 // raise this number to increase data smoothing
#define THRESHOLD 600

unsigned int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
unsigned int val = 0; // reading from probePin
unsigned int readings[NUMREADINGS];                // the readings from the analog input
unsigned int index = 0;                            // the index of the current reading
unsigned int total = 0;                            // the running total
unsigned int average = 0;                          // final average of the probe reading
unsigned int oldaverage = 0;                          // final average of the probe reading

void main()
{
	
 	int i=0;
	unsigned char c;
	char result[50];
    int num = 2300;

	OSCCON = 0b01100000;		// 4 MHz internal oscillator
	OSCTUNEbits.PLLEN = 1;		// PLL enabled (16 MHz)	
	
	TRISAbits.RA5=0;
	TRISDbits.RD2=0;
	
	adc_init();
	uart_init(9600);
    for (i = 0; i < NUMREADINGS; i++){
      readings[i] = 0;                      // initialize all the readings to 0
    }
	
	while(1)
	{
	
	  adc_channel(0);
	  val = adc_result(); 						// 10 bit ADC
	  if(val >= 1){                				// if the reading isn't zero, proceed
	
	    total -= readings[index];               // subtract the last reading
	    readings[index] = val; 					// read from the sensor
	    total += readings[index];               // add the reading to the total
	    index = (index + 1);                    // advance to the next index
	
	    if (index >= NUMREADINGS){              // if we're at the end of the array...
	      index = 0;                            // ...wrap around to the beginning
	    }  
	
	    average = total / NUMREADINGS;          // calculate the average
	    
	    if(average > THRESHOLD){
	      LATAbits.LATA5=~LATAbits.LATA5;
	      LATDbits.LATD2=~LATDbits.LATD2;
	      //uart_putc('i');
	    }
	   }
       	 itoa(average, result, 10);
    	 uart_put_array(result);
    	 uart_putc('\r');
    	 uart_putc('\n');
    	 Delay_ms(600);
////	   Serial.println(average); // use output to aid in calibrating
	   oldaverage = average;
	
	}
}
