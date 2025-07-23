#include "robot-config.h"

// Toggles the state of the Little Will Mechanism
void lilWillToggle() {
  lilWill.set(!lilWill.value());
}