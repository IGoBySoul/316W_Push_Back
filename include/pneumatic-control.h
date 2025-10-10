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

void switchAllignerLoader() {
  if (lilWill.value()==0 && alligner.value()==0) {
    lilWill.set(1);
  } else {
    alligner.set(!alligner.value());
    lilWill.set(!lilWill.value());
  }
}