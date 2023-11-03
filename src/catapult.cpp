#include "main.h"

Catapult::Catapult(int pros_motor_port, int rot_sensor_port, pros::motor_brake_mode_e brake_mode, Robot& parent_robot) {
    robot = &parent_robot;

    catapult_motor = new pros::Motor(pros_motor_port);
    rotSensor = new pros::Rotation(rot_sensor_port);

    brake_mode = brake_mode;
}

void Catapult::catapult_us_to_victory() {
    if (!cata_reset) {
        rotSensor->reset();

        catapult_motor->set_brake_mode(MOTOR_BRAKE_HOLD);

        cata_reset = true;
    }

    if (abs(rotSensor->get_angle()/100-305) > 5 || cata_state) {
        catapult_motor->move(127);
    } else { catapult_motor->brake(); }

    if (robot->controller.get_digital_new_press(DIGITAL_A)) {
        cata_state = !cata_state;
    }
}