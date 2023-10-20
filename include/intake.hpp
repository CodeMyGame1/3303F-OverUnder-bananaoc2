#pragma once

#include "main.h"

class Intake {
    public:
        /**
         * TODO: why does this have to be a pointer?
         * TODO: delete pointers on cleanup
        */
        pros::Motor* intake_motor;
        pros::ADIDigitalOut* intake_piston;
        pros::Controller* master;

        pros::motor_brake_mode_e brake_mode;

        bool intake_piston_enabled = false;
        bool intake_reset = false;

        Intake(int intake_port, char intake_piston_port, pros::motor_brake_mode_e brake_mode);

        /**
         * TODO: change "set_controller" to simply run as part of the constructor
        */
        void set_controller(pros::controller_id_e_t controller);

        void intake_the_award();
};