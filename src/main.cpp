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
/*                             DRIVER Control Task                           */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/





void usercontrol(void) {
  // Simple button state tracking
  bool lastButtonA = false;
  bool lastButtonY = false;

  while (true) {


    
    // ========== DRIVE CONTROL ========== //
    double fwd = Controller.Axis3.position();  // Left joystick Y = forward/back
    double turn = Controller.Axis1.position() * 0.667; // Left joystick X = turning

    double leftPower  = fwd + turn;
    double rightPower = fwd - turn;

  
    spinLeftDT(leftPower * 0.567);// DRIVE SPEED HERE
    spinRightDT(rightPower * 0.567);// DRIVE SPEED HERE
    
    // ========== INERTIAL SENSOR CALIBRATION ========== //
    // (Handled in pre_auton; no runtime calibration here.)

   
   
   
   // ========== INTAKE ROLLERS CONTROL ========== //
    
  // ========== RAMP INTAKE CONTROLS ========== //
  // Button mapping for ramp intake:
  //  - R2: PICKUP BALLS -> Only bottom intake motor forward
  //  - R1: SCORE TOP    -> Both motors forward (everything forward)
  //  - L1: SCORE BOTTOM -> Both motors reverse (everything reverse)
  //  - L2: SCORE MIDDLE -> Extend piston + both motors forward
  //  - No buttons pressed -> Retract piston + stop motors

  

  //sets up boolean variables for each button
    bool l1 = Controller.ButtonL1.pressing();
    bool l2 = Controller.ButtonL2.pressing();
    bool r1 = Controller.ButtonR1.pressing();
    bool r2 = Controller.ButtonR2.pressing();
   
    if (r2) {
      // PICKUP BALLS ONLY - only bottom intake motor forward, top reverse just to circulate balls (anti jamming)
      BottomIntake.spin(vex::directionType::rev, 120, vex::velocityUnits::pct);
      TopIntake.stop();
    } 
    else if (r1) {
      // SCORE TOP - both motors forward (everything forward)
      BottomIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      TopIntake.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
    }
    else if (l2) {
      // SCORE BOTTOM - both motors reverse (everything reverse)
      BottomIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      TopIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else if (l1) {
      // SCORE MIDDLE - extend piston + both motors forward
      Middle.set(true);
      BottomIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      TopIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else {
      // No buttons pressed - retract piston + stop motors
      Middle.set(false);
      BottomIntake.stop();
      TopIntake.stop();
    }
    
   
   
    // ========== MATCHLOADER CONTROL ========== //
    // A button - single press toggle
    bool currentButtonA = Controller.ButtonA.pressing();
    if (currentButtonA && !lastButtonA) {
      toggleMatchloader();  // Simple toggle - if extended it retracts, if retracted it extends
    }
    lastButtonA = currentButtonA;
   
    

    // ========== DESCORER CONTROL ========== //
    // Y button - single press toggle
    bool currentButtonY = Controller.ButtonY.pressing();
    if (currentButtonY && !lastButtonY) {
      toggleDescorer();  // Simple toggle - if extended it retracts, if retracted it extends
    }
    lastButtonY = currentButtonY;
  }
}

///----------------------------------END OF DRIVER CONTROL-----------------------------------------*/




// Main will set up the competition functions and callbacks.
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


