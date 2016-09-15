/**
 * @file    support.h
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    14-September-2016
 * @brief   This file contains the prototypes for the
 *          functions contained in support.c. 
 * */

#ifndef SUPPORT_H
#define SUPPORT_H

/*Prediction Functions */
float calculateProbability(float x, float mean, float stdev);
float calculateClassProbability(int classNumber, float *inputVector);
int   predict(float *inputVector);
float getAccuracy();
float getPrecision(int class);
float getRecall(int class);
void  calculateMetrics();
void  showOff(int testLine);

/*Output functions*/
void printMetrics();
void printConfusionMatrix();
void printTestLine(int line);


int randomNumber();
unsigned int ADCRead(unsigned char ch);
void init_adc(void);
void init_uart(void);
void putch(unsigned char data);
#endif //UNTITLED_PREDICTION_H
