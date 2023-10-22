#pragma once

#include "main.h"

class Wings {
    public:
        pros::ADIDigitalOut* wing_piston;
        pros::Controller* master;

        bool wings_enabled = true;
        bool wings_reset = false;

        Wings(char wing_piston_port);

        /**
         * TODO: change "set_controller" to simply run as part of the constructor
        */
        void set_controller(pros::controller_id_e_t controller);

        // :>
        void wing_it();
};