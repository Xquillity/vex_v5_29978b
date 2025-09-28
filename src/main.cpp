/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       katherinezeng                                             */
/*    Created:      5/27/2025, 10:30:19 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot-config.h"
#include "PID.h"
#include "autons.h"
#include "auton-selector.h"

#include "functions.h"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


  vexcodeInit();
  displayAutonSelector();
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
  switch (getSelectedAuton()) {
    case 0:
      rightAuton();
      break;
    case 1:
      leftAuton();
      break;
    case 2:
      skillsAuton();
      break;
    default:
      Brain.Screen.print("No valid auton selected!");
      break;
  }
 


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

  while (true) {
    // ========== DRIVE CONTROL ========== //
    double fwd = Controller.Axis3.position();
    double turn = Controller.Axis1.position() * 0.67; // Scale down turn to make it more manageable

    double leftPower  = fwd + turn;
    double rightPower = fwd - turn;

    spinLeftDT(leftPower * 0.75);
    spinRightDT(rightPower * 0.75);
    
    // ========== INERTIAL SENSOR CALIBRATION ========== //
         
    
    
    // ========== INTAKE ROLLERS CONTROL ========== //
    if (Controller.ButtonL2.pressing()) {// Spin  backwards, to outake up balls, and score low goals
      Intake.spin(forward, 100, percent);// Spin  forward, to pick up balls, and score high goals
    } else if (Controller.ButtonR2.pressing()) {
      Intake.spin(reverse, 100, percent);
    } else {
      Intake.stop(hold);

    }
  
    
    // Loop delay
    wait(20, msec);
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {

  pre_auton();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  Competition.test_auton();
  //Competition.test_driver();

  while (true) {
    wait(100, msec);
  }
}
