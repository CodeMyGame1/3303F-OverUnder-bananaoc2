// Brake Mode: MOTOR_BRAKE_COAST

#include "main.h"
// #include "robot.hpp"

Chassis::Chassis(std::vector<pros::Motor> left_motor_ports, std::vector<pros::Motor> right_motor_ports, pros::motor_brake_mode_e brake_mode) : left_motors(left_motor_ports), right_motors(right_motor_ports) {
    brake_mode = brake_mode;
    
    left_motors.set_brake_modes(brake_mode);
    right_motors.set_brake_modes(brake_mode);
}

void Chassis::tank_drive(int left, int right) {
    left_motors.move(left);
    right_motors.move(right);
}