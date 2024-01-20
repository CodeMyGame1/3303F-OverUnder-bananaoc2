#pragma "once"

#include "main.h"


void default_constants();

template <typename number>

void move(number target, int speed, bool wait, bool slew, bool heading);
void turn(number target, int speed, bool wait);
void lswing(number target, int speed, bool wait);
void rswing(number target, int speed, bool wait);
void waitd();

void pid_test();

void far_side();

void near_side();