#pragma once

#include "main.h"

class Wings {
    public:
        pros::ADIDigitalOut left_wing;
        pros::ADIDigitalOut right_wing;

        bool wings_enabled = false;

        Wings(std::uint8_t l_wing_port, std::uint8_t r_wing_port);

        void update();

        void reset();

        void open();

        void wing_it();
};