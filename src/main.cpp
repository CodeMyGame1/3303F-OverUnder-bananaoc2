/**
 * MAIN TODO: 
 * - address all other TODOs
 * - see if you can do PID/odometry/autons without LemLib!
*/


#include "main.h"
#include "EZ-Template/api.hpp"
// #include "robot.hpp"

/**
 * TODO: At A Glance housekeeping
 * - add gear ratio for catapult
*/
/**
 * AT A GLANCE:
 * 
 * NOTE: just as general advice, most of the code / documentation here
 * is organized in alphabetical order :P
 * 
 *  
 * OPNOTES:
 * - GAME:
 *   - ENSURE the robot is STATIONARY when you're starting the program; it needs to calibrate!
 * - the blocker requires one press before it like actually starts functioning so take that into account
 *
 * - PREP CHECKLIST:
 *   - AIR: fill the robot with air!
 *     - while filling the robot with air, at around ~70-80 PSI, the blocker WILL come down, so take caution ^-^
 *   - BATTERY: make sure the battery is full!
 * 
 * 
 * ROBOT SPECS:
 * - the front of the robot is the INTAKE
 * 
 * 
 * BLOCKER:
 * - PORT: 'A' as in Apple
 * - SPECS:
 *   - watch out it go nyoom nyoom (for legal reasons this is a joke)
 * 
 * 
 * CATAPULT:
 * - PORTS:
 *   - MOTOR: 20
 *   - ROTATION SENSOR: 12
 * - SPECS:
 *   - CARTRIDGE: 100rpm (red)
 *   - GEAR RATIO: <gear ratio here>
 *   - BRAKE MODE: HOLD
 * 
 * 
 * DRIVETRAIN: (11W * 6 motors = 66W) 
 * - PORTS:
 *   - LEFT:
 *     - front: -5
 *     - middle: -4
 *     - back: -3
 *   - RIGHT: 
 *     - front: 8
 *     - middle: 9
 *     - back: 10
 * - SPECS:
 *   - CARTRIDGE: 600rpm (blue)
 *   - GEAR RATIO: 36 : 1
 *   - BRAKE MODE: COAST
 * 
 * 
 * IMU:
 * - PORT: 17
 * 
 * 
 * INTAKE:
 * - PORT: 1
 * - SPECS:
 *   - CARTRIDGE: 200rpm (green)
 *   - GEAR RATIO: <gear ratio here>
 *   - BRAKE MODE: HOLD
 * 
 * 
 * WINGS:
 * - PORTS:
 *   - LEFT: 'B'
 *   - RIGHT: 'C'
 * - SPECS:
 *   - watch out it go boom boom (for legal reasons this is a joke)
 * 
 * 
 * Cwontrils:
 * - DRIVING: (tank drive) left and right joysticks (y-axis only)
 * - BLOCKER: (toggle; switches between open/close) L1
 * - CATAPULT: (toggle; runs continuously) A
 * - WINGS: (toggle; switches between open/close) L2
 * - INTAKE: (hold to run continuously) 
 *   - INTAKE: R1
 *   - OUTTAKE: R2
 
 * analog:
 * - A: Wing Pistons (both of them!)
 * - B: Catapult Pistons (both of them!)
 * - C: Intake Piston
*/

// from `util.cpp`~
pros::Controller controller(pros::E_CONTROLLER_MASTER);

/**
 * DRIVETRAIN: INDIVIDUAL MOTORS
*/

// L
pros::Motor lf_motor(-5);
pros::Motor lm_motor(-4);
pros::Motor lb_motor(-3);

// R
pros::Motor rf_motor(8);
pros::Motor rm_motor(9);
pros::Motor rb_motor(10);

/**
 * DRIVETRAIN: MOTOR GROUPS
*/
pros::Motor_Group left_drive({
	lf_motor, lm_motor, lb_motor
});
pros::Motor_Group right_drive({
	rf_motor, rm_motor, rb_motor
});

// /**
//  * TODO: set ports!
// */
// pros::Imu inertial_sensor(0);

// /**
//  * START: LEMLIB
// */

// lemlib::Drivetrain_t drivetrain {
// 	// ADDRESS POINTING TO left drivetrain motor group
// 	&left_drive,
// 	// ADDRESS POINTING TO right drivetrain motors
// 	&right_drive,
// 	// robot width (NOT INCLUDING EXTENDED WINGS!)
// 	15.0625, // should be able to approximate this to 15", but we :sparkles: love :sparkles: being exact
// 	// wheel diameter
// 	3.25,
// 	// wheel rpm
// 	// (NOTE: gear ratio = output : input = 60 : 36 ~ 1.667 => 360 rpm)
// 	360
// };

// lemlib::OdomSensors_t sensors {
// 	nullptr, // vertical (forward) tracking wheel 1
// 	nullptr, // vertical (forward) tracking wheel 2
// 	nullptr, // horizontal (sideways) tracking wheel 1
// 	nullptr, // horizontal (sideways) tracking wheel 2
// 	nullptr // inertial motion unit
// };

// // forward/backward PID
// lemlib::ChassisController_t lateralController {
//     8, // kP
//     30, // kD
//     1, // smallErrorRange
//     100, // smallErrorTimeout
//     3, // largeErrorRange
//     500, // largeErrorTimeout
//     5 // slew rate
// };
 
// // turning PID
// lemlib::ChassisController_t angularController {
//     4, // kP
//     40, // kD
//     1, // smallErrorRange
//     100, // smallErrorTimeout
//     3, // largeErrorRange
//     500, // largeErrorTimeout
//     0 // slew rate
// };

