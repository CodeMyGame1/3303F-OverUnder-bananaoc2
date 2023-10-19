#include "main.h"

Chassis::Chassis(std::vector<int> l_motor_ports, std::vector<int> r_motor_ports) {
    // iteratively pushes motors representing left motor ports to a vector of left motors
    for (auto l_motor_port : l_motor_ports) {
        pros::Motor temp(l_motor_port);
        left_motors.push_back(temp);
    }

    // iteratively pushes motors representing right motor ports to a vector of right motors
    for (auto r_motor_port : r_motor_ports) {
        pros::Motor temp(r_motor_port);
        right_motors.push_back(temp);
    }
};

void Chassis::set_controller(pros::controller_id_e_t controller) {
    master = new pros::Controller(controller);
};

void Chassis::drive() {
    pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                    (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                    (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

    int left = master->get_analog(ANALOG_LEFT_Y);
    int right = master->get_analog(ANALOG_RIGHT_Y);

    for (auto left_motor : left_motors) {
        left_motor.move(left * (12000 / 127.0));
    }

    for (auto right_motor : right_motors) {
        right_motor.move(right * (12000 / 127.0));
    }

    pros::delay(10);
};