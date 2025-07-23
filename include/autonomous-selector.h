#pragma once
#include "vex.h"
#include "robot-config.h"

using namespace vex;

// Index of selected autonomous routine (extern for global use)
extern int autonSelection;
// Array of autonomous routine names (extern for global use)
extern const char* autonNames[9];

// Draws the autonomous selector UI on the Brain screen
void drawAutonSelector();

// Waits for user to select and confirm autonomous routine
void autonSelector();