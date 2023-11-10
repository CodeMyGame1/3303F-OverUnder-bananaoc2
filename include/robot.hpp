// #pragma once

// #include "main.h"
// #include "catapult.hpp"
// #include "chassis.hpp"
// #include "intake.hpp"
// #include "wings.hpp"

// class Robot {
//     public:
//         Catapult catapult;
//         Chassis chassis;
//         Intake intake;
//         Wings wings;

//         pros::Controller controller;
        
//         Robot(
//             // catapult parameters
//             int pros_motor_port, int rot_sensor_port, pros::motor_brake_mode_e brake_mode_catapult,
            
//             // chassis parameters
//             std::vector<int> l_motors, std::vector<int> r_motors, pros::motor_brake_mode_e brake_mode_chassis,

//             // intake parameters
//             int intake_port, char intake_piston_port, pros::motor_brake_mode_e brake_mode_intake,

//             // wing parameters
//             char wing_piston_port,

//             // controller
//             pros::controller_id_e_t controller_name
//         );
// };