#pragma once
#include "vex.h"
#include "robot-config.h"
#include <cmath>

// PIDDrive class: Implements PID control for driving straight and turning
class PIDDrive {
public:
    PIDDrive()
        : leftA(leftMotorA), leftB(leftMotorB), leftC(leftMotorC),
          rightA(rightMotorA), rightB(rightMotorB), rightC(rightMotorC) {}

    // Drive a target distance (in inches), positive = forward, negative = backward
    void driveTo(double targetInches) {
        // --- PID Constants ---
        double kP = 0.2;        // Proportional gain: Start small (0.1–0.3), increase for faster response, decrease if oscillates.
        double kI = 0.0;        // Integral gain: Start at 0, increase only if robot stops short (steady-state error).
        double kD = 0.05;       // Derivative gain: Start at 0, increase if robot overshoots or oscillates.
        double headingKp = 1.0; // Heading correction gain: Start at 1.0, increase if robot veers, decrease if wobbles.
        int maxSpeed = 80;      // Max percent output: Lower for more control, higher for speed (may reduce accuracy).
        int timeoutMs = 4000;   // Timeout in ms: High enough for move, low enough to prevent stalling forever.
        // -------------------------------------------

        // Convert inches to degrees for 3.25" wheels
        // degrees = (inches / (wheel_circumference)) * 360
        const double wheelDiameter = 3.25;
        const double wheelCircumference = wheelDiameter * M_PI;
        int targetDegrees = static_cast<int>((targetInches / wheelCircumference) * 360.0);

        leftA.resetPosition();
        leftB.resetPosition();
        leftC.resetPosition();
        rightA.resetPosition();
        rightB.resetPosition();
        rightC.resetPosition();

        double error = 0, prevError = 0, integral = 0, derivative = 0;
        int startTime = vex::timer::system();

        double initialHeading = InertialSensor.rotation(vex::degrees);

        while (true) {
            int leftPos = (leftA.position(vex::degrees) + leftB.position(vex::degrees) + leftC.position(vex::degrees)) / 3;
            int rightPos = (rightA.position(vex::degrees) + rightB.position(vex::degrees) + rightC.position(vex::degrees)) / 3;
            int avgPos = (leftPos + rightPos) / 2;

            error = targetDegrees - avgPos;
            integral += error;
            derivative = error - prevError;

            double output = kP * error + kI * integral + kD * derivative;
            if (output > maxSpeed) output = maxSpeed;
            if (output < -maxSpeed) output = -maxSpeed;

            // Heading correction
            double currentHeading = InertialSensor.rotation(vex::degrees);
            double headingError = initialHeading - currentHeading;
            double headingCorrection = headingKp * headingError;

            // Apply correction: left gets +correction, right gets -correction
            double leftOutput = output + headingCorrection;
            double rightOutput = output - headingCorrection;

            leftA.spin(vex::forward, leftOutput, vex::percent);
            leftB.spin(vex::forward, leftOutput, vex::percent);
            leftC.spin(vex::forward, leftOutput, vex::percent);
            rightA.spin(vex::forward, rightOutput, vex::percent);
            rightB.spin(vex::forward, rightOutput, vex::percent);
            rightC.spin(vex::forward, rightOutput, vex::percent);

            if (abs(error) < 5) break; // within 5 degrees
            if (vex::timer::system() - startTime > timeoutMs) break; // timeout

            prevError = error;
            vex::task::sleep(20);
        }
        leftA.stop();
        leftB.stop();
        leftC.stop();
        rightA.stop();
        rightB.stop();
        rightC.stop();
    }

    // PID turn to a target angle (degrees) using the inertial sensor
    void turnTo(double targetAngle) {
        // --- PID Constants ---
        double kP = 0.2;        // Proportional gain: Start small (0.1–0.3), increase for faster response, decrease if oscillates.
        double kI = 0.0;        // Integral gain: Start at 0, increase only if robot stops short (steady-state error).
        double kD = 0.05;       // Derivative gain: Start at 0, increase if robot overshoots or oscillates.
        double encoderKp = 0.1; // Encoder symmetry correction: Start at 0.05–0.2, increase if one side turns more.
        int maxSpeed = 80;      // Max percent output: Lower for more control, higher for speed (may reduce accuracy).
        int timeoutMs = 3000;   // Timeout in ms: High enough for move, low enough to prevent stalling forever.
        // -------------------------------------------

        InertialSensor.resetRotation();
        leftA.resetPosition();
        leftB.resetPosition();
        leftC.resetPosition();
        rightA.resetPosition();
        rightB.resetPosition();
        rightC.resetPosition();

        double error = 0, prevError = 0, integral = 0, derivative = 0;
        int startTime = vex::timer::system();
        while (true) {
            // Inertial sensor feedback
            double currentAngle = InertialSensor.rotation(vex::degrees);
            error = targetAngle - currentAngle;
            integral += error;
            derivative = error - prevError;

            double output = kP * error + kI * integral + kD * derivative;

            // Encoder feedback for symmetry
            double leftAvg = (leftA.position(vex::degrees) + leftB.position(vex::degrees) + leftC.position(vex::degrees)) / 3.0;
            double rightAvg = (rightA.position(vex::degrees) + rightB.position(vex::degrees) + rightC.position(vex::degrees)) / 3.0;
            double encoderError = leftAvg + rightAvg; // Should be near zero if both sides turn equally (opposite directions)
            double encoderCorrection = encoderKp * encoderError;

            // Combine outputs and clamp
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

            if (fabs(error) < 1.0) break; // within 1 degree
            if (vex::timer::system() - startTime > timeoutMs) break; // timeout

            prevError = error;
            vex::task::sleep(20);
        }
        leftA.stop();
        leftB.stop();
        leftC.stop();
        rightA.stop();
        rightB.stop();
        rightC.stop();
    }

private:
    // References to drivetrain motors for direct control
    vex::motor& leftA;
    vex::motor& leftB;
    vex::motor& leftC;
    vex::motor& rightA;
    vex::motor& rightB;
    vex::motor& rightC;
};