#include <string>
#include "main.h"
// #include "robot.hpp"

Catapult::Catapult(int cata_port, int rot_port, pros::motor_brake_mode_e brake_mode) : catapult_motor(cata_port), rotSensor(rot_port) {
    // ideally, catapult should start out AT THE BOTTOM!

    rotSensor.reset();

    brake_mode = brake_mode;

    catapult_motor.set_brake_mode(brake_mode);
}

void Catapult::reset() {
    while (
        // checks if catapult is NOT at the bottom
        (
            ((rotSensor.get_angle() / 100) < 355) 
            && ((rotSensor.get_angle() / 100) > 305)
        )
        // and, of course, if the driver wants the catapult to run...
        // guess we can't do anythin about that ¯\_(ツ)_/¯
        || cata_state)
    {
        // if catapult ain't at the bottom, let's move it there!
        catapult_motor.move(127);
    }
    
    catapult_motor.brake();
}

void Catapult::toggle_catapult() {
    // toggles the catapult... ikr who would've thought

    cata_state = !cata_state;
}

void Catapult::catapult_us_to_victory() {
    pros::lcd::print(0, "Rotation Sensor Value: %s", std::to_string(rotSensor.get_angle()));

    if (
        // checks if catapult is NOT at the bottom
        (
            ((rotSensor.get_angle() / 100) < 355) 
            && ((rotSensor.get_angle() / 100) > 305)
        ) 
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