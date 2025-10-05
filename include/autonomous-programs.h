#include "pid-setup.h"
#include "data-collection.h"

// Global PIDDrive object for use in autonomous routines
PIDDrive drive;

// Autonomous routine for Red Left start position
void autonomous1() { //soloAWPleft
    drive.driveTo(48); //drive to be in line with goal
    drive.turnTo(-90); //Turn to face the goal
    drive.driveTo(12); //Drive towards the goal
    lilWillToggle(); //Enable the Match Load Mechanism
    intakeStore(); //Intake Blocks from Match Loader
    Drivetrain.drive(forward); wait(350, msec); Drivetrain.stop(); //Drive forward to ensure bot is fully up against goal
    wait(5000, msec); //Intake for 5 Seconds
    lilWillToggle(); //Disable the Match Load Mechanism
    drive.driveTo(-12); //Back away from Match Loader
    drive.turnTo(-135); //Turn towards Center Goal
    drive.driveTo(50); //Drive To Center Goal while intaking
    intakeScoreMiddle(); wait(500, msec); intakeStore();//Score 1 block into Center Goal
    
    
    drive.driveTo(-16);
    drive.turnTo(45);
    intakeStore();
    drive.driveTo(48);
    drive.turnTo(-45);
    drive.driveTo(16);
    intakeScoreBottom();
    wait(500, msec);
    intakeStop();
    drive.driveTo(-50);
    drive.turnTo(45);
    drive.driveTo(22);
    intakeScoreTop();
    wait(10000, msec);
    intakeStop();
}

// Autonomous routine for Red Right start position
void autonomous2() { //redRight
    
}

// Autonomous routine for Blue Left start position
void autonomous3() { //rightHighScore
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(30, deg);
    intakeStore();
    wait(50, msec);
    drive.driveTo(18, 15);
    wait(150, msec);
    drive.driveTo(-4, 20);
    intakeStop();
    wait(50, msec);
    Drivetrain.turnFor(85, deg);
    wait(50, msec);

    drive.driveTo(38, 55);
    wait(50, msec);
    Drivetrain.turnFor(37.5, deg);
    wait(50, msec);
    lilWillToggle();
    intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(25, pct);
    Drivetrain.drive(forward);
    wait(825, msec);
    Drivetrain.stop();
    wait(350, msec);
    intakeStop();
    drive.driveTo(-20, 45);
    
    wait(50, msec);
    lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.turnFor(-190, deg);
    wait(50, msec);
    Drivetrain.drive(forward);
    wait(400, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(1000, msec);
    intakeStop();
    wait(350, msec);
    intakeScoreTop();
    wait(2500, msec);
    intakeStop();
}

// Autonomous routine for Blue Right start position
void autonomous4() { //rightAWP
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(30, deg);
    intakeStore();
    wait(50, msec);
    drive.driveTo(18, 15);
    wait(150, msec);
    drive.driveTo(-4, 20);
    intakeStop();
    wait(50, msec);
    Drivetrain.turnFor(-70, deg);
    wait(50, msec);
    drive.driveTo(15, 20);
    intakeScoreBottom();
    wait(1000, msec);
    intakeStop();
    drive.driveTo(-51, 55);
    wait(50, msec);
    Drivetrain.turnFor(-130, deg);
    wait(50, msec);
    lilWillToggle();
    intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(25, pct);
    Drivetrain.drive(forward);
    wait(900, msec);
    Drivetrain.stop();
    wait(400, msec);
    intakeStop();
    drive.driveTo(-20, 45);
    
    wait(50, msec);
    lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.turnFor(-187, deg);
    wait(50, msec);
    Drivetrain.drive(forward);
    wait(400, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(2000, msec);
    intakeStop();
}

// Autonomous routine for Skills challenge
void autonomous5() {  //skills
}

// Autonomous routine for Programming Skills challenge
void autonomous6() {  //progSkills
}

// Autonomous routine for Test 1
void autonomous7() {  //test1
    recordDrivetrainRotation(1700, 50, "drivetrain_log.csv");
    Drivetrain.drive(forward, 600, rpm);
    wait(1500, msec);
    Drivetrain.stop();
}

// Autonomous routine for Test 2
void autonomous8() {  //test2
    drive.turnTo(90);
}