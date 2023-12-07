#include <string>
#include "main.h"
// #include "robot.hpp"

pros::Motor catapult_motor (20);
pros::Rotation rotSensor (12);

bool cata_reset = false;
bool cata_state = false;

void catapult_us_to_victory() {
    if (!cata_reset) {
        rotSensor.reset();

        catapult_motor.set_brake_mode(MOTOR_BRAKE_HOLD);

        cata_reset = true;
    }

    // ~ 360 - ~308.5

    // if (abs(rotSensor.get_angle()/100-305) > 5 || cata_state) {
    
    // pros::lcd::print(0, "Rotation Sensor Value: ");
    // console.log(std::to_string(rotSensor.get_angle()));

    pros::lcd::print(0, "Rotation Sensor Value: %s", std::to_string(rotSensor.get_angle()));
    
    if ((((rotSensor.get_angle() / 100) < 355) && ((rotSensor.get_angle() / 100) > 305)) || cata_state) {
        catapult_motor.move(127);
    } else { catapult_motor.brake(); }

    if (controller.get_digital_new_press(DIGITAL_A)) {
        cata_state = !cata_state;
    }
}