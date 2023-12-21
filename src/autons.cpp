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
 * - https://github.com/EZ-Robotics/EZ-Template/blob/v2.2.0/src/autons.cpp
 * 
 * MODELING AUTON OFF OF:
 * - https://www.youtube.com/watch?v=bTMBQ_n-3PQ
*/

/**
 * TODO: tune!
*/
// P: get where u wanna go
// I: GO FASTER
// D: slow down near the end

void default_constants() {
    ez_chassis.set_slew_min_power(80, 80);
    ez_chassis.set_slew_distance(7, 7);
    ez_chassis.set_pid_constants(&ez_chassis.headingPID, 11, 0, 20, 0);
    ez_chassis.set_pid_constants(&ez_chassis.forward_drivePID, .5, 5, 1, 0);
    ez_chassis.set_pid_constants(&ez_chassis.backward_drivePID, 0.45, 0, 5, 0);
    ez_chassis.set_pid_constants(&ez_chassis.turnPID, 5, 0.003, 35, 15);
    ez_chassis.set_pid_constants(&ez_chassis.swingPID, 7, 0, 45, 0);
}

void test_auton() {
    ez_chassis.set_drive_pid(25, 127);
    ez_chassis.wait_drive();
}

// remember, INTAKE is in front!
/**
 * AUTON DESC:
 * - starts wherever the top-left robot in this starts: https://www.youtube.com/watch?v=bTMBQ_n-3PQ; the WHOLE square, not straddling two squares
 * 
 * RISKS:
 * - could cross over the middle barrier
 * - tends towards being a risky auton by itself lel
 * 
 * REQUIREMENTS:
 * - matchload triball!!!
 * 
 * for all `set_drive_pid()` calls, keep in mind slew_min and slew_distance!
 * 
 * TODO: 
 * - TUNE!
 *   - tune speeds
 *   - tune distances / angles
 *   - figure out what needs slew and what doesn't
 * - IMPLEMENT INTAKE AND SHTUFF
 *   - figure out how we're going to get the triball out of the matchload zone
 * - is the wait for intake (pros::delay) too long?
 * - take into account field variances / uncertainties!
*/
void main_auton(Catapult catapult, Intake intake, Wings wings) {
    pros::lcd::print(0, "starting main auton");

    /**
     * MOVE: getting triball under elevation bar
    */
    
    // starts intake running CONTINUOUSLY! IMPORTANT!
    pros::lcd::print(0, "running intake");
    intake.intake_the_award();
    // moves robot directly under elevation bar
    pros::lcd::print(0, "driving forward");
    ez_chassis.set_drive_pid(12, 80);
    ez_chassis.wait_drive();
    // leeway in case the triball is not picked up by intake yet
    pros::lcd::print(0, "waiting to intake");
    pros::delay(250);
    // stops le intake
    intake.break_the_award();

    /**
     * MOVE: get triball out of matchload bar
    */
    // moves robot so its tip is touching the matchload bar
    // should ideally be holding first intaked triball + pushing alliance (matchload) triball in front
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(-42, 80, true);
    ez_chassis.wait_drive();

    /**
     * TODO: does this turn LEFT or RIGHT...?
    */
    pros::lcd::print(0, "turning \"left\"");
    ez_chassis.set_turn_pid(30, -80);
    ez_chassis.wait_drive();

    // opens wings
    pros::lcd::print(0, "opening wings");
    wings.wing_it();
    // leeway for wings to open (let's hope there's enough air in the reservoir [air tank]!)
    pros::delay(250);

    // moves fully up the matchload bar, hopefully (?) getting the matchload zone triball OUTTA THERE
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(-30, 80, true);
    ez_chassis.wait_drive();

    // turns a LITTLE towards the goal
    pros::lcd::print(0, "turning \"left\"");
    ez_chassis.set_turn_pid(30, -80);
    ez_chassis.wait_drive();


    /**
     * MOVE: scoring 3 triballs!!!
    */

    // furiously (?) scores into the goal
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(-12, 127);
    ez_chassis.wait_drive();

    // backs out of the goal a little 
    pros::lcd::print(0, "moving forward");
    ez_chassis.set_drive_pid(10, 108);
    ez_chassis.wait_drive();

    // turns around (intake now facing goal!)
    pros::lcd::print(0, "do a barrel roll");
    ez_chassis.set_turn_pid(180, 127);
    ez_chassis.wait_drive();

    // scores into the goal again
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(10, 108);
    ez_chassis.wait_drive();
    // starts outtake running
    pros::lcd::print(0, "waits to outtake");
    intake.outtake_the_award();
    // leeway for intake to outtake (quite the oxymoron, isn't it?)
    pros::delay(250);
    // stops le intake
    intake.break_the_award();

    
    /**
     * MOVE: scoring TWO MORE TRIBALLS????
    */

    // backs out of the goal again
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(-10, 108);
    ez_chassis.wait_drive();

    // turns towards the FOURTH triball yeah babyy we're on a roll!! >:))
    pros::lcd::print(0, "turning \"left\"");
    ez_chassis.set_turn_pid(75, 108);
    ez_chassis.wait_drive();

    // starts intake running
    pros::lcd::print(0, "moving forward");
    intake.intake_the_award();
    // goes TOWARDS le fourth triball :>
    ez_chassis.set_drive_pid(50, 108, true);
    ez_chassis.wait_drive();
    // leeway for intake to intake
    pros::lcd::print(0, "waiting to intake");
    pros::delay(250);
    // stops le intake
    intake.break_the_award();

    // turns around to face the goal DIAGONALLY
    ez_chassis.set_turn_pid(140, 108);
    ez_chassis.wait_drive();

    // starts outtake running
    intake.outtake_the_award();
    // leeway for outtake to outtake
    pros::delay(250);
    // stops le outtake
    intake.outtake_the_award();

    // goes towards the goal a bit (but not enough to like accidentally intake the outtaked triball :grimacing:)
    ez_chassis.set_drive_pid(16, 108, true);
    ez_chassis.wait_drive();

    // turns around towards the FIFTH TRIBALL???
    ez_chassis.set_turn_pid(100, -108);
    ez_chassis.wait_drive();

    // starts intake
    intake.intake_the_award();
    // drives towards FIFTH TRIBALL!!!
    ez_chassis.set_drive_pid(16, 108, true);
    ez_chassis.wait_drive();
    // leeway for intake to intake
    pros::delay(250);
    // stop le intake
    intake.break_the_award();

    // turns around towards goal
    ez_chassis.set_turn_pid(160, 108);
    ez_chassis.wait_drive();

    // open wings
    wings.open();
    // nyoom into goal
    ez_chassis.set_drive_pid(36, 108, true);
    ez_chassis.wait_drive();
    // start outtaking
    intake.outtake_the_award();
    // leeway for outtake to outtake
    pros::delay(250);
    // stop le outtake
    intake.break_the_award();

    // ... and that's the end of the risky, risky five-ball (possibly six if chaos unfolds) AUTON!
// 18
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