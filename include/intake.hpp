#pragma once

#include "main.h"
#include "robot.hpp"

class Intake {
    public:
        /**
         * TODO: why does this have to be a pointer?
         * TODO: delete pointers on cleanup
        */
        pros::Motor* intake_motor;
        pros::ADIDigitalOut* intake_piston;

        pros::motor_brake_mode_e brake_mode;

        // a reference to the controller of the robot
        pros::Controller* controller;

        bool intake_piston_enabled = false;
        bool intake_reset = false;

        Intake(int intake_port, char intake_piston_port, pros::motor_brake_mode_e brake_mode, pros::Controller& controller);

        void intake_the_award();
};