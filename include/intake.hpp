#pragma once

#include "main.h"
// // #include "robot.hpp"

// void intake_the_award();

class Intake {
    public:
        pros::ADIDigitalOut intake_piston_in;
        pros::ADIDigitalOut intake_piston_out;

        bool intake_enabled;

        Intake(std::uint8_t intake_piston_port1, std::uint8_t intake_piston_port2);

        void update();

        void extend_intake();

        void retract_intake();
};