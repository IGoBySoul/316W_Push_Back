#include "robot-config.h"

motor* intakeMotors[] = { &IntakeMotor1, &IntakeMotor2, &IntakeMotor3 };
const int intakeMotorCount = 3;

// Default speeds for each intake motor (all set to 100%)
int intakeMotorSpeeds[3] = {100, 100, 100};

// Helper to spin selected motors with individual speeds
void spinIntakes(const int dirs[3], const int speeds[3]) {
  for (int i = 0; i < intakeMotorCount; ++i) {
    if (dirs[i] != 0)
      intakeMotors[i]->spin(dirs[i] > 0 ? forward : reverse, speeds[i], pct);
  }
}

// Spins all intake motors forward to store game elements
void intakeStore() {
  for (int i = 0; i < intakeMotorCount; ++i) intakeMotorSpeeds[i] = 100;
  int dirs[3] = {1, 0, 1};
  spinIntakes(dirs, intakeMotorSpeeds);
}

// Spins intake motors to score in the bottom goal
void intakeScoreBottom() {
  for (int i = 0; i < intakeMotorCount; ++i) intakeMotorSpeeds[i] = 100;
  int dirs[3] = {-1, 0, -1};
  spinIntakes(dirs, intakeMotorSpeeds);
}

// Spins intake motors to score in the middle goal
void intakeScoreMiddle() {
  for (int i = 0; i < intakeMotorCount; ++i) intakeMotorSpeeds[i] = 100;
  int dirs[3] = {1, -1, -1};
  spinIntakes(dirs, intakeMotorSpeeds);
}

void intakeOuttake() {
  for (int i = 0; i < intakeMotorCount; ++i) intakeMotorSpeeds[i] = 100;
  int dirs[3] = {-1, 0, 0};
  spinIntakes(dirs, intakeMotorSpeeds);
}

// Spins intake motors to score in the top goal
void intakeScoreTop() {
  for (int i = 0; i < intakeMotorCount; ++i) intakeMotorSpeeds[i] = 100;
  int dirs[3] = {1, 1, -1};
  spinIntakes(dirs, intakeMotorSpeeds);
}

// Spins intake motors to load the chamber
void intakeChamberLoad() {
  for (int i = 0; i < intakeMotorCount; ++i) intakeMotorSpeeds[i] = 100;
  int dirs[3] = {1, 0, 0};
  spinIntakes(dirs, intakeMotorSpeeds);
}

// Stops all intake motors
void intakeStop() {
  for (int i = 0; i < intakeMotorCount; ++i)
    intakeMotors[i]->stop();
}