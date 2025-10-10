#include "pid-setup.h"
#include "data-collection.h"

// Global PIDDrive object for use in autonomous routines
PIDDrive drive;

// Autonomous routine for Red Left start position
void autonomous1() { //LeftLG
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(-30, deg);
    
    intakeStore();
    wait(50, msec);
    drive.driveTo(18, 15);
    wait(150, msec);
    drive.driveTo(-4, 20);
    intakeStop();
    
    wait(50, msec);
    Drivetrain.turnFor(-85, deg);
    wait(50, msec);
    drive.driveTo(34, 55);
    wait(50, msec);
    Drivetrain.turnFor(-41, deg);
    wait(50, msec);
    
    lilWillToggle();
    intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(25, pct);
    Drivetrain.drive(forward);
    wait(1000, msec);
    Drivetrain.stop();
    wait(450, msec);
    intakeStop();
    drive.driveTo(-20, 45);
    
    wait(50, msec);
    lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.turnFor(180, deg);
    wait(50, msec);
    Drivetrain.drive(forward);
    wait(400, msec);
    Drivetrain.stop();
    
    intakeScoreTop();
    wait(1250, msec);
    intakeOuttake();
    wait(200, msec);
    intakeScoreTop();
    wait(2000, msec);
    intakeStop();
}

// Autonomous routine for Red Right start position
void autonomous2() { //LeftAWP
    
}


void autonomous3() { //RightLG
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(30, deg);
    intakeStore();
    wait(50, msec);
    drive.driveTo(18, 15); //intake set of 3 blocks
    wait(150, msec);
    drive.driveTo(-4, 20);
    intakeStop();
    wait(50, msec);
    Drivetrain.turnFor(85, deg);
    wait(50, msec);

    drive.driveTo(34, 55); //drive toward match loader
    wait(50, msec);
    Drivetrain.turnFor(41, deg);
    wait(50, msec);
    lilWillToggle();
    intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(25, pct);
    Drivetrain.drive(forward); //drive into match loader
    wait(1000, msec);
    Drivetrain.stop();
    wait(450, msec);
    intakeStop();
    drive.driveTo(-20, 45); //drive out of match loader
    
    wait(50, msec);
    lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.turnFor(-180, deg); //turn toward long goal
    wait(50, msec);
    Drivetrain.drive(forward); //drive into long goal
    wait(400, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(1250, msec); //score into long goal, then unjam, then score again
    intakeOuttake();
    wait(200, msec);
    intakeScoreTop();
    wait(2000, msec);
    intakeStop();
}


void autonomous4() { //rightAWP
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(30, deg);
    intakeStore();
    wait(50, msec);
    drive.driveTo(18, 15); //intake set of 3 blocks
    wait(150, msec);
    drive.driveTo(-4, 20); //allign with middle goal
    intakeStop();
    wait(50, msec);
    Drivetrain.turnFor(-70, deg);
    wait(50, msec);
    drive.driveTo(15, 20); //drive into middle goal
    intakeScoreBottom(); //score into middle goal
    wait(1000, msec);
    intakeStop();
    drive.driveTo(-48, 55); //drive toward match loader
    wait(50, msec);
    Drivetrain.turnFor(-130, deg);
    wait(50, msec);
    lilWillToggle();
    intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.drive(forward); //drive into match loader
    wait(850, msec);
    Drivetrain.stop();
    wait(400, msec);
    intakeStop();
    drive.driveTo(-20, 45);
    
    wait(50, msec);
    lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.turnFor(-180, deg); // allign with long goal
    wait(50, msec);
    Drivetrain.drive(forward); //drive into long goal
    wait(400, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(1250, msec); //score into long goal, then unjam, then score again
    intakeOuttake();
    wait(200, msec);
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
