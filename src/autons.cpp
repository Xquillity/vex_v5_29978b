#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  // forward
  drivePID(12,0.155,0, 0.4);// Drive forward 12 inches
  turnPID(-90, 0.5, 0, 0.01);// Turn left 90 degrees to center up
  drivePID(4, 0.155, 0, 0.4);// Drive forward 3 inches to center up
  turnPID(90, 0.5, 0, 0.01); // Turn right 90 degrees to face the balls
  Intake.spin(reverse, 100, percent);// Spin intake forward to prepare picking up balls
  drivePID(19.2, 0.067, 0, 0.4);//GO forward 24 inches to pick up balls
  Intake.stop();

  // score balls
  turnPID(45, 0.5, 0, 0.01);
  drivePID(10.5, 0.155, 0, 0.4);
  Intake.spin(forward, 100, percent);
  wait(7000, msec); // wait 5 seconds to make sure all balls are scored
  Intake.stop(hold);
  
}                                                                            

void leftAuton() {
  //Pickup Balls
  drivePID(12, 0.2, 0, 0);
  turnPID(90, 0.06, 0.001, 0.3);
  drivePID(3, 0.5, 0.003, 0.3);
  turnPID(-90, 0.06, 0.001, 0.3);
  Intake.spin(forward, 100, percent);
  drivePID(30, 0.5, 0.003, 0.3);
  Intake.stop();
  //go score
  drivePID(-9, 0.5, 0.003, 0.3);  
  turnPID(90, 0.06, 0.001, 0.3);
  drivePID(24, 0.5, 0.003, 0.3);
  turnPID( 90, 0.06, 0.001, 0.3);
  drivePID(-3, 0.5, 0.003, 0.3);
  Intake.spin(reverse, 100, percent);
  wait(5000, msec); // wait 5 seconds to make sure all balls are scored
  Intake.stop(hold);
}

void skillsAuton() {
  drivePID(12, 0.4, 0.003, 0.3);
  turnPID(90, 0.06, 0.001, 0.3);
 

  drivePID(-12, 0.5, 0.003, 0.3);
  turnPID(90, 0.06, 0.001, 0.3);
  drivePID(6, 0.5, 0.003, 0.3);
  }
