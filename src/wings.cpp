#include "main.h"

// haha so "left" and "right" are relative to the front of the robot being the intake :clown:

Wings::Wings(std::uint8_t l_wing_port, std::uint8_t r_wing_port) {
    
}

pros::ADIDigitalOut left_wing('B');
pros::ADIDigitalOut right_wing('C');

bool wings_enabled = false;
bool wings_reset = false;

void wing_it() {
    // start of program
    if (!wings_reset) {
        left_wing.set_value(0);
        right_wing.set_value(0);

        wings_reset = true;
    }

    // toggle wing states
    /**
     * TODO: sometimes, the first time i press it, it doesn't detect
    */
    if (controller.get_digital_new_press(DIGITAL_L2)) {
        wings_enabled = !wings_enabled;

        left_wing.set_value(wings_enabled);
        right_wing.set_value(wings_enabled);
    }
}