#pragma once
#include "vex.h"
#include "robot-config.h"
#include <cmath>
#include <array>

// PIDDrive class: Implements PID control for driving straight and turning
// This class provides two main functions:
//   - driveTo(targetInches): Drives the robot a specified distance using PID control
//   - turnTo(targetAngle): Turns the robot to a specified angle using PID control and the inertial sensor
class PIDDrive {
public:
    PIDDrive()
        : leftMotors{&leftMotorA, &leftMotorB, &leftMotorC},
          rightMotors{&rightMotorA, &rightMotorB, &rightMotorC} {}

    // Drive a target distance (in inches), positive = forward, negative = backward
    // Uses PID control to move the robot accurately
    void driveTo(double targetInches) {
        // --- PID Constants ---
        double kP = 1.0;        // Proportional gain: Controls how strongly the robot reacts to error
        double kI = 0.0;        // Integral gain: Helps eliminate steady-state error (set to 0 unless needed)
        double kD = 0.05;       // Derivative gain: Dampens oscillations and overshoot
        double headingKp = 1.0; // Heading correction gain: Keeps the robot driving straight
        int maxSpeed = 80;      // Maximum motor output (percent)
        int timeoutMs = 4000;   // Timeout in milliseconds to prevent stalling forever
        // -------------------------------------------

        // Convert inches to degrees for 3.25" wheels
        // degrees = (inches / (wheel_circumference)) * 360
        const double wheelDiameter = 3.25;
        const double wheelCircumference = wheelDiameter * M_PI;
        int targetDegrees = static_cast<int>((targetInches / wheelCircumference) * 360.0);

        // Reset all drive motor encoders to zero
        for (auto m : leftMotors) m->resetPosition();
        for (auto m : rightMotors) m->resetPosition();

        // Initialize PID variables
        double error = 0, prevError = 0, integral = 0, derivative = 0;
        int startTime = vex::timer::system();

        // Store the initial heading for correction
        double initialHeading = InertialSensor.rotation(vex::degrees);

        // Main PID loop
        while (true) {
            // Calculate average encoder position for left and right sides
            double leftPos = 0, rightPos = 0;
            for (auto m : leftMotors) leftPos += m->position(vex::degrees);
            for (auto m : rightMotors) rightPos += m->position(vex::degrees);
            leftPos /= leftMotors.size();
            rightPos /= rightMotors.size();
            double avgPos = (leftPos + rightPos) / 2.0;

            // PID calculations
            error = targetDegrees - avgPos;      // How far we are from the target
            integral += error;                   // Accumulate error over time
            derivative = error - prevError;      // Rate of change of error

            double output = kP * error + kI * integral + kD * derivative; // PID output
            if (output > maxSpeed) output = maxSpeed;
            if (output < -maxSpeed) output = -maxSpeed;

            // Heading correction using inertial sensor
            double currentHeading = InertialSensor.rotation(vex::degrees);
            double headingError = initialHeading - currentHeading; // Positive if veering right, negative if left
            double headingCorrection = headingKp * headingError;   // Correction to keep robot straight

            // Apply correction: left gets +correction, right gets -correction
            double leftOutput = output + headingCorrection;
            double rightOutput = output - headingCorrection;

            // Set motor speeds
            for (auto m : leftMotors) m->spin(vex::forward, leftOutput, vex::percent);
            for (auto m : rightMotors) m->spin(vex::forward, rightOutput, vex::percent);

            // Exit conditions: close enough to target or timeout
            if (abs(error) < 5) break; // within 5 degrees of target
            if (vex::timer::system() - startTime > timeoutMs) break; // timeout

            prevError = error;
            vex::task::sleep(20); // Wait 20ms between PID updates
        }
        // Stop all drive motors at the end of the move
        for (auto m : leftMotors) m->stop();
        for (auto m : rightMotors) m->stop();
    }

    // PID turn to a target angle (degrees) using the inertial sensor
    // Positive angle = turn right, negative = turn left
    void turnTo(double targetAngle) {
        // --- PID Constants ---
        double kP = 0.2;        // Proportional gain for turning
        double kI = 0.0;        // Integral gain for turning
        double kD = 0.05;       // Derivative gain for turning
        double encoderKp = 0.1; // Correction for encoder symmetry (keeps both sides turning equally)
        int maxSpeed = 80;      // Maximum motor output (percent)
        int timeoutMs = 3000;   // Timeout in milliseconds
        // -------------------------------------------

        // Reset sensors and encoders
        InertialSensor.resetRotation();
        for (auto m : leftMotors) m->resetPosition();
        for (auto m : rightMotors) m->resetPosition();

        // Initialize PID variables
        double error = 0, prevError = 0, integral = 0, derivative = 0;
        int startTime = vex::timer::system();
        while (true) {
            // Inertial sensor feedback for current angle
            double currentAngle = InertialSensor.rotation(vex::degrees);
            error = targetAngle - currentAngle;      // How far we are from the target angle
            integral += error;                       // Accumulate error
            derivative = error - prevError;          // Rate of change

            double output = kP * error + kI * integral + kD * derivative; // PID output

            // Encoder feedback for symmetry (keeps both sides turning equally)
            double leftAvg = 0, rightAvg = 0;
            for (auto m : leftMotors) leftAvg += m->position(vex::degrees);
            for (auto m : rightMotors) rightAvg += m->position(vex::degrees);
            leftAvg /= leftMotors.size();
            rightAvg /= rightMotors.size();

            double encoderError = leftAvg + rightAvg; // Should be near zero if both sides turn equally (opposite directions)
            double encoderCorrection = encoderKp * encoderError;

            // Combine outputs and clamp to maxSpeed
            double leftOutput = output - encoderCorrection;
            double rightOutput = output + encoderCorrection;

            if (leftOutput > maxSpeed) leftOutput = maxSpeed;
            if (leftOutput < -maxSpeed) leftOutput = -maxSpeed;
            if (rightOutput > maxSpeed) rightOutput = maxSpeed;
            if (rightOutput < -maxSpeed) rightOutput = -maxSpeed;

            // Left side spins forward, right side spins reverse for turning
            for (auto m : leftMotors) m->spin(vex::forward, leftOutput, vex::percent);
            for (auto m : rightMotors) m->spin(vex::reverse, rightOutput, vex::percent);

            // Exit conditions: close enough to target or timeout
            if (fabs(error) < 1.0) break; // within 1 degree of target
            if (vex::timer::system() - startTime > timeoutMs) break; // timeout

            prevError = error;
            vex::task::sleep(20); // Wait 20ms between PID updates
        }
        // Stop all drive motors at the end of the turn
        for (auto m : leftMotors) m->stop();
        for (auto m : rightMotors) m->stop();
    }

private:
    std::array<vex::motor*, 3> leftMotors;
    std::array<vex::motor*, 3> rightMotors;
};