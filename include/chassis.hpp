#pragma once

#include "main.h"
// #include "robot.hpp"

class Chassis {
    public:
        pros::Motor_Group left_motors;
        pros::Motor_Group right_motors;

        Chassis(std::vector<pros::Motor> left_motor_ports, std::vector<pros::Motor> right_motor_ports);

        void tank_drive(int left, int right);
};

// void drive();