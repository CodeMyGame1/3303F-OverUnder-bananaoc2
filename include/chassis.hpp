#pragma once

#include "main.h"
#include "robot.hpp"

class Chassis {
    public:
        std::vector<pros::Motor> left_motors;
        std::vector<pros::Motor> right_motors;
        pros::motor_brake_mode_e brake_mode;

        // a reference to the controller of the robot
        pros::Controller* controller;

        Chassis(std::vector<int> l_motors, std::vector<int> r_motors, pros::motor_brake_mode_e brake_mode, pros::Controller& controller);

        void drive();
};