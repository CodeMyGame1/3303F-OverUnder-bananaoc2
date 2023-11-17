// Brake Mode: MOTOR_BRAKE_COAST

#include "main.h"
// #include "robot.hpp"

std::vector<pros::Motor> left_motors = {
    pros::Motor(-5),
    pros::Motor(-4),
    pros::Motor(-3)
};

std::vector<pros::Motor> right_motors = {
    pros::Motor(8),
    pros::Motor(9),
    pros::Motor(10)
};

void drive() {
    // pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
    //                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
    //                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

    int left = controller.get_analog(ANALOG_LEFT_Y);
    int right = controller.get_analog(ANALOG_RIGHT_Y);

    for (auto left_motor : left_motors) {
        left_motor.move(left);
    }

    for (auto right_motor : right_motors) {
        right_motor.move(right);
    }

    pros::delay(10);
}