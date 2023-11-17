#include "main.h"

/**
 * TODO: verify port!
*/
pros::ADIDigitalOut blocker_piston('A');

// when piston fully extended, blocker is closed!
bool piston_enabled = true;
bool blocker_reset = false;

void block_da_opponents() {
    if (!blocker_reset) {
        blocker_piston.set_value(1);
        
        blocker_reset = true;
    }

    if (controller.get_digital_new_press(DIGITAL_L1)) {
        piston_enabled = !piston_enabled;

        blocker_piston.set_value(piston_enabled);
    }
}