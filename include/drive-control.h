#include "robot-config.h"

// Function prototypes for joystick curve and drive control
double curveJoystick(bool isRed, double input, int curveAmount);
void inputCurve();

// Joystick curve configuration variables (extern for global use)
extern int turningCurve;
extern bool turningRed;
extern int forwardCurve;
extern bool forwardRed;