// my SAVIOR: https://www.youtube.com/watch?v=qKy98Cbcltw

#include "main.h"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

/**
 * SOME COOL INFO:
 * 
 * - field: 12ft x 12ft
 *   - each tile: ~24in x 24in (23.622 x 23.622 in <- 600mm x 600mm)
 * 
 * - negative degrees is left; positive degrees is right! (relative to the front, I believe!)
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
    ez_chassis.set_pid_constants(&ez_chassis.forward_drivePID, 100, 5, 1, 0);
    ez_chassis.set_pid_constants(&ez_chassis.backward_drivePID, 0.45, 0, 5, 0);
    ez_chassis.set_pid_constants(&ez_chassis.turnPID, 5, 0.003, 35, 15);
    ez_chassis.set_pid_constants(&ez_chassis.swingPID, 7, 0, 45, 0);
}

void auton_reset() {
    ez_chassis.reset_pid_targets(); // Resets PID targets to 0
	ez_chassis.reset_gyro(); // Reset gyro position to 0
	ez_chassis.reset_drive_sensor(); // Reset drive sensors to 0
}

void test_auton() {
    // chassis.left_motors.move(127);
    // chassis.left_motors.move_absolute((24 / (3.14 * 3.25)), 127);
    // chassis.right_motors.move_absolute((24 / (3.14 * 3.25)), 127);

    // pros::delay(50000);
    
    // ez_chassis.set_drive_pid(48, 127);
    // ez_chassis.wait_drive();
    ez_chassis.set_drive_pid(12, 127);
    ez_chassis.wait_drive();
}

///
// Drive Example
///
void drive_example() {
    // The first parameter is target inches
    // The second parameter is max speed the robot will drive at
    // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
    // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


    ez_chassis.set_drive_pid(24, DRIVE_SPEED, true);
    ez_chassis.wait_drive();

    ez_chassis.set_drive_pid(-12, DRIVE_SPEED);
    ez_chassis.wait_drive();

    ez_chassis.set_drive_pid(-12, DRIVE_SPEED);
    ez_chassis.wait_drive();
}

// remember, INTAKE is in front!
/**
 * AUTON DESC:
 * - as per video in DMs (CURRENT ITERATION:) starts touching the matchload bar
 * - as per YouTube video: starts wherever the top-left robot in this starts: https://www.youtube.com/watch?v=bTMBQ_n-3PQ; the WHOLE square, not straddling two squares
 * 
 * INSPIRATION:
 * - https://www.youtube.com/watch?v=bTMBQ_n-3PQ
 * - the video that Shlok sent in DMs
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

void far_side() {
    intake.intake_motors.set_brake_modes(MOTOR_BRAKE_HOLD);

    intake.intake_the_award();
    ez_chassis.set_drive_pid(6, 50);
    ez_chassis.wait_drive();
    pros::delay(100);
    intake.break_the_award();

    ez_chassis.set_drive_pid(-34, 127);
    ez_chassis.wait_drive();
    ez_chassis.set_turn_pid(45, 127);
    ez_chassis.wait_drive();
    ez_chassis.set_drive_pid(-20, 127);
    pros::delay(150);
    wings.open();
    ez_chassis.wait_drive();
    ez_chassis.set_turn_pid(135, 127);
    ez_chassis.wait_drive();
    pros::delay(1000);
    wings.close();
    ez_chassis.set_turn_pid(70, 127);
    ez_chassis.wait_drive();
    ez_chassis.set_drive_pid(-25, 127);
    wings.close();
    ez_chassis.wait_drive();
    ez_chassis.set_drive_pid(15, 127);
    ez_chassis.wait_drive();
    ez_chassis.set_turn_pid(-95, 127);
    ez_chassis.wait_drive();
    intake.outtake_the_award();
    pros::delay(750);
    ez_chassis.set_drive_pid(25, 127);
    ez_chassis.wait_drive();
    ez_chassis.set_drive_pid(-15, 127);
    ez_chassis.wait_drive();
    intake.break_the_award();
}

void near_side() {
    
}

void risky_far_side() {
    // starts with the "back" touching the matchload bar, the intake facing directly toward the elevation bar
    pros::lcd::print(0, "starting risky far side auton");

    /**
     * MOVE: getting triball under elevation bar
    */

    // starts intake running CONTINUOUSLY!
    pros::lcd::print(0, "running intake");
    intake.intake_the_award();
    intake.intake_motors.set_brake_modes(MOTOR_BRAKE_HOLD);
    // moves robot directly under elevaton bar
    pros::lcd::print(0, "driving forward");
    ez_chassis.set_drive_pid(6, 50);
    ez_chassis.wait_drive();
    // pros::delay(210);
    // stops le intake
    pros::delay(100);
    intake.break_the_award();

    // works up until this point!

    /**
     * MOVE: get triball out of matchload bar
    */

    // moves robot so its tip is touching the matchload bar
    // should ideally be holding first intaked triball + pushing alliance (matchload) triball in front
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(-34, 127, true);
    ez_chassis.wait_drive();

    // turns clockwise in place, until the front of the robot is directed along the matchload bar, in the direction of the goal
    auton_reset();
    pros::lcd::print(0, "turning \"right\"");
    ez_chassis.set_turn_pid(145, 127);
    ez_chassis.wait_drive();

    // opens wings
    pros::lcd::print(0, "opening wings");
    wings.open();

    // outtakes intaked triball
    intake.outtake_the_award();
    pros::delay(1000);
    intake.break_the_award();

    // moves halfway up the matchload bar
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(14, 127, true);
    ez_chassis.wait_drive();

    auton_reset();

    // turns a LITTLE towards the goal
    pros::lcd::print(0, "turning \"left\"");
    ez_chassis.set_turn_pid(-65, 127);
    ez_chassis.wait_drive();

    auton_reset();

    // turns FULLY around
    ez_chassis.set_turn_pid(-150, 100);
    pros::delay(250);
    wings.close();
    ez_chassis.wait_drive();

    // wings.close();

    // furiously (?) scores into the goal
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(-20, 127);
    ez_chassis.wait_drive();

    // backs out of the goal a little 
    pros::lcd::print(0, "moving forward");
    ez_chassis.set_drive_pid(15, 127);
    ez_chassis.wait_drive();

    auton_reset();

    // turn a liiiitle right
    ez_chassis.set_turn_pid(20, 127);
    ez_chassis.wait_drive();

    // furiously (?) scores into the goal
    pros::lcd::print(0, "moving backward");
    ez_chassis.set_drive_pid(-20, 127);
    ez_chassis.wait_drive();

    // backs out of the goal a little 
    pros::lcd::print(0, "moving forward");
    ez_chassis.set_drive_pid(15, 127);
    ez_chassis.wait_drive();

    // auton_reset();

    //// NOT DOING THIS PART!
    // // turns around (intake now facing goal!)
    // pros::lcd::print(0, "do a barrel roll");
    // ez_chassis.set_turn_pid(180, 127);
    // ez_chassis.wait_drive();

    // // starts outtake running
    // pros::lcd::print(0, "waits to outtake");
    // intake.outtake_the_award();

    // // rams into the goal again to score triball
    // pros::lcd::print(0, "moving backward");
    // ez_chassis.set_drive_pid(10, 127);
    // ez_chassis.wait_drive();

    // // stops le intake
    // intake.break_the_award();

    // // backs out of the goal again
    // pros::lcd::print(0, "moving backward");
    // ez_chassis.set_drive_pid(-10, 127);
    // ez_chassis.wait_drive();

    // /**
    //  * MOVE: scoring TWO MORE TRIBALLS????
    // */

    // auton_reset();

    // // turns towards the FOURTH triball yeah babyy we're on a roll!! >:))
    // pros::lcd::print(0, "turning \"left\"");
    // ez_chassis.set_turn_pid(-75, 127);
    // ez_chassis.wait_drive();

    // // starts intake running
    // pros::lcd::print(0, "moving forward");
    // intake.intake_the_award();
    // // goes TOWARDS le fourth triball :>
    // ez_chassis.set_drive_pid(50, 127, true);
    // ez_chassis.wait_drive();
    // // stops le intake
    // intake.break_the_award();

    // auton_reset();

    // // turns around to face the goal DIAGONALLY
    // ez_chassis.set_turn_pid(140, 127);
    // ez_chassis.wait_drive();

    // // goes towards the goal a bit (but not enough to like accidentally intake the outtaked triball :grimacing:)
    // ez_chassis.set_drive_pid(16, 127, true);
    // ez_chassis.wait_drive();

    // // starts outtake running
    // intake.outtake_the_award();
    // // leeway for outtake to outtake
    // pros::delay(250);
    // // stops le outtake
    // intake.break_the_award();

    // auton_reset();

    // // turns around towards the FIFTH TRIBALL???
    // ez_chassis.set_turn_pid(-150, 127);
    // ez_chassis.wait_drive();

    // // works as intended up until this point

    // // starts intake
    // intake.intake_the_award();
    // // drives towards FIFTH TRIBALL!!!
    // ez_chassis.set_drive_pid(16, 108, true);
    // ez_chassis.wait_drive();
    // // leeway for intake to intake
    // pros::delay(250);
    // // stop le intake
    // intake.break_the_award();

    // auton_reset();

    // // turns around towards goal
    // ez_chassis.set_turn_pid(160, 108);
    // ez_chassis.wait_drive();

    // // open wings
    // wings.open();
    // // nyoom into goal
    // ez_chassis.set_drive_pid(36, 108, true);
    // ez_chassis.wait_drive();
    // // start outtaking
    // intake.outtake_the_award();
    // // leeway for outtake to outtake
    // pros::delay(250);
    // // stop le outtake
    // intake.break_the_award();

    intake.intake_motors.set_brake_modes(MOTOR_BRAKE_COAST);
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

