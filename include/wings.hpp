#pragma once

#include "main.h"

class Wings {
    public:
        pros::ADIDigitalOut wing_left_piston;
        pros::ADIDigitalOut wing_right_piston;

        bool wings_enabled = false;

        Wings(std::uint8_t wing_left_piston_port, std::uint8_t wing_right_piston_port);

        void update();

        void close();

        void open();

        void wing_it();
};