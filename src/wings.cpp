#include "main.h"

// haha so "left" and "right" are relative to the front of the robot being the intake :clown:

// constructor
Wings::Wings(
  std::uint8_t wing_left_piston_port
  ,std::uint8_t wing_right_piston_port
) : wing_left_piston(wing_left_piston_port), wing_right_piston(wing_right_piston_port) {
  wings_enabled = false;
  
  wing_left_piston.set_value(wings_enabled);
  wing_right_piston.set_value(wings_enabled);
}

void Wings::update() {
  wing_left_piston.set_value(wings_enabled);
  wing_right_piston.set_value(wings_enabled);
}

void Wings::close() {
  wings_enabled = false;
  
  this->update();
}

void Wings::open() {
  wings_enabled = true;

  this->update();
}

/**
  * TODO: sometimes, the first time i press it, it doesn't detect
*/
void Wings::wing_it() {
  wings_enabled = !wings_enabled;

  this->update();
}