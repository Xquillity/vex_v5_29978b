#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  // STEP 1-2: Drive forward 24 inches
  drivePID(24, 0.155, 0, 0.4);
  
  // STEP 2 PREP: Turn left 45 degrees (diagonal)
  turnPID(45, 0.5, 0, 0.01);
  
  // STEP 2-3: Forward while collecting balls
  pickupBalls(1500); // Start pickup while driving
  drivePID(18, 0.155, 0, 0.4); // Drive forward to collection area
  
  // STEP 3-4: Backwards 
  drivePID(-18, 0.155, 0, 0.4);
  
  // STEP 4 PREP: Turn right 90 degrees
  turnPID(-90, 0.5, 0, 0.01);
  
  // STEP 4-5: Turn left 45 to align + drive to goal
  turnPID(45, 0.5, 0, 0.01); // Align scoring end to goal
  drivePID(24, 0.155, 0, 0.4); // Forward to goal area
  
  // STEP 5-6: Turn to position scoring end + drive + score
  turnPID(90, 0.5, 0, 0.01); // Position scoring end toward goal
  drivePID(12, 0.155, 0, 0.4); // Forward into scoring position
  scoreTop(5000, false); // Score first batch for 5 seconds
}

void leftAuton() {
  // No autonomous - empty function
}

void skillsAuton() {
  // No autonomous - empty function
}
