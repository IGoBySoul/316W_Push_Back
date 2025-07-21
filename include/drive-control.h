#include "robot-config.h"

// Function prototypes
double curveJoystick(bool isRed, double input, int curveAmount);
void inputCurve();

// Joystick curve values (declarations only)
extern int turningCurve;
extern bool turningRed;
extern int forwardCurve;
extern bool forwardRed;