/**
 * TODO:
 * - tune distances / angles
 * - tune delays
*/
void goal_side_two() {
    // move towards triball under elevation bar
    intake.intake_the_award();
    ez_chassis.set_drive_pid(3, 127);
    ez_chassis.wait_drive();
    pros::delay(250);
    // stops intake
    intake.break_the_award();

    // move towards matchload bar
    ez_chassis.set_drive_pid(-28, 127);
    ez_chassis.wait_drive();
    
    // turns left
    ez_chassis.set_turn_pid(-35, 108);
    ez_chassis.wait_drive();

    // opens wings
    wings.open();
    // moves along the length of matchload bar
    ez_chassis.set_drive_pid(-23, 127);
    ez_chassis.wait_drive();
    /**
     * TODO: see if the wings need to be closed
    */
    // closes wings
    wings.close();

    /**
     * TODO: verify this code is correct
    */
    // presumably turns towards goal
    ez_chassis.set_turn_pid(-85, 127);
    ez_chassis.wait_drive();

    // scores triball into goal
    ez_chassis.set_drive_pid(-15, 127);
    ez_chassis.wait_drive();

    // backs out of goal
    ez_chassis.set_drive_pid(12, 127);
    ez_chassis.wait_drive();

    /**
     * TODO: verify this code is correct
    */
    // presumably turns around
    ez_chassis.set_turn_pid(107, 127);
    ez_chassis.wait_drive();

    /**
     * TODO: is it possible for intake to outtake while moving in the direction of outtake?
    */
    // starts intake running
    intake.outtake_the_award();
    // runs into goal
    ez_chassis.set_drive_pid(15, 127);
    // waits for intake to outtake
    pros::delay(500);
    // stops intake
    intake.break_the_award();

    // backs out of goal
    ez_chassis.set_drive_pid(-15, 127);
    ez_chassis.wait_drive();

    // turns towards triball in center of field
    ez_chassis.set_turn_pid(-43, 127);
    ez_chassis.wait_drive();

    // starts intake running
    intake.intake_the_award();
    // goes towards triball in center of field
    ez_chassis.set_drive_pid(59, 127);
    ez_chassis.wait_drive();
    // wait for intake
    pros::delay(250);
    /**
     * TODO: verify this is correct
    */
    // presumably turns around
    ez_chassis.set_turn_pid(-180, 127);
    ez_chassis.wait_drive();

    // starts outtake running
    intake.outtake_the_award();
    // drives into goal
    ez_chassis.set_drive_pid(20, 127);
    ez_chassis.wait_drive();
    // waits for outtake to outtake
    pros::delay(1000);
    // drives out of goal
    ez_chassis.set_drive_pid(-10, 127);
    ez_chassis.wait_drive();
}