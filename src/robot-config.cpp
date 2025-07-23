#include "vex.h"
#include "robot-config.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain; // The main V5 Brain object for screen output and device management

// VEXcode device constructors

controller Controller = controller(primary); // Main driver controller

// Drivetrain Motors
// Three motors per side for 6-motor drive, grouped for easier control
motor leftMotorA = motor(PORT12, ratio6_1, true);   // Left front motor (reversed)
motor leftMotorB = motor(PORT13, ratio6_1, true);   // Left middle motor (reversed)
motor leftMotorC = motor(PORT14, ratio6_1, true);   // Left rear motor (reversed)
motor_group LeftDrive = motor_group(leftMotorA, leftMotorB, leftMotorC); // Left side group
motor rightMotorA = motor(PORT15, ratio6_1, false); // Right front motor
motor rightMotorB = motor(PORT16, ratio6_1, false); // Right middle motor
motor rightMotorC = motor(PORT17, ratio6_1, false); // Right rear motor
motor_group RightDrive = motor_group(rightMotorA, rightMotorB, rightMotorC); // Right side group
// Drivetrain object for arcade/tank drive (wheelbase: 319.19mm x 295mm, wheel diameter: 40mm)
drivetrain Drivetrain = drivetrain(LeftDrive, RightDrive, 319.19, 295, 40, mm, 1);

// Intake Motors
// Three motors for intake and scoring mechanisms
motor IntakeMotor1 = motor(PORT11, ratio6_1, false);    // Main intake roller
motor IntakeMotor2 = motor(PORT18, ratio18_1, false);   // Secondary intake (slower gear ratio)
motor IntakeMotor3 = motor(PORT10, ratio18_1, true);    // Chamber/roller (reversed)

// Pneumatics
// Digital output for controlling pneumatic piston/solenoid
digital_out lilWill = digital_out(Brain.ThreeWirePort.A);

// Sensors
// Inertial sensor for heading and turning feedback
inertial InertialSensor = inertial(PORT20);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true; // Used to enable/disable driver control

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
// This should be called at the start of your int main function.
void vexcodeInit( void ) {
  // nothing to initialize
}