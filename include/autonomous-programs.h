#include "pid-setup.h"
#include "data-collection.h"

// Global PIDDrive object for use in autonomous routines
PIDDrive drive;

// Autonomous routine for Red Left start position
void autonomous1() { //LeftLG
    Drivetrain.setTurnVelocity(20, pct);
    intakeStore();
    drive.driveTo(32.5, 10); //intake set of 3 blocks
    wait(150, msec);
    drive.driveTo(-2.5, 20);
    wait(50, msec);
    Drivetrain.turnFor(-105, deg);
    wait(50, msec);

    drive.driveTo(34, 40); //drive toward match loader
    wait(50, msec);
    intakeStop();
    Drivetrain.turnFor(120, deg);
    wait(200, msec);
    allignerToggle();
    /*intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.drive(forward); //drive into match loader
    wait(775, msec);
    Drivetrain.stop();
    wait(550, msec);
    intakeStop();
    drive.driveTo(-20, 45); //drive out of match loader
    
    wait(50, msec);
    lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.turnFor(183, deg); //turn toward long goal
    wait(50, msec);*/
    Drivetrain.setDriveVelocity(25, pct);
    Drivetrain.drive(forward); //drive into long goal
    wait(500, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(1250, msec); //score into long goal, then unjam, then score again
    intakeOuttake();
    wait(200, msec);
    intakeScoreTop();
    wait(1250, msec);
    intakeStop();

    //super special tech:

    drive.driveTo(-8, 30);
    pusherToggle();
    wait(50, msec);
    Drivetrain.turnFor(-45, deg);
    wait(50, msec);
    drive.driveTo(15.4, 35);
    wait(50, msec);
    Drivetrain.turnFor(46, deg);
    wait(100, msec);
    drive.driveTo(8);
    pusherToggle();
    drive.driveTo(16);
}

// Autonomous routine for Red Right start position
void autonomous2() { //LeftAWP
    
}


void autonomous3() { //RightLG
    Drivetrain.setTurnVelocity(20, pct);
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(26.5, deg);
    intakeStore();
    wait(50, msec);
    drive.driveTo(16.5, 10); //intake set of 3 blocks
    wait(150, msec);
    drive.driveTo(-2.5, 20);
    wait(50, msec);
    Drivetrain.turnFor(85, deg);
    wait(50, msec);

    drive.driveTo(31, 40); //drive toward match loader
    wait(50, msec);
    intakeStop();
    Drivetrain.turnFor(-123, deg);
    wait(200, msec);
    allignerToggle();
    /*intakeStore();
    wait(50, msec);
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.drive(forward); //drive into match loader
    wait(775, msec);
    Drivetrain.stop();
    wait(550, msec);
    intakeStop();
    drive.driveTo(-20, 45); //drive out of match loader
    
    wait(50, msec);
    lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.turnFor(183, deg); //turn toward long goal
    wait(50, msec);*/
    Drivetrain.setDriveVelocity(25, pct);
    Drivetrain.drive(forward); //drive into long goal
    wait(600, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(1250, msec); //score into long goal, then unjam, then score again
    intakeOuttake();
    wait(200, msec);
    intakeScoreTop();
    wait(1750, msec);
    intakeStop();

    //super special tech:

    drive.driveTo(-8, 30);
    pusherToggle();
    wait(50, msec);
    Drivetrain.turnFor(-45, deg);
    wait(50, msec);
    drive.driveTo(15.4, 35);
    wait(50, msec);
    Drivetrain.turnFor(45, deg);
    wait(100, msec);
    drive.driveTo(6);
    pusherToggle();
    drive.driveTo(20, 30);


}


void autonomous4() { //rightAWP
    drive.driveTo(30);
    wait(50, msec);
    Drivetrain.turnFor(30, deg);
    intakeStore();
    wait(50, msec);
    drive.driveTo(16.5, 10); //intake set of 3 blocks
    wait(150, msec);
    drive.driveTo(-4, 20); //allign with middle goal
    intakeStop();
    wait(50, msec);
    Drivetrain.turnFor(-66, deg);
    wait(50, msec);
    drive.driveTo(15.5, 20); //drive into middle goal
    intakeScoreBottom(); //score into middle goal
    wait(1000, msec);
    intakeStop();
    drive.driveTo(-51.5, 55); //drive toward match loader
    /*wait(50, msec);
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
    */


    Drivetrain.turnFor(-50, deg);


    wait(50, msec);
    //lilWillToggle();
    allignerToggle();
    Drivetrain.setDriveVelocity(30, pct);
    wait(250, msec);
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
void autonomous5() {  //skills1
    Drivetrain.setTurnVelocity(20, pct); 
    drive.driveTo(34.25, 35);
    wait(50, msec);
    Drivetrain.turnFor(90, deg);
    lilWillToggle();
    wait(200, msec);
    intakeStore();
    Drivetrain.setDriveVelocity(30, pct);
    Drivetrain.drive(forward);
    wait(500, msec);
    Drivetrain.stop();
    wait(2500, msec);
    drive.driveTo(-20, 35);
    intakeStop();
    switchAllignerLoader();
    wait(50, msec);
    Drivetrain.turnFor(172.5, deg);
    wait(50, msec);
    Drivetrain.drive(forward);
    wait(500, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(2000, msec);
    intakeOuttake();
    wait(200, msec);
    intakeScoreTop();
    wait(2000, msec);
    intakeStop();

    drive.driveTo(-7, 35);
    wait(100, msec);
    Drivetrain.turnFor(-85, deg);
    wait(100, msec);
    drive.driveTo(100, 35);
    wait(50, msec);
    switchAllignerLoader();
    wait(100, msec);
    Drivetrain.turnFor(-90, deg);
    intakeStore();
    Drivetrain.drive(forward);
    wait(650, msec);
    Drivetrain.stop();
    wait(2500, msec);
    drive.driveTo(-20, 35);
    intakeStop();
    switchAllignerLoader();
    wait(50, msec);
    Drivetrain.turnFor(175, deg);
    wait(50, msec);
    Drivetrain.drive(forward);
    wait(500, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(1000, msec);
    intakeOuttake();
    wait(250, msec);
    intakeScoreTop();
    wait(2000, msec);
    intakeStop();

    drive.driveTo(-7, 35);
    wait(50, msec);
    Drivetrain.turnFor(85, deg);
    wait(50, msec);
    drive.driveTo(15, 35);
    wait(50, msec);
    Drivetrain.turnFor(-85, deg);
    wait(50, msec);
    intakeStore();
    drive.driveTo(80, 35);
    wait(50, msec);
    Drivetrain.turnFor(-85, deg);
    wait(50, msec);
    intakeStop();
    drive.driveTo(8, 35);
    wait(50, msec);
    Drivetrain.turnFor(90, deg);
    wait(50, msec);
    switchAllignerLoader();
    intakeStore();
    wait(100, msec);
    Drivetrain.drive(forward);
    wait(700, msec);
    Drivetrain.stop();
    wait(2500, msec);
    drive.driveTo(-20, 35);
    intakeStop();
    switchAllignerLoader();
    wait(50, msec);
    Drivetrain.turnFor(175, deg);
    wait(50, msec);
    Drivetrain.drive(forward);
    wait(500, msec);
    Drivetrain.stop();
    intakeScoreTop();
    wait(1000, msec);
    intakeOuttake();
    wait(250, msec);
    intakeScoreTop();
    wait(2000, msec);
    intakeStop();
}

// Autonomous routine for Programming Skills challenge
void autonomous6() {  //skills2
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