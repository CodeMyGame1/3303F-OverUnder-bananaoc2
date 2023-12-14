#include "main.h"
#include <string>

Blocker::Blocker(std::uint8_t blocker_port) : blocker_piston(blocker_port) {
    blocker_piston.set_value(1);
}

void Blocker::block_da_opponents() {
    piston_enabled = !piston_enabled;

    blocker_piston.set_value(piston_enabled);
}