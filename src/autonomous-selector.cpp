#include "autonomous-selector.h"

int autonSelection = 0;
const char* autonNames[9] = {
  "Red Left", "Red Right", "Blue Left", "Blue Right",
  "Skills", "Prog Skills", "Test 1", "Test 2", "SKIP AUTON"
};

void drawAutonSelector() {
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono20);
  int xOffset = 10;
  int yOffset = 10;

  // Draw 9 auton buttons (8 routines + skip)
  for (int i = 0; i < 9; i++) {
    int row = i / 4;
    int col = i % 4;
    int x = xOffset + col * 100;
    int y = yOffset + row * 85;
    if (autonSelection == i) {
      Brain.Screen.setFillColor(green);
    } else {
      Brain.Screen.setFillColor(blue);
    }
    Brain.Screen.drawRectangle(x, y, 90, 70);
    Brain.Screen.setPenColor(white);
    Brain.Screen.printAt(x + 8, y + 40, autonNames[i]);
  }

  // Move confirm button up and to the right
  int confirmX = xOffset + 200; // moved right (was xOffset + 120)
  int confirmY = yOffset + 160; // moved up   (was yOffset + 200)
  int confirmW = 170;
  int confirmH = 45;
  Brain.Screen.setFillColor(green);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawRectangle(confirmX, confirmY, confirmW, confirmH);
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(confirmX + 50, confirmY + 32, "CONFIRM");

  // Display selected auton name under confirm button, also shifted
  char buf[40];
  snprintf(buf, sizeof(buf), "Selected: %s", autonNames[autonSelection]);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(confirmX + 20, confirmY + confirmH + 25, "Selected:");
  Brain.Screen.printAt(confirmX + 120, confirmY + confirmH + 25, autonNames[autonSelection]);
}

void autonSelector() {
  drawAutonSelector();
  int xOffset = 10;
  int yOffset = 10;
  while (true) {
    if (Brain.Screen.pressing()) {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      // Check auton buttons
      for (int i = 0; i < 9; i++) {
        int row = i / 4;
        int col = i % 4;
        int bx = xOffset + col * 100;
        int by = yOffset + row * 85;
        if (x >= bx && x <= bx + 90 && y >= by && y <= by + 70) {
          autonSelection = i;
          drawAutonSelector();
          while (Brain.Screen.pressing()) { wait(10, msec); }
        }
      }
      // Check confirm button (match new position)
      int confirmX = xOffset + 200;
      int confirmY = yOffset + 160;
      int confirmW = 170;
      int confirmH = 45;
      if (x >= confirmX && x <= confirmX + confirmW && y >= confirmY && y <= confirmY + confirmH) {
        while (Brain.Screen.pressing()) { wait(10, msec); }
        break;
      }
    }
    wait(20, msec);
  }
  Brain.Screen.clearScreen();
}