# Naive Bayes for PIC
This is a c implementation of the Machine Learning algorithm called Naive Bayes Gaussian. 
It's been adapted from the ORIGINAL python version in: [Naive Bayes Classifier from Scratch in Python](http://machinelearningmastery.com/naive-bayes-classifier-scratch-python/). 

This algorithm takes a series of data and classifies them into pre-defined classes based on the knowleddge extracted from a training set in a training phase.

This algorithm was developed to be used in the Embbeded System Module at IFCE to be run in an **PIC18F platform**, more specifically the PIC18F4550 MCU.

The **original** algorithm was divided into two phases:
- **Training**, where the dataset will be used to generate the summaries (means and standard deviation) intermediate dataset. This phase happens in a computer. The code for this phase can be found in: https://ajeferson.github.io/files.html and https://github.com/ajeferson/NaiveBayes 
- **Prediction**, where the intermediate dataset + testset will be use to generate the predictions. The prediction phase is the one that runs in the PIC plataform. 

## 1) Project organization
The project was organized based on the _STM32F Peripheral Library examples_ provided by **STMicroeletronics** followig these guidelines:
- Each .c file has an .h file with the functions headers
- The functions were separated according to their purposes
- The comments can be used to generate automatic documentation


## 2) Development context
The code was devolped with the purpose of running in a PIC18F4550 microcontroller, therefore memory and time restrictions should be observed in order to run the code properly. The following constraints should be noted:
- When developing the code we had 32Kbytes of ROM and 2Kbytes of RAM available, therefore our datasets were modeled and made to fit these requirements. Unless you have an external memory unit, your datasets should follow the same guidelines. To see more on how to use your own datasets, please refer to section 3.
- The code was made to run in the **MPLAB X IDE** with the **XC8** compiler , we don't guarantee it will run anywhere else (not even in your version of MPLABX and XC8 for that matter).



## 3) Where to start
#### a) The project files:

- **main.c** - Main program the calls functions from the support library (support.c). Take a look at this file to have an idea of how the flow of the programm works.
- **support.c** - Implementation of the support functions. The file has 3 kinds of functions: printing, prediciton and peripherals functions. The core of the application is in here.
- **support.h** - Headers of the functions in support.c
- **defines.h** - Definitions of special variables. In here you can alter the dataset to be used in the predictions or add your own.

#### b) Input and Output
###### The input of the program is:
- a dataset of means summarizing the training data.
- a dataset of standard deviation sumarizing the training data.
- a dataset with test cases.

All three datasets can be found in the **defines.h** file.

###### The output of the program is:
- A confusion matriz summaring the predictions of the test set.
- For each test set, the probability for each defined class.
- Metrics for the classification (i.e. Accuracy, Recall and Precision).
- A random prediction from one of the input test cases.


#### c) To use the already defined datasets
This project already comes with 3 pre-defined datasets. To use any of them, go to the **defines.h** file and uncomment the desired dataset. Don't forget to comment out the one that is being used so there won't be any conflicts. After that just run and compile the code again.

#### To use your own dataset
At this point you must have a matrix of means and another of standard deviations that summarize your training data. This is the knowledge of the classifier. All work will be done in the **defines.h** file. Follow the steps to use the code: 
- 1) Alter the values of the defines *COLUMN*, *CLASSES*, *TESLINES* to fit your datasets.
- 2) Fill in the means matrix with your means data.
- 3) Fill in the stdevs matrix with your standard deviation data.
- 4) Fill in the testSet matrix with as much test data as possible. Depending on the amount of test data the PIC memory limitation won't allow your to fill eveything.



## 4) Copyright

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.