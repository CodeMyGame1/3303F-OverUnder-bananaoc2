#include "main.h"

// constructor
Wings::Wings(
    std::uint8_t left_wing_piston_port,
    std::uint8_t right_wing_piston_port
) : left_wing_piston(left_wing_piston_port), right_wing_piston(right_wing_piston_port) {
    this->close();
}

void Wings::update() {
    left_wing_piston.set_value(wings_enabled);
    right_wing_piston.set_value(wings_enabled);
}

void Wings::close() {
    wings_enabled = false;
  
    this->update();
}

void Wings::open() {
    wings_enabled = true;

    this->update();
}

void Wings::wing_it() {
    wings_enabled = !wings_enabled;

    this->update();
}