#include "drive-control.h"
#include <cmath>

// Definitions of global variables
int turningCurve = 20; // Turning curve intensity
bool turningRed = true; // Flag for turning curve type (red or blue)
int forwardCurve = 20; // Forward curve intensity
bool forwardRed = true; // Flag for forward curve type (red or blue)

double curveJoystick(bool isRed, double input, int curveAmount) {
    // Example: cubic curve for joystick input
    double sign = (input >= 0) ? 1.0 : -1.0;
    double normalized = std::abs(input) / 100.0;
    double curved = sign * std::pow(normalized, curveAmount / 10.0) * 100.0;
    return curved;
}

void inputCurve() {
    double turnVal = curveJoystick(false, Controller.Axis1.position(percent), turningCurve);
    double forwardVal = curveJoystick(false, Controller.Axis3.position(percent), forwardCurve);

    double turnVolts = turnVal * 0.12;
    double forwardVolts = forwardVal * 0.12;

    LeftDrive.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);
    RightDrive.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
}