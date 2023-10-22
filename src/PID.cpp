#include "main.h"

PID::PID(float PID_Kp, float PID_Ki, float PID_Kd, int motorPort, float pidReqVal, int pidIntegralLim, int pidDriveMin, int pidDriveMax, pros::motor_encoder_units_e_t units) {
    PID_Kp = PID_Kp;
    PID_Ki = PID_Ki;
    PID_Kd = PID_Kd;
    motor = new pros::Motor(motorPort);
    pidReqVal = pidReqVal;
    pidIntegralLim = pidIntegralLim;
    pidDriveMin = pidDriveMin;
    pidDriveMax = pidDriveMax;
    units = units;

    motor->set_encoder_units(units);

    /**
     * TODO: `tare_position()` and `set_zero_position()` are equal in function, but theoretically only semantically different; verify that this is true
    */
    motor->tare_position();
}

/**
 * TODO: turn into while() loop task
*/
void PID::calc_pid() {
    if (pidRunning) {

        float curVal = motor->get_position();

        float pidError = curVal - pidReqVal;

        // integral term!
        if (PID_Ki != 0) {
            // if we're close enough to the target that the integral limit actually applies
            if (abs(pidError) < pidIntegralLim) {
                pidIntegral += pidError;
            } else {
                pidIntegral = 0;
            }
        } else {
            pidIntegral = 0;
        }

        pidDerivative = pidError - lastError;
        lastError = pidError;

        pidDrive = (PID_Kp * pidError) + (PID_Ki * pidIntegral) + (PID_Kd * pidDerivative);

        if (pidDrive > pidDriveMax) {
            pidDrive = pidDriveMax;
        } else if (pidDrive < pidDriveMin) {
            pidDrive = pidDriveMin;
        }

        motor->move(pidDrive);
    } else {
        pidError = 0;
        lastError = 0;
        pidIntegral = 0;
        pidDerivative = 0;
    }

    // consider having pros::delay here, IF it's not being called as part of a repeating main loop in the auton
}

void PID::move(float distance) {
    pidReqVal += distance;
}