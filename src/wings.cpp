#include "main.h"
// #include "robot.hpp"

/**
 * TODO: verify that port!
*/
pros::ADIDigitalOut wing_piston('A');

bool wings_enabled = true;
bool wings_reset = false;

void wing_it() {
    // start of program
    if (!wings_reset) {
        wing_piston.set_value(0);

        wings_reset = true;
    }

    // toggle wing states
    /**
     * TODO: sometimes, the first time i press it, it doesn't detect
    */
    if (controller.get_digital_new_press(DIGITAL_L2)) {
        wings_enabled = !wings_enabled;

        wing_piston.set_value(wings_enabled);
    }
}