#include <string>
#include "main.h"
// #include "robot.hpp"

Catapult::Catapult(int cata_port, int rot_port, pros::motor_brake_mode_e brake_mode) : catapult_motor(cata_port), rotSensor(rot_port) {
    // ideally, catapult should start out AT THE BOTTOM!

    rotSensor.reset();

    brake_mode = brake_mode;

    catapult_motor.set_brake_mode(brake_mode);
}

int Catapult::get_formatted_angle() {
    int curr_angle = rotSensor.get_angle();
    // basically if it's like 10 or something
    if (curr_angle < 300) {
        curr_angle = 360 + (curr_angle / 100);
    }

    return curr_angle;
}

void Catapult::reset() {
    int curr_angle = this->get_formatted_angle();

    while (
        // checks if catapult is NOT at the bottom
        // basically subtracting current state from "base" state (base state is 310 degrees; * 100 = 31000 centidegrees)
        (curr_angle / (310 - 10)) - ((310 * 100) / (310 - 10)) > 0 
        // and, of course, if the driver wants the catapult to run...
        // guess we can't do anythin about that ¯\_(ツ)_/¯
        || cata_state)
    {
        // if catapult ain't at the bottom, let's move it there!
        catapult_motor.move(127);

        int curr_angle = rotSensor.get_angle();
        // basically if it's like 10 or something
        if (curr_angle < 300) {
            curr_angle = 360 + (curr_angle / 100);
        }
    }
    
    catapult_motor.brake();
}

void Catapult::toggle_catapult() {
    // toggles the catapult... ikr who would've thought

    cata_state = !cata_state;
}

void Catapult::catapult_us_to_victory() {
    pros::lcd::print(0, "Rotation Sensor Value: %s", std::to_string(rotSensor.get_angle()));

    int curr_angle = this->get_formatted_angle();

    if (
        // checks if catapult is NOT at the bottom
        // basically subtracting current state from "base" state (base state is 310 degrees; * 100 = 31000 centidegrees)
        (curr_angle / (310 - 10)) - ((310 * 100) / (310 - 10)) > 0 
        // and, of course, if the driver wants the catapult to run...
        // guess we can't do anythin about that ¯\_(ツ)_/¯
        || cata_state)
    {
        // if catapult ain't at the bottom, let's move it there!
        catapult_motor.move(127);
    } else {
        // if thine shalt not move, THINE SHALT NOT MOVE!
        catapult_motor.brake();
    }
}