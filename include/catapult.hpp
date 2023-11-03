#pragma once

#include "main.h"

class Catapult {
    public:
        pros::Motor* catapult_motor;
        
        // pulling back negative; throwing forward positive
        pros::Rotation* rotSensor;

        pros::motor_brake_mode_e brake_mode;

        // the parent "robot" class
        Robot* robot;

        // also known as "istherotationsensortared"
        bool cata_reset = false;
        // the catapult starts by n o t  m o v i n g
        bool cata_state = false;

        Catapult(int pros_motor_port, int rot_sensor_port, pros::motor_brake_mode_e brake_mode, Robot& parent_robot);

        void catapult_us_to_victory();
};