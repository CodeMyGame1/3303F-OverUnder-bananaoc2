#include "main.h"

Chassis::Chassis(std::vector<int> l_motor_ports, std::vector<int> r_motor_ports, pros::motor_brake_mode_e brake_mode, Robot& parent_robot) {
    robot = &parent_robot;

    brake_mode = brake_mode;

    // iteratively pushes motors representing left motor ports to a vector of left motors
    for (auto l_motor_port : l_motor_ports) {
        pros::Motor temp(l_motor_port);
        temp.set_brake_mode(brake_mode);
        left_motors.push_back(temp);
    }

    // iteratively pushes motors representing right motor ports to a vector of right motors
    for (auto r_motor_port : r_motor_ports) {
        pros::Motor temp(r_motor_port);
        temp.set_brake_mode(brake_mode);
        right_motors.push_back(temp);
    }
};

void Chassis::drive() {
    pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                    (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                    (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

    int left = robot->controller.get_analog(ANALOG_LEFT_Y);
    int right = robot->controller.get_analog(ANALOG_RIGHT_Y);

    for (auto left_motor : left_motors) {
        left_motor.move(left * (12000 / 127.0));
    }

    for (auto right_motor : right_motors) {
        right_motor.move(right * (12000 / 127.0));
    }

    pros::delay(10);
};