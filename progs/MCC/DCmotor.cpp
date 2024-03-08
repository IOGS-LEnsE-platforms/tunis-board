/**
 * FILENAME :        MCC.cpp          
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


#include    "DCmotor.h"

/* */
void motInitPwm(void){
    motFw.period_ms(1);     // starting PWM at 1kHz
    motBw.period_ms(1);     // starting PWM at 1kHz
    motStop();              // forces the speed to 0
}

/* */
void motInitEncoder(void){
    encoder_old_state = (motChB << 1) + motChA;
    motChA.rise(&ISR_encoderEvent);
    motChA.fall(&ISR_encoderEvent);
    motChB.rise(&ISR_encoderEvent);
    motChB.fall(&ISR_encoderEvent);
    encoder_tik_cpt = 0;
}

/* */
void motRotateFw(int speed){
    float rc = speed / 100.0;
    motFw.write(rc);
    motBw.write(0);
}

/* */
void motRotateBw(int speed){
    float rc = speed / 100.0;
    motFw.write(0);
    motBw.write(rc);
}

/* */
void motStop(void){
    motFw.write(0);
    motBw.write(0);
}

/* */
void ISR_encoderEvent(void){
    // state detection of CPR encoder - https://www.cuidevices.com/blog/what-is-encoder-ppr-cpr-and-lpr#cpr
    encoder_new_state = (motChB << 1) + motChA;
    if(encoder_anticlockwise[encoder_old_state] == encoder_new_state){
        encoder_tik_cpt--;
    }
    else{
        if(encoder_clockwise[encoder_old_state] == encoder_new_state){
            encoder_tik_cpt++;
        }
    }
    encoder_old_state = encoder_new_state;

}