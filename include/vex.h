// Standard C libraries for math, input/output, memory, and string operations
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VEX Robotics API headers for hardware and competition control
#include "v5.h"
#include "v5_vcs.h"

// Macro: Wait until a condition is true, checking every 5ms
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

// Macro: Repeat a block of code for a specified number of iterations
#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)