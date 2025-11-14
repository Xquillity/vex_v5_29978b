#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "vex.h" //definitions depend on definitions in vex.h

//extern: there is a variable, no need to make another variable to reference it
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::competition Competition;

//TODO: group into drivetrain

extern vex::motor LB;
extern vex::motor LF;
extern vex::motor LM;
extern vex::motor RB;
extern vex::motor RF;
extern vex::motor RM;

extern vex::motor_group LeftDrive;
extern vex::motor_group RightDrive;

extern vex::drivetrain Drivetrain;

extern vex::motor BottomIntake;
extern vex::motor TopIntake;

extern vex::inertial InertialSensor;

// Matchloader and Descorer pistons
extern vex::digital_out Matchloader;    // Matchloader piston
extern vex::digital_out Descorer;       // Descorer piston

void vexcodeInit();

#endif