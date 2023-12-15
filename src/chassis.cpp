// Brake Mode: MOTOR_BRAKE_COAST

#include "main.h"
// #include "robot.hpp"

Chassis::Chassis(std::vector<pros::Motor> left_motor_ports, std::vector<pros::Motor> right_motor_ports) : left_motors(left_motor_ports), right_motors(right_motor_ports) {}

void Chassis::tank_drive(int left, int right) {
    left_motors.move(left);
    right_motors.move(right);
}

// void drive() {
//     // pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
//     //                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
//     //                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

//     int left = controller.get_analog(ANALOG_LEFT_Y);
//     int right = controller.get_analog(ANALOG_RIGHT_Y);

//     for (auto left_motor : left_motors) {
//         left_motor.move(left);
//     }

//     for (auto right_motor : right_motors) {
//         right_motor.move(right);
//     }

//     pros::delay(10);
// }