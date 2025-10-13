//----------------------------------------------------------------------------
//                                                                           
//    Module:       main.cpp                                                 
//    Author:       patrick                                                  
//    Created:      7/5/2025, 12:50:42 PM                                    
//    Description:  V5 project                                               
//                                                                           
//----------------------------------------------------------------------------

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

competition Competition;

void pre_auton(void) {
  autonSelector();
}

void autonomous(void) {
  Drivetrain.setTurnVelocity(25, pct);
  PIDDrive drive;
  switch (autonSelection) {
    case 0:
      autonomous1();
      break;
    case 1:
      autonomous2();
      break;
    case 2:
      autonomous3();
      break;
    case 3:
      autonomous4();
      break;
    case 4:
      autonomous5();
      break;
    case 5:
      autonomous6();
      break;
    case 6:
      autonomous7();
      break;
    case 7:
      autonomous8();
      break;
    case 8:
      break;
    default:

      break;
  }
}


void usercontrol(void) {
  printTeamLogo();
  Drivetrain.setStopping(brake);
  Drivetrain.setTurnVelocity(100, percent);
  IntakeMotor1.setStopping(brake);
  IntakeMotor2.setStopping(brake);
  IntakeMotor3.setStopping(brake);


  while (1) {
    inputCurve();
    Controller.ButtonRight.pressed(allignerToggle);
    Controller.ButtonY.pressed(switchAllignerLoader);
    Controller.ButtonDown.pressed(pusherToggle);

    if (Controller.ButtonR1.pressing()) {
      intakeScoreTop();
    } else if (Controller.ButtonL1.pressing()) {
      intakeScoreMiddle(); 
    } else if (Controller.ButtonL2.pressing()) {
      intakeScoreBottom(); 
    } else if (Controller.ButtonR2.pressing()) {
      intakeStore(); 
    } else if (Controller.ButtonB.pressing()) {
      intakeOuttake();
    } else {
      intakeStop(); 
    }

    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  // Prevent main from exiting by running an infinite loop
  while (true) {
    wait(100, msec); // Sleep to save resources
  }
}
