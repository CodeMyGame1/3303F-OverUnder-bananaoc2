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

#include "main.h"
#include "EZ-Template/api.hpp"
#include "lemlib/api.hpp"
/**
 * AT A GLANCE:
 * 
 * DRIVETRAIN: (11W * 8 motors = 88W) 
 * - PORTS:
 *   - LEFT:
 *     - top front: 18
 *     - top back: 20
 *     - bottom front: -19
 *     - bottom back: -17
 *   - RIGHT: 
 *     - top front: 11
 *     - top back: 13
 *     - bottom front: -10
 *     - bottom back: -12
 * - SPECS:
 *   - CARTRIDGE: 600rpm (blue)
 *   - GEAR RATIO: 36t -> 48t (1.333x)
 * 
 * IMU:
 * - PORT: 16
 * 
 * INTAKE:
 * - PORT: C
 * - SPECS:
 *   - two single acting pistons
 * 
 * OPNOTES:
 * - GAME:
 *   - ENSURE the robot is STATIONARY when you're starting the program; it needs to calibrate!
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
 *   - LEFT: 'A'
 *   - RIGHT: 'B'
 * 
 *
 * analog:
 * - A: left wing
 * - B: right wing
 * - C: intake
*/

// from `util.cpp`~
pros::Controller controller(pros::E_CONTROLLER_MASTER);

/**
 * DRIVETRAIN: INDIVIDUAL MOTORS
 * TODO: set ports!
*/

pros::Motor left_top_front_motor(18);
pros::Motor left_top_back_motor(20);
pros::Motor left_bottom_front_motor(-19);
pros::Motor left_bottom_back_motor(-17);

pros::Motor right_top_front_motor(-11);
pros::Motor right_top_back_motor(-13);
pros::Motor right_bottom_front_motor(10);
pros::Motor right_bottom_back_motor(12);

/**
 * DRIVETRAIN: MOTOR GROUPS
*/

pros::Motor_Group left_drive({
	left_top_front_motor, left_top_back_motor, left_bottom_front_motor, left_bottom_back_motor
});

pros::Motor_Group right_drive({
	right_top_front_motor, right_top_back_motor, right_bottom_front_motor, right_bottom_back_motor
});

/**
 * TODO: set ports!
*/
pros::Imu inertial_sensor(16);

/**
 * START: EZTEMPLATE
*/

Drive ez_chassis (
	// left chassis ports
	{ 18, 20, -19, -17 }
	
	// right chassis ports
	,{ -11, -13, 10, 12 }

	// IMU port
	,16

	// Wheel diameter
	,3.25

	// cartridge rpm (blue motors)
	,600

	// external drivetrain gear ratio (this is 36t -> 48t)
	,1.333

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
 * START: LEMLIB
*/

lemlib::Drivetrain_t drivetrain {
    &left_drive, // left drivetrain motors
    &right_drive, // right drivetrain motors
    13, // track width
    3.25, // wheel diameter
    450 // wheel rpm
};

// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    0.47, // kP
    7, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    5, // kP
    35, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis lemlib_chassis(drivetrain, lateralController, angularController, sensors);

/**
 * END: LEMLIB
*/

/**
 * START: ROBOT COMPONENT INITIALIZATION
*/

// Chassis chassis = Chassis(
// 	{left_top_front_motor, left_top_back_motor, left_bottom_front_motor, left_bottom_back_motor},
// 	{right_top_front_motor, right_top_back_motor, right_bottom_front_motor, right_bottom_back_motor},
// 	pros::E_MOTOR_BRAKE_COAST
// );
Intake intake = Intake( 
	'B', 'C'
);

Wings wings = Wings(
	'A'
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
	// Autonomous Selector using LLEMU
	/**
	 * Auton Selector for sample autons
	*/

	ez::as::auton_selector.add_autons({
		Auton("Far Side Auton", far_side),
		Auton("Near Side Auton", near_side),
		Auton("push", push),
		Auton("blank", blank)
	});

	ez_chassis.set_active_brake(0.1);
	ez_chassis.initialize();

	lemlib_chassis.initialize();

	default_constants();

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

std::uint64_t startTime;
std::uint64_t lastBuzz;
void opcontrol() {
	// closes 'em if not already done
	wings.close();

	startTime = pros::micros();
	lastBuzz = startTime;

	while (true) {
		/**
		 * START: PRINTING TO LCD
		*/

		/**
		 * END: PRINTING TO LCD
		*/

		if (pros::micros() - lastBuzz >= 100000) {
			if (pros::micros() - startTime >= 9.5e7) {
				lastBuzz = pros::micros();
			 	controller.rumble("........");
			}


			if (pros::micros() - startTime >= 9e7) {
				lastBuzz = pros::micros();
			 	controller.rumble(". . . . ");
			}

			if (pros::micros() - startTime >= 7.5e7) {
				lastBuzz = pros::micros();
			 	controller.rumble(".   .   ");
			}
		}

		/**
		 * SECTION: CHECKING CONTROLLER INPUTS
		 */
		bool R1_pressed = controller.get_digital(DIGITAL_R1);
		// bool R2_pressed = controller.get_digital(DIGITAL_R2);
			
		/**
		 * START: HANDLING CONTROLLER INPUTS
		*/

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
		 * DRIVETRAIN:
		*/
		// currently hard-coded to run tank drive!
		// chassis.tank_drive(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_Y));
		ez_chassis.set_max_speed(90);// temp for botb
		ez_chassis.tank();

		/**
		 * END: RUN OTHER ROBOT FUNCTIONS
		*/


		/**
		 * TICK DELAY: (muy muy important)
		*/
		pros::delay(10);
	}
}
