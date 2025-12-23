#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  // STEP 1-2: Drive forward 24 inches (slow for ball pickup)
 
  extendDescorer();
  drivePID(9, 0.155, 0, 0.4);
  turnPID(-35, 0.5, 0, 0.01);
  startPickupBalls(100);
  spinDTPosition(67, 15);
  wait(250, msec);
  stopIntake();
  drivePID(-3, 0.155, 0, 0.4);
  turnPID(-85.67, 0.3, 0, 0.01);
  toggleMatchloader();
  drivePID(23.467, 0.155, 0, 0.4);
  turnPID(-46.2, 0.3, 0, 0.01);
  wait(500, msec); // Give time for matchloader to extend

 //matchload balls
  startPickupBalls(100);
  spinDT(37.41);
  wait(845, msec); // Allow time to pick up balls
  stopDT();
  wait(450, msec);
  stopIntake();
  wait(50, msec);
 /**/
// STEP 3: score top`
  startPickupBalls(100);
  spinDTPosition(85.67, -30);
  stopIntake();
  
  wait(1000, msec);
  scoreTopForTime(100, 3000);



}

void leftAuton() {
  // No autonomous - empty function

  
  
}

void skillsAuton() {
  // No autonomous - empty function
}
