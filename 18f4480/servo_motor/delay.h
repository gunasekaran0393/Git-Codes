#ifndef __MY_DELAY_H
#define __MY_DELAY_H

//#include <p18cxxx.h>
#include <delays.h>

#define FOSC 4

//	For accurate delays in Ms and Us see "delays.h" file.

#if FOSC == 16
	#define DelayMs(msec) 	Delay10KTCYx(msec/5 << 1)	//input values -> 5,10,15...625
	#define DelayUs(usec)	Delay10TCYx(usec/5 << 1)	//input values -> 5,10,15...625
#elif FOSC == 4
	#define DelayMs(msec)	Delay1KTCYx(msec)			//input values -> 1,2,3...250
	#define DelayUs(usec)	Delay10TCYx(usec/10)		//input values -> 10,20,30...2500
#endif

#endif




