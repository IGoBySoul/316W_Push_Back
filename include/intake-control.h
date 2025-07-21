#include "robot-config.h"

void (intakeStore)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(forward, 100, pct);
  IntakeMotor3.spin(forward, 100, pct);
}

void (intakeScoreBottom)() {
  IntakeMotor1.spin(reverse, 100, pct);
  IntakeMotor3.spin(reverse, 100, pct);
}

void (intakeScoreMiddle)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(reverse, 100, pct);
  IntakeMotor3.spin(reverse, 100, pct);
}

void (intakeScoreTop)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(forward, 100, pct);
  IntakeMotor3.spin(reverse, 100, pct);
}

void (intakeChamberLoad)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(forward, 100, pct);
}

void (stopIntake)() {
  IntakeMotor1.stop();
  IntakeMotor2.stop();
  IntakeMotor3.stop();
}