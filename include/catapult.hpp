#pragma once

#include "main.h"
#include "robot.hpp"

class Catapult {
    public:
        pros::Motor* catapult_motor;
        
        // pulling back negative; throwing forward positive
        pros::Rotation* rotSensor;

        pros::motor_brake_mode_e brake_mode;

        // a reference to the controller of the robot
        pros::Controller* controller;

        // also known as "istherotationsensortared"
        bool cata_reset = false;
        // the catapult starts by n o t  m o v i n g
        bool cata_state = false;

        Catapult(int pros_motor_port, int rot_sensor_port, pros::motor_brake_mode_e brake_mode, pros::Controller& parent_robot);

        void catapult_us_to_victory();
};