// lemlib::Chassis auton_chassis(drivetrain, lateralController, angularController, sensors);

// /**
//  * END: LEMLIB
// */


/**
 * START: EZTEMPLATE
*/

Drive ez_chassis (
	// left chassis ports
	{ -5, -4, -3 }
	
	// right chassis ports
	,{ 8, 9, 10 }

	/**
	 * TODO: find, install, and check port number of IMU!
	*/
	// IMU port
	,0

	// wheel diameter
	,3.25

	/**
	 * TODO: verify!,
	*/
	// cartridge rpm
	,600

	// gear ratio
	,(60 / 36) // ~ 1.667

	// <not using tracking wheels lel>
	// Uncomment if using tracking wheels
	/*
	// left tracking wheel ports
	// ,{1, 2} // 3 wire encoder
	// ,8 // Rotation sensor

	// right tracking wheel ports
	// ,{-3, -4} // 3 wire encoder
	// ,-9 // Rotation sensor
	*/

	// Uncomment if tracking wheels are plugged into a 3 wire expander
	// 3 Wire Port Expander Smart Port
	// ,1
);

/**
 * END: EZ TEMPLATE
*/


/**
 * START: ROBOT COMPONENT INITIALIZATION
*/

Blocker blocker = Blocker(
	'A'
);
Catapult catapult = Catapult(
	20,
	12,
	pros::E_MOTOR_BRAKE_HOLD
);
Chassis chassis = Chassis(
	{lf_motor, lm_motor, lb_motor},
	{rf_motor, rm_motor, rb_motor},
	pros::E_MOTOR_BRAKE_COAST
);
Intake intake = Intake( 
	1, // intake port
	pros::E_MOTOR_BRAKE_HOLD
);
Wings wings = Wings(
	'B',
	'C'
);

/**
 * END: ROBOT COMPONENT INITIALIZATION
*/



/**
 * ROBOTINIT: DESCRIPTION
 * 
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	/**
	 * TODO: pros::delay for legacy ports configuring?
	*/

	/**
	 * TODO: consider autonomous selector?
	*/
	// Autonomous Selector using LLEMU
	// ez::as::auton_selector.add_autons({
	// 	Auton("Example Drive\n\nDrive forward and come back.", drive_example),
	// 	Auton("Example Turn\n\nTurn 3 times.", turn_example),
	// 	Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
	// 	Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
	// 	Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
	// 	Auton("Combine all 3 movements", combining_movements),
	// 	Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
	// });
	// ez::as::initialize();

	/**
	 * LEMLIB:
	*/
	// /**
	//  * IMPORTANT: WILL TAKE 3 SECONDS TO CALIBRATE; ENSURE ROBOT IS STATIONARY!
	// */
	// auton_chassis.calibrate();

	// EZ-Template
	/**
	 * TODO: modify active brake kP
	*/
	ez_chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
	ez_chassis.initialize();

	pros::lcd::initialize();
} 

/**
 * DISABLEDSTATE: INIT
 * 
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * COMPINIT: DESCRIPTION
 * 
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
 * AUTONOMOUS: DESCRIPTION
 * 
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
void autonomous() {
	ez_chassis.reset_pid_targets(); // Resets PID targets to 0
	ez_chassis.reset_gyro(); // Reset gyro position to 0
	ez_chassis.reset_drive_sensor(); // Reset drive sensors to 0
	ez_chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.
	
	main_auton(intake);
	// ez::as::auton_selector.call_selected_auton();
}


bool L2_pressed = false;
bool R2_pressed = false;
/**
 * OPCONTROL: DESCRIPTION
 * 
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

		/**
		 * START: PRINTING TO LCD
		*/

		/**
		 * END: PRINTING TO LCD
		*/


		/**
		 * SECTION: CHECKING CONTROLLER INPUTS
		 */
		bool R1_pressed = controller.get_digital(DIGITAL_R1);
		bool R2_pressed = controller.get_digital(DIGITAL_R2);

		
		/**
		 * START: HANDLING CONTROLLER INPUTS
		*/

		/**
		 * CATAPULT:
		*/
		if (controller.get_digital_new_press(DIGITAL_A)) {
			catapult.toggle_catapult();
		}

		/**
		 * BLOCKER:
		*/
		if (controller.get_digital_new_press(DIGITAL_L1)) {
			blocker.block_da_opponents();
		} 

		/**
		 * WINGS:
		*/
		if (controller.get_digital_new_press(DIGITAL_L2)) {
			wings.wing_it();
		}

		/**
		 * INTAKE:
		*/
		// if the intake and outtake buttons are either BOTH pressed or BOTH depressed...
		if (R1_pressed == R2_pressed) {
			// don't do anything!
			intake.break_the_award();
		}
		// intake
		else if (R1_pressed) {
			intake.intake_the_award();
		}
		// outtake
		else if (R2_pressed) {
			intake.outtake_the_award();
		}

		/**
		 * END: HANDLING CONTROLLER INPUTS
		*/


		/**
		 * START: RUN OTHER ROBOT FUNCTIONS
		*/

		/**
		 * CATAPULT:
		*/
		catapult.catapult_us_to_victory();

		/**
		 * DRIVETRAIN:
		*/
		// currently hard-coded to run tank drive!
		chassis.tank_drive(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_Y));

		/**
		 * END: RUN OTHER ROBOT FUNCTIONS
		*/


		/**
		 * TICK DELAY: (muy muy important)
		*/
		pros::delay(10);
	}
}
