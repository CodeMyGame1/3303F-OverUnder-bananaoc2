// my SAVIOR: https://www.youtube.com/watch?v=qKy98Cbcltw

#include "main.h"
#include "autons.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

#define s DRIVE_SPEED

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
*/

/**
 * TODO: tune!
*/
// P: get where u wanna go
// I: GO FASTER (this increases exponentially so be careful with this term)
// D: slow down near the end

// move and turn functions because i dont want to type them out every single time i want to do something

void move(number target, int speed = s, bool wait = true, bool slew = false, bool heading = false) {
    ez_chassis.set_drive_pid(target, speed, slew, heading);

    if (wait) { ez_chassis.wait_drive(); }
}

void turn(number target, int speed = s, bool wait = true) {
    ez_chassis.set_turn_pid(target, speed);

    if (wait) { ez_chassis.wait_drive(); }
}

void lswing(number target, int speed = s, bool wait = true) {
    ez_chassis.set_swing_pid(LEFT_SWING, target, speed);

    if (wait) { ez_chassis.wait_drive(); }
}

void rswing(number target, int speed = s, bool wait = true) {
    ez_chassis.set_swing_pid(RIGHT_SWING, target, speed);

    if (wait) { ez_chassis.wait_drive(); }
}

void waitd() {
    ez_chassis.wait_drive();
}

void default_constants() {
    ez_chassis.set_slew_min_power(80, 80); // default
    ez_chassis.set_slew_distance(7, 7); // default
    ez_chassis.set_pid_constants(&ez_chassis.headingPID, 11, 0, 20, 0); // default, will need tuning if we keep drift drive
    ez_chassis.set_pid_constants(&ez_chassis.forward_drivePID, 0.48, 0.0025, 7, 0); // could be tuned to be a bit more snappy e.g. tuning kI
    ez_chassis.set_pid_constants(&ez_chassis.backward_drivePID, 0.48, 0.0025, 7, 0); // could be tuned to be a bit more snappy e.g. tuning kI
    ez_chassis.set_pid_constants(&ez_chassis.turnPID, 5, 0.003, 35, 15);// default
    ez_chassis.set_pid_constants(&ez_chassis.swingPID, 7, 0, 45, 0);// default
    ez_chassis.set_exit_condition(ez_chassis.drive_exit, 20, 50, 75, 150, 125, 500); // needs tuning, still pauses a considerable amount
}

void pid_test() { // test pid constants
    move(10.0);
    move(-10.0);
    turn(45);
    rswing(0);
}

void far_side() {
    wings.open();
    turn(45);
    move(18.5);
    turn(0);
    pros::delay(250);
    wings.close();
    turn(37.5);
    intake.extend_intake();
    move(30);
    turn(0);
    move(-15);
    intake.retract_intake();
}

void near_side() {
    wings.open();
    turn(-45);
    move(18.5);
    turn(0);
    pros::delay(250);
    wings.close();
    turn(43.5);
    intake.extend_intake();
    move(57.5); 
    intake.retract_intake();
    pros::delay(500);
    move(-57.5);
    turn(135);
    move(18.5);
    turn(90);
    intake.extend_intake();
    move(24);
}

void in_progress_far_side() { 
    // wings.open();
    intake.extend_intake();
    pros::delay(1000);
    //wings.close();
    move(24.0);
    turn(-32.5);
    move(39.0); 
    rswing(-90.0, s, true);
    move(10.0);
    pros::delay(150);
    intake.retract_intake();
    waitd();

    move(-5);
    turn(90.0);
    intake.extend_intake();
    // wings.open();
    move(25.0);
    pros::delay(100);
    move(-13.0);

    turn(225.);
    intake.extend_intake();
    move(25.);
    lswing(270.);
    pros::delay(100);
    intake.retract_intake();
    pros::delay(100);

    // move(-10);
    // turn(-135);
    // move(17);
    // wings.open();
    // turn(0);
    // turn(45);
    // wings.close();
    // intake.extend_intake();
    // move(-7);
    // turn(-90);
    // move(15);
    // pros::delay(100);
    // intake.retract_intake();
    // pros::delay(100);

    // move(-15);
    // turn(45);
    // move(17);
    // turn(0);
    // intake.extend_intake();
    // move(12);
    // move(-5);
    // move(5);
    // //goofyahh
    // move(6);
}