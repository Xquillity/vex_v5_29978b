#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  //----------------- STEP 1: get first 3 balls -----------------//

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
  drivePID(23.367, 0.155, 0, 0.4);// forwards( to be in line with matchloader)
  turnPID(-51.167, 0.3, 0, 0.01); // turn to face matchloader
  wait(500, msec); // Give time for matchloader to extend

  //----------------- STEP 3: Matchload -----------------//

  startPickupBalls(100);
  spinDT(57.41);// forwards into matchloader
  wait(950, msec); // Allow time to pick up balls
  stopDT();
  wait(450, msec);
  stopIntake();
  wait(50, msec);
   //----------------- STEP 4: score top -----------------//
  // move to goal
  
   startPickupBalls(100);
  drivePID(-35, 0.1, 0, 0.4);
 stopIntake();
  wait(50, msec);

  // Score
  startScoreTop(100);
  wait(3000, msec); // Adjust time as needed to ensure balls are scored
  stopIntake();
  wait(100, msec);
  



//----------------- wing setup----------------//
spinDTPosition(78, 4.67);
turnPID(80.67, 0.5, 0, 0.01);
toggleMatchloader();
spinDTPosition(78, -9);
turnPID(-76.47, 0.3, 0, 0.01);


//------wing-------//
drivePID(-15, 0.1, 0, 0.4);

}





void leftAuton() {
  // No autonomous - empty function
  //----------------- STEP 1: get first 3 balls -----------------//

  drivePID(9, 0.155, 0, 0.4);
  turnPID(35, 0.5, 0, 0.01);
  startPickupBalls(100);
  spinDTPosition(67, 15);
  wait(250, msec);
  stopIntake();

  //----------------- STEP 2: prep to move to matchload location -----------------//
  drivePID(-3, 0.155, 0, 0.4);// backwards
  turnPID(85.67, 0.3, 0, 0.01); //turn
  toggleMatchloader();// matchloader down
  drivePID(23.367, 0.155, 0, 0.4);// forwards( to be in line with matchloader)
  turnPID(51.167, 0.3, 0, 0.01); // turn to face matchloader
  wait(500, msec); // Give time for matchloader to extend

  //----------------- STEP 3: Matchload -----------------//

  startPickupBalls(100);
  spinDT(57.41);// forwards into matchloader
  wait(950, msec); // Allow time to pick up balls
  stopDT();
  wait(450, msec);
  stopIntake();
  wait(50, msec);
   //----------------- STEP 4: score top -----------------//
  // move to goal
  
   startPickupBalls(100);
  drivePID(-35, 0.1, 0, 0.4);
 stopIntake();
  wait(50, msec);

  // Score
  startScoreTop(100);
  wait(3000, msec); // Adjust time as needed to ensure balls are scored
  stopIntake();
  wait(100, msec);
  


/*
//----------------- wing setup----------------//
spinDTPosition(78, 4.67);
turnPID(80.67, 0.5, 0, 0.01);
toggleMatchloader();
spinDTPosition(78, -9);
turnPID(-76.47, 0.3, 0, 0.01);


//------wing-------//
drivePID(-15, 0.1, 0, 0.4);
*/
  
  
}

void skillsAuton() {
  // No autonomous - empty function
}
