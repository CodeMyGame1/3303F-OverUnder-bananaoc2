#include "main.h"
#include <string>

// constructor
Intake::Intake(std::uint8_t intake_piston_port) : intake_pistons(intake_piston_port) {}

void Intake::update() {
    intake_pistons.set_value(intake_enabled);
}

void Intake::extend_intake() {
    intake_enabled = true;

    this->update();
}

void Intake::retract_intake() {
    intake_enabled = false;

    this->update();
}