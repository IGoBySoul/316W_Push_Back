#pragma once
#include "vex.h"
#include "robot-config.h"

using namespace vex;

// Autonomous selector variables
extern int autonSelection;
extern const char* autonNames[9];

// Draw 9 buttons for autonomous selection
void drawAutonSelector();

// Wait for user to select autonomous
void autonSelector();