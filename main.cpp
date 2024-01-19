/**
 * NOTE: TODOs in the code are ranked by order of priority
 * 
 * "TODOPR<N>:" denotes a TODO of priority N
 * - example: "TODOPRONE\:" (omit backslash; that's just to prevent confusion when searching for other, actual TODOs)
 * 
 * "TODOPRHK\:" (again, omit backslash) denotes a TODO that is purely for housekeeping / organizing the code
 * 
 * NOTE: just as general advice, most of the code / documentation here is organized in ALPHABETICAL order :P
*/

/**
 * looking at robot from intake side:
 * back, top, on left: 20
 * back, bottom, right: 2
 * back, bottom, left: 6
 * radio port 8
*/

/**
 * RUSH TODO: (12/26):
 * - AUTONS! 
 * - replace IMU Keps nut with locknut
 * - replace IMU with new wire (+ find new place for battery and add a battery mount )
*/

/**
 * RUSH TODO: (bublin moment)
 * - intake hardstop
 *   - screw method (not using for now)
 *     - put rubber nuts on intake hardstop screw
 * - add bigger sprocket to intake system (on the outside!)
 * - (when looking from intake side: bottom top right) -> securely fasten second rubber band (twist & stretch over the motor case!)
 * - wire pneumatics
 * - find better place for battery
 * - port 8 might be loose connection
 * - build side hang!
 * - add two rubberbands on flywheel motors
 * - maybe cut down flywheel axle bc too long?
 * - gears skipping & interfering on left side
 * - the right side (with the intake as the front) sleds are kinda tilted-
 * - battery mount
 * - replace keps nut on IMU with actual locknut
 * - see if auton is legal (can't pass elevation bar but can hover over it!)
 * - sorting:
 *   - see if we actually want to use our blocker
*/

/**
 * REMEMBER TO ADDRESS ALL OTHER TODOs!
 * - TODOPRONE: ADD IMU!!!
 * - TODOPRONE: add new ports!
 * - TODOPRHK: edit ports in "AT A GLANCE"
 * 
 * 
 * - TODOPRTHREE: consider making brake mode HOLD for chassis
 * - TODOPRTHREE: multiple tunes for multiple states of the robot (different weights of items placed on it?)
 * - see if you can do PID/odometry/autons without LemLib/EZTemplate!
 * - will it be "setting up"/initializing robot for 5 seconds DURING, or BEFORE autonomous period?
*/


#include "main.h"
#include "EZ-Template/api.hpp"
// #include "robot.hpp"

/**
 * TODOPRHK:
 * - add gear ratio for flywheel
*/
/**
 * AT A GLANCE:
 * 
 * 
 * BLOCKER:
 * - PORT: 'A' as in Apple
 * - SPECS:
 *   - watch out it go nyoom nyoom (for legal reasons this is a joke)
 * 
 * 
 * CATAPULT: (not active in new bot)
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
 *   - CARTRIDGE: 600rpm (blue) -> 200rpm (green)
 *   - GEAR RATIO: 36 : 1
 *   - BRAKE MODE: COAST 
 * 
 * 
 * FLYWHEEL:
 * - PORTS: (same as intake)
 *   - <add ports here> 
 * - 
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
 * OPNOTES:
 * - GAME:
 *   - ENSURE the robot is STATIONARY when you're starting the program; it needs to calibrate!
 * - the blocker requires one press before it like actually starts functioning so take that into account
 *
 * - PREP CHECKLIST:
 *   - AIR: fill the robot with air!
 *     - while filling the robot with air, at around ~70-80 PSI, the blocker WILL come down, so take caution ^-^
 *   - BATTERY: make sure the battery is full!
 *   - LICENSE PLATES: make sure the license plates are on, and of the right color (and team number ig lmfao)!
 * 
 * - TO KEEP IN MIND: (during the game)
 *   - the front of the robot is the intake!!!
 * 
 * WINGS:
 * - PORTS:
 *   - LEFT: 'B'
 *   - RIGHT: 'C'
 * - SPECS:
 *   - watch out it go boom boom (for legal reasons this is a joke)
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
 * TODO: set ports!
*/

// L
// pros::Motor lf_motor(-17);
// pros::Motor lbb_motor(-6);
// pros::Motor lbt_motor(18);
pros::Motor left_top_front_motor(18);
pros::Motor left_top_back_motor(20);
pros::Motor left_bottom_front_motor(-19);
pros::Motor left_bottom_back_motor(-17);

// R
// pros::Motor rf_motor(8);
// pros::Motor rbb_motor(16);
// pros::Motor rbt_motor(-20);
pros::Motor right_top_front_motor(-11);
pros::Motor right_top_back_motor(-13);
pros::Motor right_bottom_front_motor(10);
pros::Motor right_bottom_back_motor(12);

/**
 * DRIVETRAIN: MOTOR GROUPS
*/
// pros::Motor_Group left_drive({
// 	lf_motor, lbb_motor, lbt_motor
// });
pros::Motor_Group left_drive({
	left_top_front_motor, left_top_back_motor, left_bottom_front_motor, left_bottom_back_motor
});

// pros::Motor_Group right_drive({
// 	rf_motor, rbb_motor, rbt_motor
// });
pros::Motor_Group right_drive({
	right_top_front_motor, right_top_back_motor, right_bottom_front_motor, right_bottom_back_motor
});

/**
 * INTAKE: INDIVIDUAL MOTORS
 * TODO: set these ports!
*/

pros::Motor intake_motor_one(9);
pros::Motor intake_motor_two(-11);

