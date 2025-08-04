#include "robot-config.h"
#include <fstream>
#include <string>

// Records the average drivetrain rotation over a set period and saves to SD card as CSV.
// @param durationMs - Duration to record in milliseconds
// @param intervalMs - Interval between samples in milliseconds
// @param filename   - CSV filename to save on SD card (e.g., "drivetrain_log.csv")
const double wheelDiameter = 3.25;
const double wheelCircumference = wheelDiameter * M_PI;

void recordDrivetrainRotation(int durationMs, int intervalMs, const std::string& filename) {
    int samples = durationMs / intervalMs;
    std::ofstream file("/usd/" + filename); // SD card path

    // Write CSV header
    file << "Time(ms),AverageRotation(degrees)\n";

    for (int i = 0; i < samples; ++i) {
        // Get average rotation from all drive motors
        double leftAvg = (leftMotorA.position(degrees) + leftMotorB.position(degrees) + leftMotorC.position(degrees)) / 3.0;
        double rightAvg = (rightMotorA.position(degrees) + rightMotorB.position(degrees) + rightMotorC.position(degrees)) / 3.0;
        double avgRotation = (leftAvg + rightAvg) / 2.0;

        file << (i * intervalMs) << "," << (avgRotation * wheelCircumference) << "\n";
        vex::task::sleep(intervalMs);
    }

    file.close();
}