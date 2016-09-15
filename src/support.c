/**
 * @file    support.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    23-September-2016
 * @brief   This file contains functions that execute predictions, test accuracy etc
 *          on the knowledge (summaries) with the test data set. It also contains all functions
 *          related to outputting the data to the user.
 * */


#include <stdio.h>
#include "../include/defines.h"
#include <math.h>
#include <plib/usart.h>



/*--------------------------------------------------------------------------------------------------
 * 
 * PREDICTION FUNCTIONS
 * 
--------------------------------------------------------------------------------------------------*/
/**
 * @brief Calculates the log (natural log) probability of a given number belonging to a distribution based on the gaussian:
 * @note p = 1/(sqrt(2*PI*stdev)) * e^-(((x- mean)^2)/(2*(stdev^2)))
 * Where stdev is the standard deviation of the column and class to which x belongs to.
 * Where mean is the mean of the column and class to which x belongs to.
 * @param[in] float x The input value to be evaluated by the formula.
 * @param[in] float mean The mean value of the column and class to which x belongs to.
 * @param[in] float stdev The standard deviation of the column and class to which x belongs to.
 * @returns The likelihood (in log probability domain) of x belonging to the distribution represented by mean and stdev.
 * */
float calculateProbability(float x, float mean, float stdev)
{
    float number = x - mean;
    float power  = -(number*number)/(2*stdev*stdev);
    float res = ((SQRT2PI * stdev));     
    return power-log(res);
    
}


/**
 * @brief Calculates the total probability of a certain class based on single probabilities yielded by each feature.
 *        THe function will calculate the probability of each feature(column) from the input vector and add them together.
 * @param[in] int classNumber The class to be considered
 * @returns the cumulative probability of that class
 * */
float calculateClassProbability(int classNumber, float *inputVector)
{
    int i;
    float classProbability = 0;
    /*  for each feature, calculate the probability and add them together */
    for(i = 0; i<COLUMNS-1; i++)
    {
        /*  considering the Bayes criterion, the total probability is the product of each single probability */
        classProbability+=calculateProbability(inputVector[i], means[classNumber][i], stdevs[classNumber][i] ); 
    }

    return classProbability;
   
}


/**
 * @brief Predicts to which class the input vector belongs.
 *
 * @note Basically, runs over the probabilities for each class
 * and returns the highest one.
 *
 * @param[in] float* inputVector The pointer to the vector to predict the class. The input vector
 * must me a set of values with the (COLUMNS - 1) columns. It is a set of attributes for the algorithm to predict
 * based on the knowledge it has calculated.
 * @return The predicted class to which the input vector belongs.
 * */
int predict(float *inputVector) {

    int i;

    /*  Probability of a class in each loop */
    float classProb;

    /*  Holds the highest probability */
    float bestProb = -1;

    /*  Holds the number of class which has the highest probability */
    int bestLabel = -1;

    for(i = 0; i < CLASSES; i++) {
        classProb = calculateClassProbability(i, inputVector); /*  Calculating the probability for the current class on the loop */
	
        printf("Proability for class %d: %f\n",i,classProb);
        if((bestLabel==-1) || (classProb > bestProb)) { /*  Checking if the new class' probability is higher than the highest known probability */
            bestProb = classProb;
            bestLabel = i;  
        }
    }
    printf("\n\n");
        
    return bestLabel;

}


/**
 * @brief Fills in the values in the confusion matrix. 
 * @note The size of the Confusion Matrix is determined by the number of possible classes.
 * A confusion matrix for a 2 class model is:
 *                      Predicted Class 0           Predicted Class 1
 * Entry is of Class 0  True positives              False Negatives
 * Entry is of Class 1  False positives             True Negatives
 * The function will run over each entry of the testSet(row) and yeild the result of the prediction,
 * it will then fill the confusion matrix with the result of the prediction
 * */
