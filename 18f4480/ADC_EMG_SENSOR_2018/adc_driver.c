/*----------------------------*/

#include <p18cxxx.h>
#include "delay.h"

/*----------------------------*/

void adc_init(void);
void adc_channel(unsigned char);
unsigned int adc_result(void);

unsigned char adc_result_8(void);
/*----------------------------*/

//void main(){}

/*----------------------------*/

void adc_init(void){

//	PORTCbits.RC1 = 0;	
//	TRISCbits.TRISC1 = 0;
//	TRISCbits.TRISC2 = 1;
	
	TRISA = 0xF;					// RA<3:0> are analog inputs
	ADCON2 = 0b10111101;							// AN<3:0> are analog
	//ANCON1 = 0b00010111;			// Vbg is turned off	
	ADCON1 = 0b00000000;			// 16 TOSC, 20 TAD, right justified 
}
/*----------------------------*/

void adc_channel(unsigned char ch){	
	DelayUs(100);
	ADCON0 = ch << 2;			//channel AN0 to AN3
	ADCON0bits.ADON = 1;		//enable ADC
}
/*----------------------------*/

unsigned int adc_result(void){

	ADRESH = ADRESL = 0;				// Clears AD result register 
	ADCON0bits.GO_DONE = 1;				// Automatic acquisition and starts conversion 	
	while(ADCON0bits.GO_DONE);			// Wait conversion to complete
	return (((unsigned int)ADRESH)<<8)|(ADRESL);	
}
/*----------------------------*/

unsigned char adc_result_8(void){

	ADRESH = ADRESL = 0;				// Clears AD result register 
	ADCON0bits.GO_DONE = 1;				// Automatic acquisition and starts conversion 	
	while(ADCON0bits.GO_DONE);			// Wait conversion to complete
	return(ADRESL);	
}




