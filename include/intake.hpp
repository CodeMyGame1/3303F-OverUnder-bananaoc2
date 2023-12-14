#pragma once

#include "main.h"

class Intake {
    public:
        pros::Motor intake_motor;

        pros::motor_brake_mode_e brake_mode;
        
        Intake(int intake_port, pros::motor_brake_mode_e brake_mode);

        void intake_the_award();

        // :((
        void outtake_the_award();

        // uh oh
        void break_the_award();
};