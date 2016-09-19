/**
 * @file    support.h
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    14-September-2016
 * @brief   This file contains the prototypes for the
 *          functions contained in support.c. 
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
 * 
 * */
#ifndef SUPPORT_H
#define SUPPORT_H

/**< Prediction Functions */
float calculateProbability(float x, float mean, float stdev);
float calculateClassProbability(int classNumber, float *inputVector);
int   predict(float *inputVector);
float getAccuracy();
float getPrecision(int class);
float getRecall(int class);
void  calculateMetrics();
void  showOff(int testLine);

/**< Output functions*/
void printMetrics();
void printConfusionMatrix();
void printTestLine(int line);


/**< Peripherals functions */
int randomNumber();
unsigned int ADCRead(unsigned char ch);
void init_adc(void);
void init_uart(void);
void putch(unsigned char data);
#endif //UNTITLED_PREDICTION_H
