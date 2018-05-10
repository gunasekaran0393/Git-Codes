/* 
 * File:   pwm_test.c
 * Author: Guna
 *
 * Created on July 20, 2015, 1:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <htc.h>
#include "pic18f4480.h"


#pragma config OSC = IRCIO7
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON

#define SYSTEM_CLOCK_FREQUENCY  4000000    /* 4 MHz */

#define _XTAL_FREQ  SYSTEM_CLOCK_FREQUENCY

/*
 * 
 */
int main(int argc, char** argv) {

TRISA = 0;

int i=0;

while(1)

{
    LATA = 0xFF;

    for(i=0; i<6000; i++);

    LATA = 0x00;

    for(i=0; i<6000; i++);

}
    return (EXIT_SUCCESS);
}

