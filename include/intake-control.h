#include "robot-config.h"

// Spins all intake motors forward to store game elements
void (intakeStore)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(forward, 100, pct);
  IntakeMotor3.spin(forward, 100, pct);
}

// Spins intake motors to score in the bottom goal
void (intakeScoreBottom)() {
  IntakeMotor1.spin(reverse, 100, pct);
  IntakeMotor3.spin(reverse, 100, pct);
}

// Spins intake motors to score in the middle goal
void (intakeScoreMiddle)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(reverse, 100, pct);
  IntakeMotor3.spin(reverse, 100, pct);
}

// Spins intake motors to score in the top goal
void (intakeScoreTop)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(forward, 100, pct);
  IntakeMotor3.spin(reverse, 100, pct);
}

// Spins intake motors to load the chamber
void (intakeChamberLoad)() {
  IntakeMotor1.spin(forward, 100, pct);
  IntakeMotor2.spin(forward, 100, pct);
}

// Stops all intake motors
void (stopIntake)() {
  IntakeMotor1.stop();
  IntakeMotor2.stop();
  IntakeMotor3.stop();
}