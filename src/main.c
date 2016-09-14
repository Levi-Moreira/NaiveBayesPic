#define _XTAL_FREQ 20000000
#include <xc.h>
#include <math.h>
#include <stdio.h>
#include "../include/extra.h"
#include "../include/defines.h"

// BEGIN CONFIG
#pragma config FOSC     = HS    /// EXTERN CLOCK 8MHZ
#pragma config IESO     = OFF   /// INTERNAL/EXTERNAL OSCILATOR DISABLE
#pragma config PWRT     = OFF   /// DISABLE POWER-UP TIMER
#pragma config BORV     = 3     /// BROWN-OUT RESET MINIMUM
#pragma config WDT      = OFF   /// DISABLE WATCHDOG TIMER
#pragma config WDTPS    = 32768 /// WATCHDOG TIMER 32768s
#pragma config MCLRE    = OFF   /// MASTER CLEAR PIN (RE3) DISBALE
#pragma config LPT1OSC  = OFF   /// TIMER1 LOW POWER OPERATION
#pragma config PBADEN   = OFF   /// PORTB.RB0,1,2,3,4 AS I/O DIGITAL
#pragma config STVREN   = ON    /// STACK FULL/UNDERFLOW CAUSE RESET
#pragma config LVP      = OFF   /// DISABLE LOW VOLTAGE PROGRAM (ICSP DISABLE)*/
//END CONFIG

#define STRLEN 4

volatile unsigned char t;
volatile unsigned char rcindex = 0;
volatile unsigned long int res = 0;
volatile unsigned long int  result = 0;


void interrupt ISR(void)
{
    
    if (PIR1bits.RCIF)  // check if receive interrupt has fired
    {
        
        printf("%c", RCREG);
        
        t = RCREG;      // read received character to buffer

        if ( (t != '\n') && (rcindex < STRLEN) )
        {
            result = t;
            result <<= (3-rcindex)*8;
            res |= result;

            rcindex++;          // increment string index

        }
        else
        {
            rcindex = 0;        // reset string index
            printf("%lu",res);
        }

        PIR1bits.RCIF = 0;      // reset receive interrupt flag
    }
}

void main() {
    
    init_uart();
//    init_adc();
    
    printf("Init complete!\n");
    
    INTCONbits.PEIE = 1;    // enable peripheral interrupts
    INTCONbits.GIE = 1;     // enable interrupts
    
//    printf("\nRunning Naive Bayes in Dataset: mfeat\n\n");

    /* Calculates Recall and Precision for classes */
//    calculateMetrics();

    /* Print confusion matrix for the model */
//    printConfusionMatrix();

    /* Show the metrics for the model */
//    printMetrics();

    /* Show off the prediction skills */
//    showOff(randomNumber());
    
    while(1) {
    }
}