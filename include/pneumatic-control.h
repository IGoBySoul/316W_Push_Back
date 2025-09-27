#include "robot-config.h"

void lilWillToggle() {
  lilWill.set(!lilWill.value());
}

void allignerToggle() {
  alligner.set(!alligner.value());
}

void pusherToggle() {
  pusher.set(!pusher.value());
}