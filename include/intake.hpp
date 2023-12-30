#pragma once

#include "main.h"
// #include "robot.hpp"

class Intake {
    public:
        pros::Motor_Group intake_motors;

        pros::motor_brake_mode_e brake_mode;
        
        Intake(std::vector<pros::Motor> motor_ports, pros::motor_brake_mode_e brake_mode);

        void intake_the_award();

        // :((
        void outtake_the_award();

        // uh oh
        void break_the_award();
};
void intake_the_award();