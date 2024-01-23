// my SAVIOR: https://www.youtube.com/watch?v=qKy98Cbcltw

#include "main.h"
#include "autons.hpp"

const int DRIVE_SPEED = 117; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.

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

void waitd() {
    ez_chassis.wait_drive();
}

void move(double target, int speed = s, bool wait = true, bool slew = true, bool heading = true) {
    ez_chassis.set_drive_pid(target, speed, slew, heading);

    if (wait) { waitd(); }
}

void turn(double target, int speed = s, bool wait = true) {
    ez_chassis.set_turn_pid(target, speed);

    if (wait) { waitd(); }
}

void lswing(double target, int speed = s, bool wait = true) {
    ez_chassis.set_swing_pid(LEFT_SWING, target, speed);

    if (wait) { waitd(); }
}

void rswing(double target, int speed = s, bool wait = true) {
    ez_chassis.set_swing_pid(RIGHT_SWING, target, speed);

    if (wait) { waitd(); }
}

void default_constants() {
    ez_chassis.set_slew_min_power(80, 80); // default
    ez_chassis.set_slew_distance(7, 7); // default
    ez_chassis.set_pid_constants(&ez_chassis.headingPID, 11, 0, 20, 0); // default, will need tuning if we keep drift drive
    ez_chassis.set_pid_constants(&ez_chassis.forward_drivePID, 0.47, 0.0025, 7.15, 0); // could be tuned to be a bit more snappy e.g. tuning kI
    ez_chassis.set_pid_constants(&ez_chassis.backward_drivePID, 0.47, 0.0025, 7, 0); // could be tuned to be a bit more snappy e.g. tuning kI
    ez_chassis.set_pid_constants(&ez_chassis.turnPID, 5, 0.003, 35, 15);// default
    ez_chassis.set_pid_constants(&ez_chassis.swingPID, 7, 0, 45, 0);// default
    ez_chassis.set_exit_condition(ez_chassis.drive_exit, 25,  75, 150, 175, 250, 150); // needs tuning, still pauses a considerable amount
    ez_chassis.set_exit_condition(ez_chassis.turn_exit,  90, 3,  500, 7, 500, 500);
    ez_chassis.set_exit_condition(ez_chassis.swing_exit,  90, 3,  500, 7, 500, 500);
}

void pid_test() { // test pid constants
    move(10.0);
    move(-10.0);
    turn(45);
    rswing(0);
}

// moves bot backwards, straight into goal
void push() {
    move(-34.);
}

void blank() {}

void far_side() { 
    // Far side auton
    // 1. bump alliance triball matchload towards goal
    // 2. rush middle triball
    // 3. drop in front of goal
    // 4. turn around and grab other middle triball
    // 5. turn around and score both middle triballs into goal
    // 6. grab side middle triball
    // 7. drop to side entrance of goal
    // 8. drive into alley and grab alley triball
    // 9. kick out triball in matchload zone
    // 10. score matchload triball, matchload zone triball, side middle triball
    // 11. turn around and score alley triball in intake
    // 12. drive into alley and touch horizontal bar with zipties on intake

    wings.open();
    intake.extend_intake();
    pros::delay(100);
    wings.close();
    move(24.0);
    turn(-15);
    move(35.);
    intake.retract_intake();
    pros::delay(50);
    turn(90);
    pros::delay(50);
    intake.extend_intake();
    pros::delay(50);
    move(10.);
    move(-15.);
    turn(-72.5);
    move(15.);
    intake.retract_intake();
    pros::delay(50);

    move(-5.);
    turn(90);
    // wings.open();
    intake.extend_intake();
    move(35.);

    move(-15.);
    turn(225.);
    intake.extend_intake();
    move(23.);
    lswing(270.);
    intake.retract_intake();
    pros::delay(50);

    move(-26.);
    turn(135., s, false);
    pros::delay(75);
    intake.extend_intake();
    waitd();
    pros::delay(50);

    turn(180);
    move(40.);
    turn(270.);

    move(30.);
    pros::delay(50);
    intake.retract_intake();
    pros::delay(50);

    turn(270);
    move(-40.);
    lswing(235);
    wings.open();
    move(-25.);
    turn(150);
    wings.close();
    turn(180);
    move(-17.);
    move(17.);
    turn(0);
    intake.extend_intake();
    pros::delay(50);
    move(19.);
    move(-15.);

    turn(235);
    move(25.);
    turn(270);
    move(30);
    intake.extend_intake();
}

void near_side() {
    // Near side auton
    // 1. bump alliance triball matchload towards goal
    // 2. rush middle triball
    // 3. drop to alley
    // 4. kick out triball in matchload zone into alley
    // 5. score alliance triball matchload
    // 6. drive back to alley and push triballs to other side
    // 7. touch horizontal bar with zipties on intake

    wings.open();
    intake.extend_intake();
    pros::delay(100);
    wings.close();
    move(24.0);
    turn(15);
    move(35.);
    intake.retract_intake();
    pros::delay(50);
    move(-35.);
    turn(0);
    move(-21.);
    wings.open();
    turn(-135);
    pros::delay(50);
    wings.close();
    rswing(-90);
    turn(90);
    pros::delay(50);
    intake.extend_intake();
    turn(135);
    move(-25.);
    turn(180);
    move(-15.);
    move(15.);
    turn(135);
    move(25.);
    turn(90);
    move(30.);
}
