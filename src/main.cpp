//----------------------------------------------------------------------------
//                                                                           
//    Module:       main.cpp                                                 
//    Author:       patrick                                                  
//    Created:      7/5/2025, 12:50:42 PM                                    
//    Description:  V5 project                                               
//                                                                           
//----------------------------------------------------------------------------

// Include the main VEX library for hardware control and competition functions
#include "vex.h"
// Include cmath for mathematical functions (e.g., abs, pow, sqrt)
#include <cmath>
// Include custom robot configuration header (motors, sensors, etc.)
#include "robot-config.h"
// Include intake control logic (intake motors, scoring, etc.)
#include "intake-control.h"
// Include drive control logic (drivetrain, joystick mapping, etc.)
#include "drive-control.h"
// Include miscellaneous helper functions
#include "random-functions.h"
// Include pneumatic control logic (pistons, solenoids, etc.)
#include "pneumatic-control.h"
// Include PID setup and control logic for precise movement
#include "pid-setup.h"
// Include autonomous routines for competition
#include "autonomous-programs.h"
// Include autonomous routine selector logic
#include "autonomous-selector.h"

using namespace vex;

// Create a global instance of the competition class to manage match phases
competition Competition;

// Pre-autonomous function: runs before autonomous and user control
// Used to initialize robot and select autonomous routine
void pre_auton(void) {
  autonSelector(); // Display and handle autonomous routine selection
}

// Autonomous function: runs during the autonomous period of the match
void autonomous(void) {
  PIDDrive drive; // Create a PIDDrive object for precise driving
  // Select and run the appropriate autonomous routine based on user selection
  switch (autonSelection) {
    case 0:
      // Red Left Autonomous
      void autonomous1();
      break;
    case 1:
      // Red Right Autonomous
      void autonomous2();
      break;
    case 2:
      // Blue Left Autonomous
      void autonomous3();
      break;
    case 3:
      // Blue Right Autonomous
      void autonomous4();
      break;
    case 4:
      // Skills Autonomous
      void autonomous5();
      break;
    case 5:
      // Programming Skills Autonomous
      void autonomous6();
      break;
    case 6:
      // Test Autonomous 1
      void autonomous7();
      break;
    case 7:
      // Test Autonomous 2
      void autonomous8();
      break;
    case 8:
      // Skip Autonomous: do nothing
      break;
    default:
      // If no valid selection, do nothing
      break;
  }
}

// User control function: runs during the driver control period
void usercontrol(void) {
  printTeamLogo();

  // Main driver control loop: runs repeatedly during user control
  while (1) {
    inputCurve(); // Apply input curve to joystick for smoother driving

    // Map controller buttons to intake functions
    Controller.ButtonA.pressed(lilWillToggle); // Toggles the Match Loader Emptying Mechanism

    // Intake control logic based on button presses
    if (Controller.ButtonR1.pressing()) {
      intakeScoreTop(); // Score in the top goal
    } else if (Controller.ButtonR2.pressing()) {
      intakeScoreMiddle(); // Score in the middle goal
    } else if (Controller.ButtonB.pressing()) {
      intakeScoreBottom(); // Score in the bottom goal
    } else if (Controller.ButtonL1.pressing()) {
      intakeStore(); // Store game elements
    } else if (Controller.ButtonL2.pressing()) {
      intakeChamberLoad(); // Load chamber
    } else {
      stopIntake(); // Stop intake if no buttons are pressed
    }

    // Wait 20 milliseconds to prevent wasted CPU resources
    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}

// Main function: entry point for the program
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous); // Register autonomous function
  Competition.drivercontrol(usercontrol); // Register user control function

  // Run the pre-autonomous function (setup and auton selection)
  pre_auton();

  // Prevent main from exiting by running an infinite loop
  while (true) {
    wait(100, msec); // Sleep to save resources
  }
}
