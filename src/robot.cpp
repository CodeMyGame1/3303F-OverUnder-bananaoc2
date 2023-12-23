/**
 * NOT IN USE RIGHT NOW
*/

// #include "main.h"

// Robot::Robot(
//     // catapult parameters
//     int pros_motor_port, int rot_sensor_port, pros::motor_brake_mode_e brake_mode_catapult,
    
//     // chassis parameters
//     std::vector<int> l_motors, std::vector<int> r_motors, pros::motor_brake_mode_e brake_mode_chassis,

//     // intake parameters
//     int intake_port, char intake_piston_port, pros::motor_brake_mode_e brake_mode_intake,

//     // wing parameters
//     char wing_piston_port,

//     // controller
//     pros::controller_id_e_t controller_name

// // "constructing" the sub-classes into class variables
// ) : controller(controller_name),
//     catapult(pros_motor_port, rot_sensor_port, brake_mode_catapult, controller),
//     chassis(l_motors, r_motors, brake_mode_chassis, controller),
//     intake(intake_port, intake_piston_port, brake_mode_intake, controller),
//     wings(wing_piston_port, controller)

// {};