#include<pic18f4480.h>                                                // Include Header for PIC18f455

       /* ******COMPILER DIRECTIVES FOR CHIP CONFIGURATION BITS ***   */
//#pragma config PLLDIV = 5 , CPUDIV = OSC1_PLL2 , USBDIV = 2    // You can write this way
// OR
#pragma config OSC = IRCIO67

//#pragma config IESO = OFF                                 // OR this way

//#pragma config PWRT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = OFF

/*  ***************  TIMER *************** */
       void delayzz(void)
        {              int i, j;
                        for(i=0;i<100;i++)
                {
                          for(j=0;j<2;j++)
                      {           /* Well its Just a Timer */            }    }   }


                /* ****************** MAIN ****************** */

      void main(void)
         {
                        ADCON1 = 0x08;
                        TRISA = 0 ;                  
                        TRISB = 1;
                        LATA = 0;
                        //INTCON2bits.RBPU =0;
                        INTCONbits.GIE = 1;
                        //INTCONbits.PEIE =1;
                        INTCONbits.INT0IE =1;
                        INTCONbits.INT0IF = 0;
                        INTCON2bits.RBPU=0;

                        //INTCON2bits.RBIP=1;

                        //RCONbits.IPEN = 0;
                        //LATAbits.LATA5 = 0;
                        PORTAbits.RA5 = 0;
           while(1)
                            {
               //if(PORTBbits.RB0==1)
               
                                  LATAbits.LATA5 = 1;
                                // PORTAbits.RA5 = 1;
                                  delayzz();
                                  LATAbits.LATA5 = 0;
                                   delayzz();
                                   if(INTCONbits.INT0IF == 1)
                                   {
                                       PORTAbits.RA3 = 1;
                                   }
           }
        }

/* THE END */

void interrupt ISR()
{
   if(INTCONbits.INT0IF)
   {
       //LATAbits.LATA5 = 0;
     // PORTAbits.RA5 = 0;
       //delayzz();
       //INTCONbits.RBIF = 0;
       
       PORTAbits.RA4 =~PORTAbits.RA4 ;
      LATAbits.LATA5 = ~LATAbits.LATA5;
      INTCONbits.INT0IF = 0;

   }
   return;
   //INTCONbits.INT0IF = 0;
}