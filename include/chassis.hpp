#pragma once

#include "main.h"

class Chassis {
    public:
        std::vector<pros::Motor> left_motors;
        std::vector<pros::Motor> right_motors;
        pros::motor_brake_mode_e brake_mode;

        // the parent "robot" class
        Robot* robot;

        Chassis(std::vector<int> l_motors, std::vector<int> r_motors, pros::motor_brake_mode_e brake_mode, Robot& parent_robot);

        void drive();
};