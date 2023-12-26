#include "main.h"

// haha so "left" and "right" are relative to the front of the robot being the intake :clown:

Wings::Wings(std::uint8_t wing_port) : wing_piston(wing_port) {
  wings_enabled = false;
  wing_piston.set_value(0);
}

void Wings::update() {
  wing_piston.set_value(wings_enabled);
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