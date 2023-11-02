#pragma once

#include "main.h"

class Robot {
    public:
        Catapult* catapult;
        Chassis* chassis;
        Intake* intake;
        Wings* wings;

        pros::controller_digital_e_t* controller;
        
        Robot(Catapult* catapult, Chassis* chassis, Intake* intake, Wings* wings, pros::controller_digital_e_t controller);
};