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
    intakeStop;
    drive.driveTo(-50);
    drive.turnTo(45);
    drive.driveTo(22);
    intakeScoreTop();
    wait(10000, msec);
    intakeStop;
}

// Autonomous routine for Red Right start position
void autonomous2() { //redRight
    
}

// Autonomous routine for Blue Left start position
void autonomous3() { //blueLeft
}

// Autonomous routine for Blue Right start position
void autonomous4() { //blueRight
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(32.5, deg);
    intakeStore();
    wait(50, msec);
    drive.driveTo(18, 15);
    wait(250, msec);
    intakeStop();
    Drivetrain.turnFor(-78, deg);
    drive.driveTo(14, 20);
    intakeScoreBottom();
    wait(1000, msec);
    intakeStop();
    drive.driveTo(-45);
    wait(50, msec);
    Drivetrain.turnFor(-131, deg);
    wait(50, msec);
    lilWillToggle();
    intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(35, pct);
    Drivetrain.drive(forward);
    wait(750, msec);
    Drivetrain.stop();
    wait(500, msec);
    intakeStop();
    
    drive.driveTo(-20, 45);
    wait(50, msec);
    lilWillToggle();
    Drivetrain.turnFor(180, deg);
    allignerToggle();
    Drivetrain.drive(forward);
    wait(500, msec);
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