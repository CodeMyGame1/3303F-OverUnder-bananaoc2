#pragma once

#include "main.h"

class Blocker {
    public:
        pros::ADIDigitalOut blocker_piston;

        bool piston_enabled = true;

        Blocker(std::uint8_t blocker_port);

        void block_da_opponents();
};