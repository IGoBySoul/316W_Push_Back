#include "drive-control.h"
#include <cmath>

// Definitions of global variables for joystick curve adjustment
int turningCurve = 20; // Turning curve intensity (higher = more nonlinear)
bool turningRed = true; // Flag for turning curve type (not used in this example)
int forwardCurve = 20; // Forward curve intensity (higher = more nonlinear)
bool forwardRed = true; // Flag for forward curve type (not used in this example)

// curveJoystick
// Applies a nonlinear curve to joystick input for smoother control.
// @param isRed      - Unused flag for alternate curve (future use)
// @param input      - Joystick value (-100 to 100)
// @param curveAmount- Curve intensity (higher = more curve)
// @return           - Curved joystick value (-100 to 100)
double curveJoystick(bool isRed, double input, int curveAmount) {
    // Example: cubic curve for joystick input
    double sign = (input >= 0) ? 1.0 : -1.0;
    double normalized = std::abs(input) / 100.0;
    double curved = sign * std::pow(normalized, curveAmount / 10.0) * 100.0;
    return curved;
}

// inputCurve
// Reads joystick values, applies curve, and sets motor voltages for smooth driving.
void inputCurve() {
    double turnVal = curveJoystick(false, Controller.Axis1.position(percent), turningCurve);
    double forwardVal = curveJoystick(false, Controller.Axis3.position(percent), forwardCurve);

    double turnVolts = turnVal * 0.12;      // Scale to voltage (max 12V)
    double forwardVolts = forwardVal * 0.12;

    // Set left and right drive voltages for arcade drive
    LeftDrive.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);
    RightDrive.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
}