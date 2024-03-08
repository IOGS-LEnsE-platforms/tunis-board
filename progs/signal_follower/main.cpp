/**
 * FILENAME :        main.cpp          
 *
 * DESCRIPTION :
 *       Testing TUNIS extension board for Nucleo Board
 *          Signal processing
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    19/jan/2023
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#include "mbed.h"

/// Ticker for sampling
Ticker      sampling_tik;


/// Analog input 1 E1
AnalogIn        analog_E1(PA_0);
/// Analog input 2 E2
AnalogIn        analog_E2(PA_1);
/// Analog output 1 S1 / Can also be used as DigitalOut
AnalogOut       analog_S1(PA_4);
/// Analog output 2 S2 / Can also be used as DigitalOut
AnalogOut       analog_S2(PA_5);

/* Methods */
/**
 * Interrupt routine attached to the sampling of the inputs
 */
void ISR_samplingTik(void);

/* Main code */
int main()
{

    sampling_tik.attach(&ISR_samplingTik, 100us);

    while (true){
    }
}


/* */
void ISR_samplingTik(void){
    /* Inputs sampling */
    float in1 = analog_E1.read();
    float in2 = analog_E2.read();

    /* Outputs update */
    analog_S1.write(in1);
    analog_S2.write(in2);
}