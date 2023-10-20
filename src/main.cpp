#include "main.h"

/**
 * TODO: make it and I OOP!!!!!
 * TODO: add PID!
 * TODO: add autons!
 * TODO: add odometry!
*/ 

/**
 * At A Glance:
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

// defining all our lovely classes :>
/**
 * TODO: make intake class as an instance under this; rename "Chassis" to "Robot" class :>
*/
Chassis chassis ({5, -10}, {-9, 7}, MOTOR_BRAKE_COAST);
Intake intake (6, 'C', MOTOR_BRAKE_HOLD);
Wings wings ('A');
/**
 * TODO: add catapult motor port
*/
Catapult catapult (0, 20, MOTOR_BRAKE_HOLD);

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
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	// i honestly have no idea why i'm even doing this...
	chassis.set_controller(pros::E_CONTROLLER_MASTER);
	intake.set_controller(pros::E_CONTROLLER_MASTER);
	wings.set_controller(pros::E_CONTROLLER_MASTER);
	catapult.set_controller(pros::E_CONTROLLER_MASTER);

	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {
		// currently hard-coded to run tank drive!
		chassis.drive();

		// all our lovely other functions!
		wings.wing_it();
		intake.intake_the_award();
		catapult.catapult_us_to_victory();

		pros::delay(10);
	}
}
