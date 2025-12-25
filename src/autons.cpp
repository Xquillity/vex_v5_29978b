#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {

  
  //----------------- STEP 1: get first 3 balls -----------------//

  drivePID(9, 0.07, 0, -0.3);
  turnPID(-35, 0.5, 0, 0.01);
  startPickupBalls(100);
  spinDTPosition(67, 15);
  wait(250, msec);
  stopIntake();

  //----------------- STEP 2: prep to move to matchload location -----------------//
  drivePID(-3, 0.07, 0, -0.3);// backwards  
  turnPID(-85.67, 0.45, 0, 0.015); //turn - reduced kP to decrease correction  
  toggleMatchloader();// matchloader down
  drivePID(26.067, 0.07, 0, -0.3);// forwards( to be in line with matchloader) ( THIS IS THE SMOOTH FORWARDS MOTION)

  turnPID(-50.967,  0.45, 0, 0.015); // turn to face matchloader
 // wait(500, msec); // Give time for matchloader to extend

  //----------------- STEP 3: Matchload -----------------//

  startPickupBalls(100);
  spinDT(35.41);// forwards into matchloader
  wait(950, msec); // Allow time to pick up balls
  stopDT();
  wait(450, msec);
  stopIntake();
  
   //----------------- STEP 4: score top -----------------//
  // move to goal
  
   startPickupBalls(100);
  spinDT(-100); // reverse from matchloader
  wait(1000, msec);
 stopIntake();
  wait(50, msec);

  // Score
  startScoreTop(100);
  wait(1700, msec); // Adjust time as needed to ensure balls are scored
  stopIntake();
  wait(100, msec);
  



//----------------- wing setup----------------//

spinDTPosition(78, 4.67);
turnPID(80.67, 0.45, 0, 0.015);
toggleMatchloader();
spinDTPosition(78, -9);
turnPID(-79.47,  0.45, 0, 0.015);


//------wing-------//
drivePID(-20, 0.1, 0, 0.4);

}





void leftAuton() {
   
  //----------------- STEP 1: Drive to position 1 -----------------//
  drivePID(15, 0.07, 0, -0.3); // Drive forward to position 1
  
  //----------------- STEP 2: Curved path from 1 to 2 -----------------//
  // Gentle curve - right side slightly faster to curve left
  driveCurve(25, 35, 800); // Left wheels 25%, right wheels 35%, for 800ms
  
  // Fine adjustment if needed
  drivePID(5, 0.07, 0, -0.3); // Small forward movement to reach position 2
   
}

void skillsAuton() {
  // No autonomous - empty function
}
