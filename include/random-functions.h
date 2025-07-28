#include "robot-config.h"

// Team color variable: 0 = white, 1 = red, 2 = blue, 3 = yellow
int teamColor = 0;

// Prints a stylized team logo to the Brain screen with color based on teamColor
void printTeamLogo() {
  color penColors[] = {white, red, blue, yellow};
  color fillColor = black;

  // Clamp teamColor to valid range
  int colorIdx = (teamColor >= 0 && teamColor < 4) ? teamColor : 0;

  Brain.Screen.setPenColor(penColors[colorIdx]);
  Brain.Screen.setFillColor(fillColor);

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(3, 1);

  const char* logo[] = {
    "   .d8888b.   d888   .d8888b.    888       888   ",
    "  d88P  Y88b d8888  d88P  Y88b   888   o   888   ",
    "       .d88P   888  888          888  d8b  888   ",
    "      8888     888  d888888b.    888 d888b 888   ",
    "        Y8b.   888  888P  Y88b   888d88888b888   ",
    "  888    888   888  888    888   88888P Y88888   ",
    "  Y88b  d88P   888  Y88b. d88P   8888P   Y8888   ",
    "   'Y8888P'  8888888 'Y8888P'    888P     Y888   "
  };

  for (const char* line : logo) {
    Brain.Screen.print(line);
    Brain.Screen.newLine();
  }
}