void calculateMetrics()
{

    int i,j;

    for(i = 0; i<CLASSES; i++)
    {
        for(j = 0; j<CLASSES; j++)
            confusionMatrix[i][j] = 0;
    }

    /*  Holds the current prediction on the loop */
    int prediction;

    for(i = 0; i < TEST_LINES; i++) {
        printf("Test line #%d\n",i);
        prediction = predict(testSet[i]); /*  Gets the prediction for a given test set line */
        confusionMatrix[(int)testSet[i][COLUMNS-1]][prediction]++;
    }

}


/**
 * @brief Runs over the confusion matriz and calculates the accuracy of the model.
 *        The accuracy of the model is the percntage of correct guesses it made, this is derived
 *        from the confusion matriz by simply adding up the numbers in the main diagonal and
 *        deviding by the total amount of elements in the matrix.
 * @returns The percentage of right predictions on the test set.
 * */
float getAccuracy() {

    int i;
    int sum = 0;
    for(i = 0; i<CLASSES;i++)
    {
        sum+=confusionMatrix[i][i];
    }

    return (sum/(float)TEST_LINES);

}


/**
 * @brief Analyzes the Confusion Matrix outputed by the model and calculates the recall.
 * @note The recall, or sensibility reveals the capability of the model to correclty predict a class in the cases
 * in which a data entry belongs to that class. Can the model identify when an instance belongs to a class?
 * @return The true positives over the sum of true positves and false negatives. For a multiclass problem the recall of a class i
 * will be M[i][i]/sum of elements of line i. M is the confusion matrix for the model.
 * */
float getRecall(int class)
{
    int i;
    int sum = 0;
    for(i = 0; i<CLASSES;i++)
    {
        sum+=confusionMatrix[class][i];
    }

    return (confusionMatrix[class][class]/(float)sum);
}

/**
 * @brief Analyzes the Confusion Matrix outputed by the model and calculates the precision.
 * @note The precision reveals the capability of the model to correclty predict a class in the cases
 * in which a data entry doesn't belong to that class. Can the model identify when an instance does NOT belong to a class?
 * @return The true negatives over the sum of true negatives and false positives. For a multiclass problem the precision of a class i
 * will be M[i][i]/sumof elements of column i. M is the confusion matrix for the model.
 * */
float getPrecision(int class) {
    int i;
    int sum = 0;
    for(i = 0; i<CLASSES;i++)
    {
        sum+=confusionMatrix[i][class];
    }
    return (confusionMatrix[class][class]/(float)sum);
}


/**
 * @brief Shows off the skill of the classifier by predicting the class of a certain entry.
 * @param testLine The line of the test set to be predicted.
 * */
