#include "main.h"

/**
 * SOME COOL INFO:
 * 
 * - field: 12ft x 12ft
 *   - each tile: ~24in x 24in (23.622 x 23.622 in <- 600mm x 600mm)
 * 
 * 
 * USEFUL LINKS:
 * - https://ez-robotics.github.io/EZ-Template/docs/auton_functions/
 * - https://vr.vex.com/
 * - https://www.vexrobotics.com/over-under-manual
 * - https://kb.vex.com/hc/en-us/articles/15549324090772-Understanding-the-VRC-Over-Under-Field-Layout
*/

/**
 * TODO: tune!
*/
void default_constants() {
    ez_chassis.set_slew_min_power(80, 80);
    ez_chassis.set_slew_distance(7, 7);
    ez_chassis.set_pid_constants(&ez_chassis.headingPID, 11, 0, 20, 0);
    ez_chassis.set_pid_constants(&ez_chassis.forward_drivePID, 0.45, 0, 5, 0);
    ez_chassis.set_pid_constants(&ez_chassis.backward_drivePID, 0.45, 0, 5, 0);
    ez_chassis.set_pid_constants(&ez_chassis.turnPID, 5, 0.003, 35, 15);
    ez_chassis.set_pid_constants(&ez_chassis.swingPID, 7, 0, 45, 0);
}

void main_auton(Intake intake) {
    intake.intake_the_award();
    
}

// model auton:

// void main_auton(pros::Motor_Group left_motors, pros::Motor_Group right_motors) {
//     intake.move(-127);
//     chassis.moveTo(-4, 60, 500);
// 	pros::delay(500);
//     intake.brake();

//     chassis.moveTo(-34, 60, 1000);
//     //left_wing.set_value(1);
//     chassis.turnTo(-60, 50, 500, true);
//     chassis.moveTo(-62, 16, 1500);

//     chassis.moveTo(-60, 35, 500);
//     chassis.turnTo(-60, 16, 1000, false);
//     intake.move(127);
//     chassis.moveTo(-60, 16, 1500);

// 	chassis.moveTo(-60, 25, 1000);
// 	chassis.turnTo(-10, 36, 1000);
// 	chassis.moveTo(-75, 36, 500);

// 	chassis.setPose(-60, 36, 90);

//     // chassis.moveTo(-47, 43, 500);
// 	chassis.moveTo(-24, 35, 2000);
// 	chassis.moveTo(-16, 30, 1000);

//     intake.move(-127);
//     chassis.moveTo(-9, 15, 2000);
// 	chassis.moveTo(-20, 12, 1000);
//     pros::delay(500);

//     chassis.moveTo(-12, 0, 1000);
//     intake.move(-127);
//     chassis.moveTo(-9, 0, 2500, 100.0);
//     pros::delay(250);
//     intake.brake();

//     chassis.turnTo(-60, 5, 1000);
//     //left_wing.set_value(1);
//     //right_wing.set_value(1);
//     chassis.moveTo(-60, 5, 2000);
// 	pros::delay(1000);

// 	chassis.moveTo(0, 5, 2000);
// 	chassis.setPose(-10, 5, -90);
// 	chassis.moveTo(-47, 47, 100);
// 	chassis.turnTo(-9, 65, 1000);
// 	chassis.moveTo(-9, 65, 1000);
// }