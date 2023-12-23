/**
 * NOT IN USE RIGHT NOW
*/

#pragma once

#include "main.h"
// #include "robot.hpp"

class Catapult {
    public:
        pros::Motor catapult_motor;
        pros::Rotation rotSensor;

        bool cata_state = false;

        Catapult(int cata_port, int rot_port, pros::motor_brake_mode_e brake_mode);

        int get_formatted_angle();

        void reset();

        void toggle_catapult();

        void catapult_us_to_victory();
};