void showOff(int testLine)
{
    printf("\n---------------------------Prediction Demonstration----------------------\nShowing off the prediction skills in the input vector: \n");
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


/*--------------------------------------------------------------------------------------------------
 * 
 * PRINTING FUNCTIONS
 * 
--------------------------------------------------------------------------------------------------*/

/**
 * @brief Print out the metrics (Recall, Precision and Accuracy for the model).
 * @note Please note that the Recall and Precision are printed by class and the Accuracy is for the whole model.
 * */
void printMetrics()
{
    printf("\n------------------Metrics for the Model---------------------------\n");
    int i;
    for(i = 0; i<CLASSES; i++)
    {
        printf("Metrics for Class %d\n", i);
        printf("Precision %f\n", getPrecision(i));
        printf("Recall %f\n\n",getRecall(i) );
    }

    printf("\nModel Accuracy considering %d test entries: %f%%\n", TEST_LINES, getAccuracy());
}


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
* @param The line index to be printed. Normally randomonly picked.
**/
void printTestSetLine(int line)
{
    int i;
    for(i = 0; i<COLUMNS; i++)
    {
        printf("%f, ",testSet[line][i]);
    }
}


/**
 * @brief Effectively prints out a byte in the USART interface.
 * @note To make the printf function works by printing in the USART interface this function needed
 *       to  be implemented, this funtions normally prints out the result in the screen. Note that
 *       in this case it will use the TXREG to output the data therefore printing out in the USART
 *       interface.
 * @param data
 */



/*--------------------------------------------------------------------------------------------------
 * 
 * PERIPHERALS FUNCTIONS
 * 
--------------------------------------------------------------------------------------------------*/

void putch(unsigned char data) {
    /* wait until the transmitter is ready */
    while( ! PIR1bits.TXIF)          
        continue;
    /* Send the byte by putting it in the transmitter register*/
    TXREG = data;                     
}



/** @brief Initilizes the usart interface.
 *  @note The usart interface is needed for the outputting of the system results. 
 *  Hence the need of this function.
 **/
void init_uart(void) {
    
    unsigned char UART1Config = 0, baud = 0;
    
    /* Enable transmitter*/
    TXSTAbits.TXEN = 1;  
    
    /* Enables serial port*/
    RCSTAbits.SPEN = 1;               
    
    /**
     * COnfigures the USART communication
     * USART_TX_INT_OFF - Transmit interrupt is turned off
     * USART_RX_INT_OFF - Receive interrupt is turned off
     * USART_ASYNCH_MODE - USART is in asinc mode
     * USART_EIGHT_BIT - Data has 8 bit
     * USART_BRGH_HIGH - Will use high baud rate
     */
    
    UART1Config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_HIGH ;
   
    /* Bauderate calculated*/
    /**
     * X = ((FOSC/Desired Baud Rate)/16) ? 1
     * The desired baud rate is 9600, FOSC is 20000000 therefore the number is 129
     */
    baud = 129;
    
    /* Start the USART with the above configuration*/
    OpenUSART(UART1Config,baud);

}

/**
 * @brief Starts up the adc for capturing a reading from a pin
 */
void init_adc(void) {
    /**
     * bit7 - Result is right justified
     * bit6 - Not implemented
     * bit5-3 -2TAD is enough time with a 20MHZ cristal
     * bit 2-0 - FOSC is devided by 16
     */
    ADCON2= 0b10001101;
}

/**
 * @brief Read the data from a certain ADC chanel
 * @param ch The channel fromwhich to read the data
 * @return The data read from the channel, a integer number from 0 to 1023
 */
unsigned int ADCRead(unsigned char ch) {
    
   /* Verifies if it's a valid channel*/ 
   if(ch>13) return 0;  
   
   /* Clears Channel seletor register*/
   ADCON0=0x00;
   
   /* The channel selection bits are bits 5-2, therefore we need to shift the input channel by two bits*/
   ADCON0=(ch<<2);   
   
   /* Switch on the ADC*/
   ADON=1;  
   
   /*Let the conversion begin*/
   GODONE=1;  
   
   /* Wait until it is ready*/
   while(GODONE); 
   
   /*Switch off the ADC*/
   ADON=0;  

   /* Returns the data read*/
   return ADRES;
   
}

/**
 * @brief Uses the ADC to select a random numer to be used as selector of a test line
 * @note It will collect 100 readings and take the avarage of them.
 *       It will then remove the floating point part of the number, normalize it and use as random number.
 * @return A random number generated by the adc in the range 0-TestLines
 */
int randomNumber() {
    
    int i;
    int acc = 0;
    float res;
    
    /* Collects 100 readings*/
    for(i = 0;i < 100; i++) {
        acc+=ADCRead(1);
    }
    
    /* Removes the integer part of the number and turns it into a new integer number*/
    res = (acc/100.0 - (int)(acc/100.0))*100000;
    
    /* Normalize it to fit the range 0 - TESLINES*/
    res = ((int) res) % TEST_LINES;
    
    /* Sometimes the number is negative, takes care of this option*/
    return (int) (res < 0 ? -res : res);
    
}

