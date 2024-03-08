/**
 * FILENAME :        MCC.h          
 *
 * DESCRIPTION :
 *       Direct Current Motor control by a standard H-bridge (L293/L298)
 *
 *       This library gives function to control a Direct Current Motor by
 *  a standard H-bridge (type L293 or L298)
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    19/jan/2023
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#ifndef     __DCMOTOR_H__
#define     __DCMOTOR_H__

#include "mbed.h"

/* Inputs and outputs - Must be defined in the main part of the application */
/// CC motor pin - clockwise direction
extern      PwmOut      motFw;
/// CC motor pin - anticlockwise direction
extern      PwmOut      motBw;

/// Channel A of the quadrature encoder
extern      InterruptIn     motChA;   
/// Channel B of the quadrature encoder
extern      InterruptIn     motChB;

/// Error of the System Control Loop - 1 revolution = 0 to 3.3V (DAC)
extern      AnalogOut       systemError; 

/// Output of the System Control Loop - 1 revolution = 0 to 3.3V (DAC)
extern      AnalogOut       systemOutput; 

/* Global variables */
/// tik counter from the quadrature encoder
extern      int             encoder_tik_cpt;
/// tik number per tour value for CPR encoder
extern      int             tik_per_tour;
/// state of the encoder
extern      uint8_t         encoder_new_state;
extern      uint8_t         encoder_old_state;
const       uint8_t         encoder_anticlockwise[4] = {1, 3, 0, 2};
const       uint8_t         encoder_clockwise[4] = {2, 0, 3, 1};

/* Methods */

/**
 * Initializes the PWM output for controling the DC motor and forces the speed to 0
 *
 * @return Modifies the PWM frequency at 1kHz and forces the duty cycle to 0
 */
void motInitPwm(void);

/**
 * Initializes the interrupt routines attached to the two channels encoder
 *
 * @return Attaches interrupt routines to rising and falling edge of the quadrature encoder channels
 */
void motInitEncoder(void);

/**
 * Modifies the rotation speed of the CC motor in the Clockwise direction
 *
 * @param[in] speed the relative value of the rotation speed - expressed as a percentage - 0 to 100 %.
 *
 * @return Modifies the rotation speed of the CC motor in the Clockwise direction
 */
void motRotateFw(int speed);

/**
 * Modifies the rotation speed of the CC motor in the AntiClockwise direction
 *
 * @param[in] speed the relative value of the rotation speed - expressed as a percentage - 0 to 100 %.
 *
 * @return Modifies the rotation speed of the CC motor in the AntiClockwise direction
 */
void motRotateBw(int speed);

/**
 * Modifies the rotation speed of the CC motor in the AntiClockwise direction
 *
 * @param[in] speed the relative value of the rotation speed - expressed as a percentage - 0 to 100 %.
 *
 * @return Modifies the rotation speed of the CC motor in the AntiClockwise direction
 */
void motStop(void);

/**
 * Interrupt routine attached to the encoder channels event (rising and falling edge)
 *
 * @return Increments or decrements {encoder_tik_cpt} counter depending on the rotation direction
 */
void ISR_encoderEvent(void);


#endif