#pragma once

#include "main.h"

class Chassis {
    public:
        std::vector<pros::Motor> left_motors;
        std::vector<pros::Motor> right_motors;
        pros::Controller* master;

        Chassis(std::vector<int> l_motors, std::vector<int> r_motors);

        void set_controller(pros::controller_id_e_t controller);

        void drive();
};