#include "main.h"

// haha so "left" and "right" are relative to the front of the robot being the intake :clown:

Wings::Wings(std::uint8_t l_wing_port, std::uint8_t r_wing_port) : left_wing(l_wing_port), right_wing(r_wing_port) {
  left_wing.set_value(0);
  right_wing.set_value(0);
}

void Wings::update() {
  left_wing.set_value(wings_enabled);
  right_wing.set_value(wings_enabled);
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