/**
 * TODO: set ports!
*/
pros::Imu inertial_sensor(7);

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

// gear ratio 4:50	

Drive ez_chassis (
	/**
	 * TODOPRONE: set these ports
	*/
	// left chassis ports
	{ 18, 20, -19, -17 }
	
	// right chassis ports
	,{ -11, -13, 10, 12 }

	/**
	 * TODOPRONE: set port
	*/
	// IMU port
	,15

	// wheel diameter
	/**
	 * NOTE: THE ACTUAL DIAMETER OF THE WHEEL IS 3.25 INCHES
	 * 
	 * why did we set it to a different value? well, when we tune the PID, the robot still consistently undershoots the target distance 
	 * (but at a set proportion). therefore, we have resorted to the (questionable?) move of adjusting the wheel diameter to 
	 * compensate for this. the below value is NOT the actual diameter of the wheel
	 * 
	 * TODOPRONE: tune wheel diameter
	*/
	,1.9

	/**
	 * TODOPRTHREE: verify this is correct (blue motors for dt, right?)
	*/
	// cartridge rpm
	,600

	// gear ratio ~ 1.667
	/**
	 * TODOPRTWO: verify gear ratio is correct!
	*/
	,(60 / 36)

	/**
	 * UNCOMMENT IF: using tracking wheels
	*/
	/*
	// left tracking wheel ports
	// ,{1, 2} // 3 wire encoder
	// ,8 // Rotation sensor

	// right tracking wheel ports
	// ,{-3, -4} // 3 wire encoder
	// ,-9 // Rotation sensor
	*/

	/**
	 * UNCOMMENT IF: tracking wheels are plugged into a 3 wire expander
	*/
	// 3 Wire Port Expander Smart Port
	// ,1
);

/**
 * END: EZ TEMPLATE
*/


/**
 * START: ROBOT COMPONENT INITIALIZATION
*/

// /**
//  * TODO: add blocker ports
// */
// Blocker blocker = Blocker(
// 	'B'
// );
// Catapult catapult = Catapult(
// 	20,
// 	12,
// 	pros::E_MOTOR_BRAKE_HOLD
// );
Chassis chassis = Chassis(
	{left_top_front_motor, left_top_back_motor, left_bottom_front_motor, left_bottom_back_motor},
	{right_top_front_motor, right_top_back_motor, right_bottom_front_motor, right_bottom_back_motor},
	pros::E_MOTOR_BRAKE_COAST
);
Intake intake = Intake( 
	'C'
);
/**
 * TODO: add wing ports
*/
Wings wings = Wings(
	'A', 'B'
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
	 * TODOPRTWO: pros::delay for legacy ports configuring?
	*/

	/**
	 * TODOPRONE: verify autonomous selector works
	*/
	// Autonomous Selector using LLEMU
	/**
	 * Auton Selector for sample autons
	*/

	// ez::as::auton_selector.add_autons({
	// 	Auton("Example Drive\n\nDrive forward and come back.", drive_example),
	// 	Auton("Example Turn\n\nTurn 3 times.", turn_example),
	// 	Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
	// 	Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
	// 	Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
	// 	Auton("Combine all 3 movements", combining_movements),
	// 	Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
	// });
	ez::as::auton_selector.add_autons({
		Auton("near side holly", auton3),
		Auton("Far Side Auton", far_side),
		Auton("Drive back", drive_back),
		Auton("Near Side Auton", near_side),
		Auton("Test Far Side Auton", test_far_side),
		Auton("Skills", skills)
	});

	/**
	 * LEMLIB:
	*/
	// /**
	//  * IMPORTANT: WILL TAKE 3 SECONDS TO CALIBRATE; ENSURE ROBOT IS STATIONARY!
	// */
	// auton_chassis.calibrate();

	// EZ-Template
	/**
	 * TODOPRTHREE: modify active brake kP
	*/
	ez_chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
	ez_chassis.initialize();
	/**
	 * TODOPRTHREE: not using bc tuning PID constants seemingly has no effect; add in later?
	*/
	// default_constants();

	// pros::lcd::initialize();
	ez::as::initialize();
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
	
	ez::as::auton_selector.call_selected_auton();

	// near_side();
	// goal_side_two();

	// test_auton();
	// drive_example();
}

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
	// closes 'em if not already done
	wings.close();
	// closes blocker if not already done

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
		// bool R2_pressed = controller.get_digital(DIGITAL_R2);
			
		/**
		 * START: HANDLING CONTROLLER INPUTS
		*/

		/**
		 * CATAPULT:
		*/
		// if (controller.get_digital_new_press(DIGITAL_A)) {
		// 	catapult.toggle_catapult();
		// }

		// /**
		//  * BLOCKER:
		// */
		// if (controller.get_digital_new_press(DIGITAL_L1)) {
		// 	blocker.block_da_opponents();
		// } 

		/**
		 * WINGS:
		*/
		if (controller.get_digital_new_press(DIGITAL_L2)) {
			wings.wing_it();
		}

		/**
		 * INTAKE:
		*/
		if (controller.get_digital(DIGITAL_R1)) {
			intake.extend_intake();
		} else {
			intake.retract_intake();
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
		// catapult.catapult_us_to_victory();

		/**
		 * DRIVETRAIN:
		*/
		// currently hard-coded to run tank drive!
		// chassis.tank_drive(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_Y));
		// ez_chassis.tank();
		ez_chassis.arcade_standard(ez::SPLIT);

		/**
		 * END: RUN OTHER ROBOT FUNCTIONS
		*/


		/**
		 * TICK DELAY: (muy muy important)
		*/
		pros::delay(10);
	}
}
