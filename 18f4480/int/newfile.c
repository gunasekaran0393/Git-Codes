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
                        TRISAbits.RA5 = 0 ;

                        /*
                        INTCONbits.RBIE = 1;
                        INTCONbits.RBIF = 0;
                        INTCONbits.GIE	  = 1;
                        //INTCONbits.PEIE = 1;

                        INTCON2bits.RBIP = 1;
                        RCONbits.IPEN = 0;*/
                       // LATAbits.LATA5 = 0;
           while(1)
                            {
                                 //LATAbits.LATA5 = 1;
                               PORTAbits.RA5 = 1;   // RB-1 to High
                                //LATAbits.LATA1 = 1;   // RB-1 to High

                                delayzz();
                                PORTAbits.RA5 = 0;
                              // LATAbits.LATA5 = 0;    // RB-0 to LOW
                                //LATBbits.LATB1 = 0;    // RB-0 to LOW

                                 delayzz();

                              }
        }

/* THE END */


    /*  void interrupt my_isr(void)
      {
          if(INTCONbits.RBIF == 1)
          {
             LATAbits.LATA5 = 0;

          }
          return;
      }
*/
