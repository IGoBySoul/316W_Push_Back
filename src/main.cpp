/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       patrick                                                   */
/*    Created:      7/5/2025, 12:50:42 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <cmath>
#include "robot-config.h"
#include "intake-control.h"
#include "drive-control.h"
#include "random-functions.h"
#include "pneumatic-control.h"
#include "pid-setup.h"
#include "autonomous-programs.h"
#include "autonomous-selector.h"

using namespace vex;

// A global instance of competition
competition Competition;



void pre_auton(void) {
  autonSelector();
}


void autonomous(void) {
  PIDDrive drive;
  switch (autonSelection) {
    case 0:
      // Red Left
      void autonomous1();
      break;
    case 1:
      // Red Right
      void autonomous2();
      break;
    case 2:
      // Blue Left
      void autonomous3();
      break;
    case 3:
      // Blue Right
      void autonomous4();
      break;
    case 4:
      // Skills
      void autonomous5();
      break;
    case 5:
      // Prog Skills
      void autonomous6();
      break;
    case 6:
      // Test 1
      void autonomous7();
      break;
    case 7:
      // Test 2
      void autonomous8();
      break;
    case 8:
      // SKIP AUTON
      // Do nothing, skip autonomous
      break;
    default:
      break;
  }
}


void usercontrol(void) {
  //Brain.Screen.drawImageFromFile("team-logo.png", 0, 0);
  printTeamLogo();
  while (1) {
    inputCurve();
    Controller.ButtonA.pressed(lilWillToggle);
    if (Controller.ButtonR1.pressing()) {
      intakeScoreTop();
    } else if (Controller.ButtonR2.pressing()) {
      (intakeScoreMiddle)();
    } else if (Controller.ButtonB.pressing()) {
      (intakeScoreBottom());
    } else if (Controller.ButtonL1.pressing()) {
      (intakeStore)();
    } else if (Controller.ButtonL2.pressing()) {
      (intakeChamberLoad)();
    } else {
      stopIntake();
    }
    
    


    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
