#include "main.h"
// #include "robot.hpp"

pros::Motor catapult_motor (8);
pros::Rotation rotSensor (20);

bool cata_reset = false;
bool cata_state = false;

void catapult_us_to_victory() {
    if (!cata_reset) {
        rotSensor.reset();

        catapult_motor.set_brake_mode(MOTOR_BRAKE_HOLD);

        cata_reset = true;
    }

    if (abs(rotSensor.get_angle()/100-305) > 5 || cata_state) {
        catapult_motor.move(127);
    } else { catapult_motor.brake(); }

    if (controller.get_digital_new_press(DIGITAL_A)) {
        cata_state = !cata_state;
    }
}