#include "main.h"

Robot::Robot(Catapult* catapult_copy, Chassis* chassis_copy, Intake* intake_copy, Wings* wings_copy, pros::controller_digital_e_t controller) {
    catapult = catapult_copy;
    chassis = chassis_copy;
    intake = intake_copy;
    wings = wings_copy;

    controller = controller;

    // catapult->set_controller(controller);
    // chassis->set_controller(controller);
    // intake->set_controller(controller);

};