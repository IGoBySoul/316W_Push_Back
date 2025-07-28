#include "robot-config.h"

motor* intakeMotors[] = { &IntakeMotor1, &IntakeMotor2, &IntakeMotor3 };
const int intakeMotorCount = 3;

// Helper to spin selected motors
void spinIntakes(const int dirs[3], int speed = 100) {
  for (int i = 0; i < intakeMotorCount; ++i) {
    if (dirs[i] != 0)
      intakeMotors[i]->spin(dirs[i] > 0 ? forward : reverse, speed, pct);
  }
}

// Spins all intake motors forward to store game elements
void intakeStore() {
  int dirs[3] = {1, 1, 1};
  spinIntakes(dirs);
}

// Spins intake motors to score in the bottom goal
void intakeScoreBottom() {
  int dirs[3] = {-1, 0, -1};
  spinIntakes(dirs);
}

// Spins intake motors to score in the middle goal
void intakeScoreMiddle() {
  int dirs[3] = {1, -1, -1};
  spinIntakes(dirs);
}

// Spins intake motors to score in the top goal
void intakeScoreTop() {
  int dirs[3] = {1, 1, -1};
  spinIntakes(dirs);
}

// Spins intake motors to load the chamber
void intakeChamberLoad() {
  int dirs[3] = {1, 1, 0};
  spinIntakes(dirs);
}

// Stops all intake motors
void stopIntake() {
  for (int i = 0; i < intakeMotorCount; ++i)
    intakeMotors[i]->stop();
}