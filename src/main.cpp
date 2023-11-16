#include "main.h"
// #include "robot.hpp"

/**
 * TODO: do i have to include `#pragma once` in the header files?
*/

/**
 * TODO: see if you can do PID/odometry/autons without LemLib!
*/

/**
 * At A Glance:
 * 
 * FINAL CHECKLIST:
 * - ENSURE the robot is STATIONARY when you're starting the program; it needs to calibrate!
 * 
 * OTHER NOTES:
 * - currently not using `include/PID.hpp`; `include/robot.hpp`; `src/PID.cpp`; and `src/robot.cpp`
 * 
 * Motors -- total: 88W (limit):
 * - 4 MAIN drivetrain motors (L: {-1, -4}; P: {3, 2})
 *   - blue (600rpm)
 *   - 36:1 gear ratio
 *   - (11W * 4 motors = 44W)
 * - 2 pairs of big and small cata motors (DRIVETRAIN: L: {5, -10}; R: {-9, 7}; TBD CATA)
 *   - big motors
 *     - <one of the colors of the rainbow> (200rpm)
 *     - 8:1 gear ratio
 *     - (11W * 2 motors = 22W)
 *   - small motors
 *     - <one of the colors of the rainbow> (200rpm)
 *     - 8:1 gear ratio
 *     - (5.5W * 2 motors = 11W)
 * - 1 intake motor (P: 6)
 *   - green (200rpm)
 *   - 1:3 gear ratio 
 *   - (11W * 1 motor = 11W)
 * 
 * Sensors:
 * - Rotational Sensor (P: 20)
 * - Inertial Motion Sensor (P: 11)
 * 
 * Cwontrils:
 * - DRIVING: (tank drive) left and right joysticks (y-axis only)
 * - WINGS: L2
 * - INTAKE: R1 intake, R2 outtake
 * - PTO: X
 
 * analog:
 * - A: Wing Pistons (both of them!)
 * - B: Catapult Pistons (both of them!)
 * - C: Intake Piston
*/

pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Robot robot (
// 	0, 
// 	20, 
// 	MOTOR_BRAKE_HOLD
// );

/**
 * DRIVETRAIN: INDIVIDUAL PORTS
 * TODO: set ports; left motors SHOULD be reversed!
*/
// L
pros::Motor left_drive_front_motor(5);
pros::Motor left_drive_middle_motor(-4);
pros::Motor left_drive_back_motor(3);

// R
pros::Motor right_drive_front_motor(8);
pros::Motor right_drive_middle_motor(-9);
pros::Motor right_drive_back_motor(10);


/**
 * DRIVETRAIN: MOTOR GROUPS
*/
pros::Motor_Group left_drive({
	left_drive_front_motor, left_drive_middle_motor, left_drive_back_motor
});
pros::Motor_Group right_drive({
	right_drive_front_motor, right_drive_middle_motor, right_drive_back_motor
});

/**
 * SENSORS
 * TODO: set ports!
// */
// pros::Imu inertial_sensor(0);

/**
 * LEMLIB
*/

lemlib::Drivetrain_t drivetrain {
	// ADDRESS POINTING TO left drivetrain motor group
	&left_drive,
	// ADDRESS POINTING TO right drivetrain motors
	&right_drive,
	// robot width (NOT INCLUDING EXTENDED WINGS!)
	15.0625, // should be able to approximate this to 15", but we :sparkles: love :sparkles: being exact
	// wheel diameter
	3.25,
	// wheel rpm
	// (NOTE: gear ratio = output : input = 60 : 36 ~ 1.667 => 360 rpm)
	360
};

lemlib::OdomSensors_t sensors {
	nullptr, // vertical (forward) tracking wheel 1
	nullptr, // vertical (forward) tracking wheel 2
	nullptr, // horizontal (sideways) tracking wheel 1
	nullptr, // horizontal (sideways) tracking wheel 2
	nullptr // inertial motion unit
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis auton_chassis(drivetrain, lateralController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	/**
	 * TODO: pros::delay for legacy ports configuring?
	*/

	// WILL TAKE 3 SECONDS TO CALIBRATE; ENSURE ROBOT IS STATIONARY!
	auton_chassis.calibrate();

	pros::lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while (true) {
		// currently hard-coded to run tank drive!
		drive();

		// all our lovely other functions!
		// wing_it();
		intake_the_award();
		// catapult_us_to_victory();

		pros::delay(10);
	}
}
