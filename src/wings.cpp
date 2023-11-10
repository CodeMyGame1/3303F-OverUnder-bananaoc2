#include "main.h"
#include "robot.hpp"

Wings::Wings(char wing_piston_port, pros::Controller& controller) {
    controller = controller;

    wing_piston = new pros::ADIDigitalOut(wing_piston_port);
}

void Wings::wing_it() {
    // start of program
    if (!wings_reset) {
        wing_piston->set_value(0);

        wings_reset = true;
    }

    // toggle wing states
    /**
     * TODO: sometimes, the first time i press it, it doesn't detect
    */
    if (controller->get_digital_new_press(DIGITAL_L2)) {
        wings_enabled = !wings_enabled;

        wing_piston->set_value(wings_enabled);
    }
}

// void wings() {
//     // closes wings when the robot starts up
//     if (!wings_reset) {
//       wing.set_value(0);

//       wings_reset = true;
//     }

//     // toggles wing states
//     if (master.get_digital_new_press(DIGITAL_L2)) {
//       wings_enabled = !wings_enabled;

//       wing.set_value(wings_enabled);
//     }
// }