#include<p18f4480.h>                                                // Include Header for PIC18f455

       /* ******COMPILER DIRECTIVES FOR CHIP CONFIGURATION BITS ***   */
//#pragma config PLLDIV = 5 , CPUDIV = OSC1_PLL2 , USBDIV = 2    // You can write this way
// OR
#pragma config OSC = IRCIO7

//#pragma config IESO = OFF                                 // OR this way

//#pragma config PWRT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = OFF

/*  ***************  TIMER *************** */
       void delayzz(void)
        {              int i, j;
                        for(i=0;i<500;i++)
                {
                          for(j=0;j<2;j++)
                      {           /* Well its Just a Timer */            }    }   }


                /* ****************** MAIN ****************** */

      void main(void)
         {
                        TRISA = 0 ;                  // PORT B Setting: Set all the pins in port B to Output.

           while(1)
                            {
                                LATAbits.LATA5 = 1;   // RB-1 to High
                                //LATAbits.LATA1 = 1;   // RB-1 to High

                                 delayzz();

                                LATAbits.LATA5 = 0;    // RB-0 to LOW
                                //LATBbits.LATB1 = 0;    // RB-0 to LOW

                                 delayzz();

                              }
        }

/* THE END */

 
