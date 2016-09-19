/**
 * @file    main.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    25-August-2016
 * @brief   This file contains the main body of the program. Please refer to the README file for more information
 *          on how to run/use this code.
 * 
 * 
 *  This file is part of NaiveBayes for PIC.
 *
 *   NaiveBayes for PIC is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   NaiveBayes for PIC is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 * */
#define _XTAL_FREQ 20000000    /**< The clock frequency being used. */

#include <xc.h>
#include <math.h>
#include <stdio.h>
#include "../include/defines.h"
#include "../include/support.h"

/* Pragmas to configure the use of PIC18F*/
#pragma config FOSC     = HS    /// EXTERN CLOCK 20MHZ
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


void main() {
    
    /* Initilizes the UART for printing*/
    init_uart();
    
    /* Initilizes the ADC for random number generation*/
    init_adc();
    
    printf("\nRunning Naive Bayes in Dataset: mfeat\n\n");

    /* Calculates Recall and Precision for classes */
    calculateMetrics();

    /* Print confusion matrix for the model */
    printConfusionMatrix();

    /* Show the metrics for the model */
    printMetrics();

    /* Show off the prediction skills */
    showOff(randomNumber());
    
    /* Loops forever*/
    while(1);
}