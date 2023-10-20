#pragma once

#include "main.h"

class Chassis {
    public:
        std::vector<pros::Motor> left_motors;
        std::vector<pros::Motor> right_motors;
        pros::motor_brake_mode_e brake_mode;

        /**
         * TODO: why does this have to be a pointer?
         * TODO: delete pointers on cleanup
        */
        pros::Controller* master;

        Chassis(std::vector<int> l_motors, std::vector<int> r_motors, pros::motor_brake_mode_e brake_mode);

        /**
         * TODO: change "set_controller" to simply run as part of the constructor
        */
        void set_controller(pros::controller_id_e_t controller);

        void drive();
};