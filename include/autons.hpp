#pragma "once"

#include "main.h"


void default_constants();

void move(double target, int speed, bool wait, bool slew, bool heading);
void turn(double target, int speed, bool wait);
void lswing(double target, int speed, bool wait);
void rswing(double target, int speed, bool wait);
void waitd();

void pid_test();

void push();

void blank();

void far_side();

void near_side();

void in_progress_far_side();