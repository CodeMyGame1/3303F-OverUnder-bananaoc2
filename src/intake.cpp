#include "main.h"
#include <string>

Intake::Intake(std::vector<pros::Motor> motor_ports, pros::motor_brake_mode_e brake_mode) : intake_motors(motor_ports) {
    brake_mode = brake_mode;
};

// runs WHEN controller.get_digital(DIGITAL_R1)
void Intake::intake_the_award() {
    intake_motors.move(127);
}

// runs WHEN controller.get_digital(DIGITAL_R2)
/**
 * verify if this runs correctly
*/
void Intake::outtake_the_award() {
    intake_motors.move(-127);
}

// runs WHEN controller.get_digital(DIGITAL_R1) / controller.get_digital(DIGITAL_R2) DEPRESSED
void Intake::break_the_award() {
    intake_motors.brake();
}