#pragma once

#include "main.h"

class Wings {
    public:
        pros::ADIDigitalOut* wing_piston;

        // the parent "robot" class
        Robot* robot;

        bool wings_enabled = true;
        bool wings_reset = false;

        Wings(char wing_piston_port, Robot& parent_robot);

        // :>
        void wing_it();
};