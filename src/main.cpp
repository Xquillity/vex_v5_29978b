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
    // (Handled in pre_auton; no runtime calibration here.)

    // ========== INTAKE ROLLERS CONTROL ========== //

    // (temporary hopper controller test removed)
    
  // ========== INTAKE/SCORING CONTROLS (consolidated) ========== //
  // Button mapping:
  //  - L1: Score top  -> IB forward, IM forward, IT reverse, hopper reverse
  //  - L2: Score mid  -> IB forward, IM reverse, IT stopped, hopper reverse
  //  - R1: Reverse    -> IB reverse, IM reverse, IT reverse, hopper reverse
  //  - R2: Hopper in  -> IB forward, IM reverse, IT reverse, hopper reverse


  //sets up boolean variables for each button
    bool l1 = Controller.ButtonL1.pressing();
    bool l2 = Controller.ButtonL2.pressing();
    bool r1 = Controller.ButtonR1.pressing();
    bool r2 = Controller.ButtonR2.pressing();

   
    if (r2) {
      // SCORE TOP
      IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);//clockwise
      IM.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);//clockwise
      IT.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);//
      hopper.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    } 
 //SCORE MIDDLE   
    else if (r1) {
      
      IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
      IM.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
      IT.stop();
      hopper.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);

 //REVERSE / UNJAM     
    } else if (l2) {
      
      IB.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
      IM.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
      IT.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
      hopper.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);

//HOPPER INTAKE
    } else if (l1) {
      // Hopper intake
      IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
      IM.stop();
      IT.stop();
      hopper.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    } else {
      // No intake buttons pressed
      IB.stop();
      IM.stop();
      IT.stop();
      hopper.stop();
    }
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
