/**
 * @file    util.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    25-August-2016
 * @brief   This file contains the implementations for the
 *          auxiliar functions, i.e. print functions.
 * */

#include <stdio.h>
#include "../include/util.h"
#include "../include/defines.h"
#include <plib/usart.h>

/**
 * @brief Prints to the console the test dataset.
 * */
/*void printTestset() {
    int i, j;
    for (i = 0; i < TEST_LINES; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf("%f", testSet[i][j]);
            if(j < COLUMNS - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}*/

/**
 * @brief Prints the summaries to the console.
 * */
/*void printSummaries() {

    int i, j;
    for (i = 0; i < CLASSES; i++) {
        printf("Classe %d:\n", i);
        for (j = 0; j < COLUMNS - 1; j++) {
            printf("(%11.6f, %11.6f)\n", means[i][j], stdevs[i][j]);
        }
        printf("\n");
    }

}*/


/**
 * @brief Prints the confusion matrix of the model.
 * */
void printConfusionMatrix()
{
    printf("------------------Confusion Matrix for the Model------------------\n          ");
    int i, j;

    //printf("          ");
    for(i = 0; i<CLASSES; i++)
    {
	printf(" C%d   ",i);
    }
    printf("\n");
    for(i = 0; i<CLASSES;i++)
    {
        printf("Class %d |",i);
        for(j = 0; j<CLASSES;j++)
            printf("  %d   ",confusionMatrix[i][j] );
        printf("\n");
    }
}

/**
* @brief Prints a given line from the test set.
* @param The line index to be printed.
**/
void printTestSetLine(int line)
{
    int i;
    for(i = 0; i<COLUMNS; i++)
    {
        printf("%f, ",testSet[line][i]);
    }
}

//unsigned char UART1Config = 0, baud = 0;

void putch(unsigned char data) {
    while( ! PIR1bits.TXIF)          // wait until the transmitter is ready
        continue;
    TXREG = data;                     // send one character
}

void init_uart(void) {
    TXSTAbits.TXEN = 1;     // enable transmitter
    TXSTAbits.BRGH = 1;     // high baud rate mode
    RCSTAbits.CREN = 1;     // enable continous receiving

    // configure I/O pins
    ADCON1 = 0xff;
    TRISBbits.TRISB5 = 1;     // RX pin is input
    TRISBbits.TRISB7 = 1;     // TX pin is input (automatically configured)

    SPBRG = 129;            // set baud rate to 9600 baud (4MHz/(16*baudrate))-1

    PIE1bits.RCIE = 1;      // enable USART receive interrupt
    RCSTAbits.SPEN = 1;     // enable USART
}

void init_adc(void) {
    ADCON2= 0b10001010;
}

unsigned int ADCRead(unsigned char ch) {
    
   if(ch>13) return 0;  //Invalid Channel
   
   ADCON0=0x00;
   ADCON0=(ch<<2);   //Select ADC Channel
   ADON=1;  //switch on the adc module
   GODONE=1;  //Start conversion
   
   while(GODONE); //wait for the conversion to finish
   
   ADON=0;  //switch off adc

   return ADRES;
   
}

int randomNumber() {
    
    int i;
    int acc = 0;
    float res;
    
    for(i = 0;i < 100; i++) {
        acc+=ADCRead(1);
    }
    
    res = (acc/100.0 - (int)(acc/100.0))*100000;
    res = ((int) res) % TEST_LINES;
    return (int) (res < 0 ? -res : res);
    
}
