#include "main.h"

Intake::Intake(int intake_port, char intake_piston_port, pros::motor_brake_mode_e brake_mode, Robot& parent_robot) {
    robot = &parent_robot;

    intake_motor = new pros::Motor(intake_port);
    // most likely removing intake piston :> 
    intake_piston = new pros::ADIDigitalOut(intake_piston_port);

    brake_mode = brake_mode;
}

void Intake::intake_the_award() {
    // at the beginning of the program, `intake_reset` will be false; this field will run
    if (!intake_reset) {
        // set the intake motors' brake mode
        intake_motor->set_brake_mode(brake_mode);

        intake_piston->set_value(1);

        intake_reset = true;
    }

    // intake
    if (robot->controller.get_digital(DIGITAL_R1)) {
        intake_motor->move(-127);
    // outtake
    } else if (robot->controller.get_digital(DIGITAL_R2)) {
        intake_motor->move(127);
    } else { intake_motor->brake(); }
}