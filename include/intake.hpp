#pragma once

#include "main.h"
// // #include "robot.hpp"

// void intake_the_award();

class Intake {
    public:
        pros::ADIDigitalOut intake_pistons;

        bool intake_enabled;

        Intake(std::uint8_t intake_piston_port);

        void update();

        void extend_intake();

        void retract_intake();
};