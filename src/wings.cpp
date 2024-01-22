#include "main.h"

// constructor
Wings::Wings(
  std::uint8_t wing_piston_port
) : wing_piston(wing_piston_port) {
  wings_enabled = false;
  
  wing_piston.set_value(wings_enabled);
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

void Wings::wing_it() {
  wings_enabled = !wings_enabled;

  this->update();
}