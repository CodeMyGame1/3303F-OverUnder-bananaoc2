#pragma once

#include "main.h"

class Wings {
    public:
        pros::ADIDigitalOut wing_piston;

        bool wings_enabled = false;

        Wings(std::uint8_t wing_piston_port);

        void update();

        void close();

        void open();

        void wing_it();
};