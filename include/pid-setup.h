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

    // Drive a target distance (in inches), with optional maxSpeed, minSpeed, and timeoutMs
    void driveTo(double targetInches, int maxSpeed = 50, int minSpeed = 10, int timeoutMs = 4000) {
        // --- PID Constants ---
        double kP = 3;
        double kI = 0.0;
        double kD = 0.05;
        double headingKp = 0.25;

        // Separate ramp fractions for up and down
        double rampUpFraction = 0.05;
        double rampDownFraction = 0.20;

        double rampUpDistance = fabs(targetInches) * rampUpFraction;
        double rampDownDistance = fabs(targetInches) * rampDownFraction;

        const double gearRatio = 450.0 / 600.0;
        const double wheelDiameter = 3.25;
        const double wheelCircumference = wheelDiameter * M_PI;

        for (auto m : leftMotors) m->resetPosition();
        for (auto m : rightMotors) m->resetPosition();

        double error = 0, prevError = 0, integral = 0, derivative = 0;
        int startTime = vex::timer::system();
        double initialHeading = InertialSensor.rotation(vex::degrees);

        while (true) {
            double leftPosDeg = 0, rightPosDeg = 0;
            for (auto m : leftMotors) leftPosDeg += m->position(vex::degrees);
            for (auto m : rightMotors) rightPosDeg += m->position(vex::degrees);
            leftPosDeg /= leftMotors.size();
            rightPosDeg /= rightMotors.size();

            double leftPosIn = (leftPosDeg * wheelCircumference / 360.0) * gearRatio;
            double rightPosIn = (rightPosDeg * wheelCircumference / 360.0) * gearRatio;
            double avgPosIn = (leftPosIn + rightPosIn) / 2.0;

            error = targetInches - avgPosIn;
            integral += error;
            derivative = error - prevError;

            double output = kP * error + kI * integral + kD * derivative;

            // Trapezoidal speed profile
            double distanceTraveled = fabs(avgPosIn);
            double distanceRemaining = fabs(targetInches - avgPosIn);

            int profileSpeed = maxSpeed;

            // Ramp up
            if (distanceTraveled < rampUpDistance) {
                profileSpeed = minSpeed + (maxSpeed - minSpeed) * (distanceTraveled / rampUpDistance);
            }
            // Ramp down
            else if (distanceRemaining < rampDownDistance) {
                double dynamicMinSpeed = minSpeed * (distanceRemaining / rampDownDistance);
                profileSpeed = dynamicMinSpeed + (maxSpeed - dynamicMinSpeed) * (distanceRemaining / rampDownDistance);
                if (profileSpeed > 40) profileSpeed = 40;
            }
            // Cruise
            else {
                profileSpeed = maxSpeed;
            }

            // Clamp output to profileSpeed
            if (output > profileSpeed) output = profileSpeed;
            if (output < -profileSpeed) output = -profileSpeed;

            // Only enforce minSpeed if error is significant (e.g., > 5 inches)
            if (fabs(error) > 3.0 && fabs(output) < minSpeed) {
                output = (output > 0) ? minSpeed : -minSpeed;
            }

            // Heading correction
            double currentHeading = InertialSensor.rotation(vex::degrees);
            double headingError = initialHeading - currentHeading;
            double headingCorrection = headingKp * headingError;

            double leftOutput = output + headingCorrection;
            double rightOutput = output - headingCorrection;

            for (auto m : leftMotors) m->spin(vex::forward, leftOutput, vex::percent);
            for (auto m : rightMotors) m->spin(vex::forward, rightOutput, vex::percent);

            // Exit condition: stop when within 3 inches of target
            if (fabs(error) < 3.0) break;
            if (vex::timer::system() - startTime > timeoutMs) break;

            prevError = error;
            vex::task::sleep(20);
        }
        for (auto m : leftMotors) m->stop(vex::brake);
        for (auto m : rightMotors) m->stop(vex::brake);

        // Gradual braking loop after PID exit
        const int brakeSteps = 1;
        for (int i = brakeSteps; i >= 1; --i) {
            double brakePower = (double)i / brakeSteps * 20;
            for (auto m : leftMotors) m->spin(vex::forward, brakePower, vex::percent);
            for (auto m : rightMotors) m->spin(vex::forward, brakePower, vex::percent);
            vex::task::sleep(30);
        }

        // After the PID loop, gradually slow motors to zero before applying brakes
        const int coastSteps = 1;
        for (int i = coastSteps; i >= 1; --i) {
            double coastPower = (double)i / coastSteps * 20;
            for (auto m : leftMotors) m->spin(vex::forward, coastPower, vex::percent);
            for (auto m : rightMotors) m->spin(vex::forward, coastPower, vex::percent);
            vex::task::sleep(20);
        }
        for (auto m : leftMotors) m->stop(vex::brake);
        for (auto m : rightMotors) m->stop(vex::brake);
    }

    // PID turn to a target angle (degrees) using the inertial sensor
    // Positive angle = turn right, negative = turn left
    void turnTo(double targetAngle) {
        // --- PID Constants ---
        double kP = 0.32;        // Proportional gain
        double kI = 0.0;         // Integral gain
        double kD = 0.062;        // Derivative gain
        double encoderKp = 0.1;  // Symmetry correction gain
        int maxSpeed = 35;       // Maximum motor output (percent)
        int minSpeed = 8;        // Minimum motor output (percent)
        int timeoutMs = 3000;    // Timeout in milliseconds

        // Reset encoders
        for (auto m : leftMotors) m->resetPosition();
        for (auto m : rightMotors) m->resetPosition();

        // Gear ratio adjustment
        const double gearRatio = 450.0 / 600.0; // Output RPM / Motor RPM

        // Calculate target encoder degrees for the turn
        const double wheelTrack = 12.0; // Distance between left/right wheels (inches), adjust for your robot
        const double wheelDiameter = 3.25;
        const double wheelCircumference = wheelDiameter * M_PI;
        double turnCircumference = wheelTrack * M_PI;
        double turnFraction = fabs(targetAngle) / 360.0;
        double targetTurnInches = turnCircumference * turnFraction;
        double targetEncoderDeg = (targetTurnInches / wheelCircumference) * 360.0 / gearRatio; // <-- gear ratio applied

        // Trapezoidal profile for turning
        double rampUpFraction = 0.10;   // 10% of turn for ramp up
        double rampDownFraction = 0.20; // 20% of turn for ramp down
        double rampUpDistance = fabs(targetEncoderDeg) * rampUpFraction;
        double rampDownDistance = fabs(targetEncoderDeg) * rampDownFraction;

        double error = 0, prevError = 0, integral = 0, derivative = 0;
        int startTime = vex::timer::system();

        while (true) {
            double leftAvg = 0, rightAvg = 0;
            for (auto m : leftMotors) leftAvg += m->position(vex::degrees);
            for (auto m : rightMotors) rightAvg += m->position(vex::degrees);
            leftAvg /= leftMotors.size();
            rightAvg /= rightMotors.size();

            // Use only motor encoders for feedback, include gear ratio
            double currentEncoder = ((fabs(leftAvg) + fabs(rightAvg)) / 2.0) / gearRatio;
            error = targetEncoderDeg - currentEncoder;
            integral += error;
            derivative = error - prevError;

            // Trapezoidal speed profile for turning
            double distanceTraveled = fabs(currentEncoder);
            double distanceRemaining = fabs(targetEncoderDeg - currentEncoder);

            int profileSpeed = maxSpeed;

            // Ramp up
            if (distanceTraveled < rampUpDistance) {
                profileSpeed = minSpeed + (maxSpeed - minSpeed) * (distanceTraveled / rampUpDistance);
            }
            // Ramp down
            else if (distanceRemaining < rampDownDistance) {
                double dynamicMinSpeed = minSpeed * (distanceRemaining / rampDownDistance);
                profileSpeed = dynamicMinSpeed + (maxSpeed - dynamicMinSpeed) * (distanceRemaining / rampDownDistance);
                if (profileSpeed > 20) profileSpeed = 20; // Cap for gentle finish
            }
            // Cruise
            else {
                profileSpeed = maxSpeed;
            }

            // PID output with symmetry correction
            double symmetryError = leftAvg - rightAvg;
            double output = kP * error + kI * integral + kD * derivative - encoderKp * symmetryError;

            // Clamp output to profileSpeed
            if (output > profileSpeed) output = profileSpeed;
            if (output < -profileSpeed) output = -profileSpeed;

            // Only enforce minSpeed if error is significant
            if (fabs(error) > 10.0 && fabs(output) < minSpeed) {
                output = (output > 0) ? minSpeed : -minSpeed;
            }

            // Left side spins forward, right side spins reverse for turning
            for (auto m : leftMotors) m->spin(vex::forward, output, vex::percent);
            for (auto m : rightMotors) m->spin(vex::reverse, output, vex::percent);

            // Exit condition: within 5 degrees of target
            if (fabs(error) < 5.0) break;
            if (vex::timer::system() - startTime > timeoutMs) break;

            prevError = error;
            vex::task::sleep(20);
        }

        // Gradually slow motors to zero before applying brakes
        const int coastSteps = 10;
        for (int i = coastSteps; i >= 1; --i) {
            double coastPower = (double)i / coastSteps * 20; // Start at 20%, decrease to 0%
            for (auto m : leftMotors) m->spin(vex::forward, coastPower, vex::percent);
            for (auto m : rightMotors) m->spin(vex::reverse, coastPower, vex::percent);
            vex::task::sleep(40);
        }
        // Stop all drive motors at the end of the turn
        for (auto m : leftMotors) m->stop(vex::brake);
        for (auto m : rightMotors) m->stop(vex::brake);
    }

private:
    std::array<vex::motor*, 3> leftMotors;
    std::array<vex::motor*, 3> rightMotors;
};