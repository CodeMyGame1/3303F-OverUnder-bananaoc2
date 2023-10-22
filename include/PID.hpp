#pragma once

#include "main.h"

void Controller;

/**
 * TODO: considering cutting off "PID" from the class variable names
*/
class PID {
    public:
        /**
         * TODO: adjust (all three)!
         * TODO: should the PID constants be final values?
        */
        float PID_Kp;
        float PID_Ki;
        float PID_Kd;

        float pidError = 0;

        float lastError = 0;
        float pidIntegral = 0;
        float pidDerivative = 0;

        float pidDrive = 0;

        pros::Motor* motor;

        float pidReqVal;
        
        int pidIntegralLim;
        int pidDriveMin;
        int pidDriveMax;

        pros::motor_encoder_units_e_t units;

        bool pidRunning = 0;

        /**
         * just in case clarification is necessary... these constructor variables are NOT equivalent to the class variables defined above;
         * they are named similarly to denote that each constructor variable will be assigned to its respective class variable during instantiation
        */
        PID(float PID_Kp, float PID_Ki, float PID_Kd, int motorPort, float pidReqVal, int pidIntegralLim, int pidDriveMin, int pidDriveMax, pros::motor_encoder_units_e_t units);

        void calc_pid();

        void move(float distance);
};