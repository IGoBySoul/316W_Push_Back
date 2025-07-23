#pragma once
#include "vex.h"
#include "robot-config.h"
#include <cmath>

// PIDDrive class: Implements PID control for driving straight and turning
// This class provides two main functions:
//   - driveTo(targetInches): Drives the robot a specified distance using PID control
//   - turnTo(targetAngle): Turns the robot to a specified angle using PID control and the inertial sensor
class PIDDrive {
public:
    // Constructor: Initializes references to the drivetrain motors
    PIDDrive()
        : leftA(leftMotorA), leftB(leftMotorB), leftC(leftMotorC),
          rightA(rightMotorA), rightB(rightMotorB), rightC(rightMotorC) {}

    // Drive a target distance (in inches), positive = forward, negative = backward
    // Uses PID control to move the robot accurately
    void driveTo(double targetInches) {
        // --- PID Constants ---
        double kP = 0.2;        // Proportional gain: Controls how strongly the robot reacts to error
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
        leftA.resetPosition();
        leftB.resetPosition();
        leftC.resetPosition();
        rightA.resetPosition();
        rightB.resetPosition();
        rightC.resetPosition();

        // Initialize PID variables
        double error = 0, prevError = 0, integral = 0, derivative = 0;
        int startTime = vex::timer::system();

        // Store the initial heading for correction
        double initialHeading = InertialSensor.rotation(vex::degrees);

        // Main PID loop
        while (true) {
            // Calculate average encoder position for left and right sides
            int leftPos = (leftA.position(vex::degrees) + leftB.position(vex::degrees) + leftC.position(vex::degrees)) / 3;
            int rightPos = (rightA.position(vex::degrees) + rightB.position(vex::degrees) + rightC.position(vex::degrees)) / 3;
            int avgPos = (leftPos + rightPos) / 2;

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
            leftA.spin(vex::forward, leftOutput, vex::percent);
            leftB.spin(vex::forward, leftOutput, vex::percent);
            leftC.spin(vex::forward, leftOutput, vex::percent);
            rightA.spin(vex::forward, rightOutput, vex::percent);
            rightB.spin(vex::forward, rightOutput, vex::percent);
            rightC.spin(vex::forward, rightOutput, vex::percent);

            // Exit conditions: close enough to target or timeout
            if (abs(error) < 5) break; // within 5 degrees of target
            if (vex::timer::system() - startTime > timeoutMs) break; // timeout

            prevError = error;
            vex::task::sleep(20); // Wait 20ms between PID updates
        }
        // Stop all drive motors at the end of the move
        leftA.stop();
        leftB.stop();
        leftC.stop();
        rightA.stop();
        rightB.stop();
        rightC.stop();
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
        leftA.resetPosition();
        leftB.resetPosition();
        leftC.resetPosition();
        rightA.resetPosition();
        rightB.resetPosition();
        rightC.resetPosition();

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
            double leftAvg = (leftA.position(vex::degrees) + leftB.position(vex::degrees) + leftC.position(vex::degrees)) / 3.0;
            double rightAvg = (rightA.position(vex::degrees) + rightB.position(vex::degrees) + rightC.position(vex::degrees)) / 3.0;
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
            leftA.spin(vex::forward, leftOutput, vex::percent);
            leftB.spin(vex::forward, leftOutput, vex::percent);
            leftC.spin(vex::forward, leftOutput, vex::percent);
            rightA.spin(vex::reverse, rightOutput, vex::percent);
            rightB.spin(vex::reverse, rightOutput, vex::percent);
            rightC.spin(vex::reverse, rightOutput, vex::percent);

            // Exit conditions: close enough to target or timeout
            if (fabs(error) < 1.0) break; // within 1 degree of target
            if (vex::timer::system() - startTime > timeoutMs) break; // timeout

            prevError = error;
            vex::task::sleep(20); // Wait 20ms between PID updates
        }
        // Stop all drive motors at the end of the turn
        leftA.stop();
        leftB.stop();
        leftC.stop();
        rightA.stop();
        rightB.stop();
        rightC.stop();
    }

private:
    // References to drivetrain motors for direct control
    // These are set to the actual motor objects defined in robot-config.h
    vex::motor& leftA;
    vex::motor& leftB;
    vex::motor& leftC;
    vex::motor& rightA;
    vex::motor& rightB;
    vex::motor& rightC;
};