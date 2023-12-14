#include "main.h"
#include <string>

pros::Motor intake_motor(1);

Intake::Intake(int intake_port, pros::motor_brake_mode_e brake_mode) : intake_motor(intake_port) {
    brake_mode = brake_mode;
    
    intake_motor.set_brake_mode(brake_mode);
};

// runs WHEN controller.get_digital(DIGITAL_R1)
void Intake::intake_the_award() {
    intake_motor.move(-127);
}

// runs WHEN controller.get_digital(DIGITAL_R2)
void Intake::outtake_the_award() {
    intake_motor.move(127);
}

// runs WHEN controller.get_digital(DIGITAL_R1) / controller.get_digital(DIGITAL_R2) DEPRESSED
void Intake::break_the_award() {
    intake_motor.brake();
}