/**
 * @file    prediction/extra.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    25-August-2016
 * @brief   This file contains some extra functions related to
 *          predicting classes, accuracy etc.
 * */

#include <stdio.h>
#include "../include/defines.h"
#include "../include/prediction.h"
#include "../include/util.h"

/**
 * @brief Shows off the skill of the classifier by predicting the class of a certain entry.
 * @param testLine The line of the test set to be predicted.
 * */
void showOff(int testLine)
{
    printf("\n---------------------------Prediction Demonstration----------------------");
    printf("\nShowing off the prediction skills in the input vector: \n");
    printTestSetLine(testLine);
    int prediction = predict(testSet[testLine]);
    printf("\nPredicted class %d\n",prediction );
    if(prediction==testSet[testLine][COLUMNS-1])
    {
        printf("It's a hit :)\n");
    }else
    {
        printf("It's a miss :(\n");
    }

}
