#include "vex.h"
using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller;

//Drivetrain Motors
extern motor leftMotorA;
extern motor leftMotorB;
extern motor leftMotorC;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor rightMotorC;
extern motor_group LeftDrive;
extern motor_group RightDrive;
extern drivetrain Drivetrain;

//Intake Motors
extern motor IntakeMotor1;
extern motor IntakeMotor2;
extern motor IntakeMotor3;

//Pneumatics
extern digital_out lilWill;

//Sensors
extern inertial InertialSensor;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );