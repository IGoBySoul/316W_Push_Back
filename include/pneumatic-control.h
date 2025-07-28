#include "robot-config.h"

// Toggles the state of the Match Loader Emptying Mechanism
void lilWillToggle() {
  lilWill.set(!lilWill.value());
}