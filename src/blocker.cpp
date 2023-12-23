#include "main.h"
#include <string>

Blocker::Blocker(std::uint8_t blocker_port_1, std::uint8_t blocker_port_2) : blocker_piston_1(blocker_port_1), blocker_piston_2(blocker_port_2) {
    blocker_piston_1.set_value(0);
    blocker_piston_2.set_value(0);
}

void Blocker::block_da_opponents() {
    blocker_enabled = !blocker_enabled;

    blocker_piston_1.set_value(blocker_enabled);
    blocker_piston_2.set_value(blocker_enabled);
}