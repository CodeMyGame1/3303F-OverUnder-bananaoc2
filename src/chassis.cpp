// Brake Mode: MOTOR_BRAKE_COAST

#include "main.h"
// #include "robot.hpp"

Chassis::Chassis(std::vector<pros::Motor> left_motor_ports, std::vector<pros::Motor> right_motor_ports, pros::motor_brake_mode_e brake_mode) : left_motors(left_motor_ports), right_motors(right_motor_ports) {
    brake_mode = brake_mode;
    
    // left_motors.set_encoder_units(pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_ROTATIONS);
    // right_motors.set_encoder_units(pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_ROTATIONS);

    left_motors.set_brake_modes(brake_mode);
    right_motors.set_brake_modes(brake_mode);
}

void Chassis::tank_drive(int left, int right) {
    // pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
    //                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
    //                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

    
    left_motors.move(left);
    right_motors.move(right);
}