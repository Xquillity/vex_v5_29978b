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
    
  // ========== S-SHAPED INTAKE CONTROLS ========== //
  // Button mapping for S-shaped intake (3 rollers only):
  //  - R2: Score TOP    -> IB fwd (pick up), IM fwd (guide up), IT fwd (CLOCKWISE to top)
  //  - R1: Score MIDDLE -> IB fwd (pick up), IM fwd (guide up), IT rev (COUNTERCLOCKWISE to middle)  
  //  - L2: Reverse      -> All rollers reverse to unjam
  //  - L1: Intake only  -> IB fwd (pick up), IM fwd (guide), IT stopped

  //sets up boolean variables for each button
    bool l1 = Controller.ButtonL1.pressing();
    bool l2 = Controller.ButtonL2.pressing();
    bool r1 = Controller.ButtonR1.pressing();
    bool r2 = Controller.ButtonR2.pressing();

   
    if (r2) {
      // SCORE TOP - IT clockwise directs balls to top goal
      IB.spin(vex::directionType::fwd, 120, vex::velocityUnits::pct);  // pick up balls
      IM.spin(vex::directionType::fwd, 120, vex::velocityUnits::pct);  // guide balls up S-shape
      IT.spin(vex::directionType::fwd, 120, vex::velocityUnits::pct);  // CLOCKWISE to direct to top
    } 
    else if (r1) {
      // SCORE MIDDLE - IT counterclockwise directs balls to middle goal
      IB.spin(vex::directionType::fwd, 120, vex::velocityUnits::pct);  // pick up balls
      IM.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);  // guide balls up S-shape
      IT.spin(vex::directionType::rev, 120, vex::velocityUnits::pct);  // COUNTERCLOCKWISE to direct to middle
    }  
    else if (l2) {  
      // REVERSE / UNJAM - all rollers reverse
      IB.spin(vex::directionType::rev, 120, vex::velocityUnits::pct);
      IM.spin(vex::directionType::rev, 120, vex::velocityUnits::pct);
      IT.spin(vex::directionType::fwd, 120, vex::velocityUnits::pct);
    } 
    else if (l1) {
      // INTAKE ONLY - collect balls without directing them anywhere
      IB.spin(vex::directionType::fwd, 120, vex::velocityUnits::pct);  // pick up balls
      IM.spin(vex::directionType::fwd, 120, vex::velocityUnits::pct);  // guide balls up
      IT.stop();  // top roller off - balls stay in intake
    } else {
      // No intake buttons pressed - stop all rollers
      IB.stop();
      IM.stop();
      IT.stop();
    }

    // ========== PNEUMATIC CONTROLS ========== //
    // Simple pneumatic controls using directional pad:
    // Up = 75mm cylinder, Down = 50mm cylinder, A = 25mm cylinder
    
    if (Controller.ButtonUp.pressing()) {
      Pneumatic75mm.set(true);   // extend 75mm
    } else {
      Pneumatic75mm.set(false);  // retract 75mm
    }
    
    if (Controller.ButtonDown.pressing()) {
      Pneumatic50mm.set(true);   // extend 50mm
    } else {
      Pneumatic50mm.set(false);  // retract 50mm
    }
    
    if (Controller.ButtonA.pressing()) {
      Pneumatic25mm.set(true);   // extend 25mm
    } else {
      Pneumatic25mm.set(false);  // retract 25mm
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


// jaydon is here