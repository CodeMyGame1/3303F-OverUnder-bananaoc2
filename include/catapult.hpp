#pragma once

#include "main.h"

class Catapult {
    public:
        pros::Motor* catapult_motor;
        pros::Controller* master;
        
        // pulling back negative; throwing forward positive
        pros::Rotation* rotSensor;

        pros::motor_brake_mode_e brake_mode;

        bool cata_reset = false;

        Catapult(int pros_motor_port, int rot_sensor_port, pros::motor_brake_mode_e brake_mode);

        void set_controller(pros::controller_id_e_t controller);

        void catapult_us_to_victory();
};