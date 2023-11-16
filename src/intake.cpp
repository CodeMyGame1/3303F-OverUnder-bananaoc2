#include "main.h"
// #include "robot.hpp"

pros::Motor intake_motor(1);
/**
 * TODO: verify intake piston port
*/
pros::ADIDigitalOut intake_piston('C');

bool intake_piston_enabled = false;
bool intake_reset = false;

void intake_the_award() {
    // at the beginning of the program, `intake_reset` will be false; this field will run
    if (!intake_reset) {
        // set the intake motors' brake mode
        intake_motor.set_brake_mode(MOTOR_BRAKE_HOLD);

        intake_piston.set_value(1);

        intake_reset = true;
    }

    // intake
    if (controller.get_digital(DIGITAL_R1)) {
        intake_motor.move(-127);
    // outtake
    } else if (controller.get_digital(DIGITAL_R2)) {
        intake_motor.move(127);
    } else { intake_motor.brake(); }
}