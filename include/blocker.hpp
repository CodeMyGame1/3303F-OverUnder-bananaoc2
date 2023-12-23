#pragma once

#include "main.h"

class Blocker {
    public:
        pros::ADIDigitalOut blocker_piston_1;
        pros::ADIDigitalOut blocker_piston_2;

        bool blocker_enabled = true;

        Blocker(std::uint8_t blocker_port_1, std::uint8_t blocker_port_2);

        void block_da_opponents();
};