#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  //----------------- STEP 1: get first 3 balls -----------------//
  extendDescorer();

  drivePID(9, 0.155, 0, 0.4);
  turnPID(-35, 0.5, 0, 0.01);
  startPickupBalls(100);
  spinDTPosition(67, 15);
  wait(250, msec);
  stopIntake();

  //----------------- STEP 2: prep to move to matchload location -----------------//
  drivePID(-3, 0.155, 0, 0.4);// backwards
  turnPID(-85.67, 0.3, 0, 0.01); //turn
  toggleMatchloader();// matchloader down
  drivePID(23.467, 0.155, 0, 0.4);// forwards( to be in line with matchloader)
  turnPID(-46.2, 0.3, 0, 0.01); // turn to face matchloader
  wait(500, msec); // Give time for matchloader to extend

  //----------------- STEP 3: Matchload -----------------//

  startPickupBalls(100);
  spinDT(37.41);// forwards into matchloader
  wait(845, msec); // Allow time to pick up balls
  stopDT();
  wait(450, msec);
  stopIntake();
  wait(50, msec);
 
//----------------- STEP 4: score top`-----------------//

// move to goal
  startPickupBalls(100);
  spinDTPosition(100, -30);
  stopIntake();
  wait(50, msec);
 
  // Score
  startScoreTop(100);
  wait(3000, msec); // Adjust time as needed to ensure balls are scored
  stopIntake();



}

void leftAuton() {
  // No autonomous - empty function

  
  
}

void skillsAuton() {
  // No autonomous - empty function
}
