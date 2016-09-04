#define _XTAL_FREQ 20000000
#include <xc.h>
#include <plib/usart.h>
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
#pragma config LVP      = OFF   /// DISABLE LOW VOLTAGE PROGRAM (ICSP DISABLE)
//END CONFIG

unsigned char UART1Config = 0, baud = 0;

void putch(unsigned char data) {
    while( ! PIR1bits.TXIF)          // wait until the transmitter is ready
        continue;
    TXREG = data;                     // send one character
}

void init_uart(void) {
    TXSTAbits.TXEN = 1;               // enable transmitter
    RCSTAbits.SPEN = 1;               // enable serial port
    
    UART1Config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_HIGH ;
    baud = 129;
    OpenUSART(UART1Config,baud);

}

void main()
{
    init_uart();
    
    //srand(time(NULL));
    
    printf("\nRunning Naive Bayes in Dataset: mfeat\n\n");

    /* Calculates Recall and Precision for classes */
//    calculateMetrics();

    /* Print confusion matrix for the model */
//    printConfusionMatrix();

    /* Show the metrics for the model */
//    printMetrics();

    /* Show off the prediction skills */
    showOff(0);
    
    while(1);
}