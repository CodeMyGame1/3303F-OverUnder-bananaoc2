#pragma once

#include "main.h"
#include "robot.hpp"

class Wings {
    public:
        pros::ADIDigitalOut* wing_piston;

        // a reference to the controller of the robot
        pros::Controller* controller;

        bool wings_enabled = true;
        bool wings_reset = false;

        Wings(char wing_piston_port, pros::Controller& controller);

        // :>
        void wing_it();
};