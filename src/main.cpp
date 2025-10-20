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
#include "gifclass.h"

using namespace vex;

competition Competition;

// Only declare the Gif object globally so you can control its lifetime
vex::Gif* gif = nullptr;

// Helper to check if VEXnet/competition switch is connected
bool isCompetitionConnected() {
  return Competition.isFieldControl() || Competition.isCompetitionSwitch();
}

void pre_auton(void) {
  // Stop and delete the gif if it exists, so autonSelector can use the screen
  /*if (gif != nullptr) {
    delete gif;
    gif = nullptr;
  }*/
  // Only show auton selector if VEXnet/competition switch is connected
  if (isCompetitionConnected()) {
    autonSelector();
  }
}

void autonomous(void) {
  // Make sure GIF is not running during autonomous
  /*if (gif != nullptr) {
    delete gif;
    gif = nullptr;
  }*/
  Drivetrain.setTurnVelocity(25, pct);
  PIDDrive drive;
  switch (autonSelection) {
    case 0: autonomous1(); break;
    case 1: autonomous2(); break;
    case 2: autonomous3(); break;
    case 3: autonomous4(); break;
    case 4: autonomous5(); break;
    case 5: autonomous6(); break;
    case 6: autonomous7(); break;
    case 7: autonomous8(); break;
    case 8: break;
    default: break;
  }
}

void usercontrol(void) {
  // Start the GIF display only in driver control
  /*if (gif == nullptr) {
    gif = new vex::Gif("world.gif", 120, 0);
  }*/

  Drivetrain.setStopping(brake);
  Drivetrain.setTurnVelocity(100, percent);
  IntakeMotor1.setStopping(brake);
  IntakeMotor2.setStopping(brake);
  IntakeMotor3.setStopping(brake);

  //int count = 0;
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

    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  // Prevent main from exiting by running an infinite loop
  while (true) {
    wait(100, msec);
  }
}
