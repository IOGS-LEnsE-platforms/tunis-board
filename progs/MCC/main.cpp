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
#include "DCmotor.h"

/// MCC library inputs/outputs declaration - based on TUNIS board from LEnsE
//     (http://lense.institutoptique.fr/ressources/General/LEnsE/TPElec/CarteTUNIS/Carte_TUNIS.pdf)
PwmOut              motFw(D10);
PwmOut              motBw(D9);
InterruptIn         motChA(D15); 
InterruptIn         motChB(D14);

int         tik_per_tour = 979;     // Pololu Motor - 3039 - 20.4:1 * 48 CPR
int         encoder_tik_cpt;
uint8_t     encoder_new_state = 0;
uint8_t     encoder_old_state = 0;

/// Others inputs/outputs declaration - based on TUNIS board from LEnsE
//     (http://lense.institutoptique.fr/ressources/General/LEnsE/TPElec/CarteTUNIS/Carte_TUNIS.pdf)
/// Error of the System Control Loop - 1 revolution = 0 to 3.3V (DAC)
AnalogOut           systemError(D13); 
/// Output of the System Control Loop - 1 revolution = 0 to 3.3V (DAC)
AnalogOut           systemOutput(A2); 
/// Setpoint Input of the System Control Loop - 1 revolution = 0 to 3.3V (ADC)
AnalogIn            setpointInput(A0);
/// Ticker for the control loop sampling
Ticker              controlLoopTik;

/// Input command for position control
float               control_input;
/// Error of the control Loop
float               controlLoop_error;
/// Position of the motor - 1 revolution = 0 to 3.3V (DAC)
float               controlLoop_ouput;
/// Gain of the PID controller
float               gain = 100.0;

/* Methods */
/**
 * Interrupt routine attached to the sampling of the Contol Loop System
 *
 * @return Updates the system control loop outputs
 */
void ISR_controlLoopTik(void);

/* Main code */
int main()
{
    motInitPwm();

    motRotateFw(50);        // motor turns clockwise at 50% of the maximum speed
    wait_us(3000000);       // ... during 3 s
    motStop();              // motor stops
    wait_us(1000000);       // ... during 1 s
    motRotateBw(70);        // motor turns anticlockwise at 70% of the maximum speed
    wait_us(2000000);       // ... during 2 s
    motStop();              // motor stops
    wait_us(1000000);       // ... during 1 s
    
    motInitEncoder();
    controlLoopTik.attach(&ISR_controlLoopTik, 100us);

    while (true){
    }
}


/* */
void ISR_controlLoopTik(void){
    int output_val;
    /* Input sampling and error calculation */
    control_input = setpointInput.read()-0.5;
    controlLoop_error = (control_input - (1.0*encoder_tik_cpt/tik_per_tour));
    //systemError.write(controlLoop_error / 2.0 + 0.5);
    systemError.write(controlLoop_error + 0.5);

    /* Output update */
    if(controlLoop_error <= 0){
        output_val = -gain*controlLoop_error;
        motRotateBw(output_val);
    }
    else{
        output_val = gain*controlLoop_error;
        motRotateFw(output_val);
    }
    systemOutput.write(1.0*encoder_tik_cpt/tik_per_tour + 0.5);

}