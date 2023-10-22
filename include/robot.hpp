#pragma once

#include "main.h"

class Robot {
    public:
        Catapult catapult;
        Chassis chassis;
        Intake intake;
        Wings wings;
        
        Robot(Catapult& catapult, Chassis& chassis, Intake& intake, Wings& wings);
};