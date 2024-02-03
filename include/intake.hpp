#pragma once

#include "main.h"
// // #include "robot.hpp"

// void intake_the_award();

class Intake {
    public:
        // pros::ADIDigitalOut intake_piston_in;
        // pros::ADIDigitalOut intake_piston_out;

        pros::Motor intake_motor;
        pros::motor_brake_mode_e brake_mode;

        bool intake_enabled;

        // Intake(std::uint8_t intake_piston_port1, std::uint8_t intake_piston_port2);

        Intake(std::int8_t intake_motor_port, pros::motor_brake_mode_e brake_mode);

        // void update();

        // void extend_intake();

        // void retract_intake();

        void intake_the_award();

        void outtake_the_award();

        void break_the_award();
};