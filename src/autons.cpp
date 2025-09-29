#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  // forward
  // Drive and pick up balls, then score using helper functions.
  drivePID(12,0.155,0, 0.4); // Drive forward 12 inches
  turnPID(-90, 0.5, 0, 0.01); // Turn left 90 degrees
  drivePID(4, 0.155, 0, 0.4); // Drive forward 3 inches
  turnPID(90, 0.5, 0, 0.01); // Turn right to face the balls

  pickupBalls(1200); // run IB+IM inward to collect for 1.2s
  drivePID(19.2, 0.067, 0, 0.4); // Drive forward to pick up balls

  // Score sequence
  turnPID(45, 0.5, 0, 0.01);
  drivePID(10.5, 0.155, 0, 0.4);
  scoreTop(7000, false); // run top-scoring pattern for 7s (hopper reversed)
  
}                                                                            

void leftAuton() {
  //Pickup Balls
  // Example left auton using helper functions
  drivePID(12, 0.2, 0, 0);
  turnPID(90, 0.06, 0.001, 0.3);
  drivePID(3, 0.5, 0.003, 0.3);
  turnPID(-90, 0.06, 0.001, 0.3);

  pickupBalls(1500); // collect for 1.5s
  drivePID(30, 0.5, 0.003, 0.3);

  // go score
  drivePID(-9, 0.5, 0.003, 0.3);
  turnPID(90, 0.06, 0.001, 0.3);
  drivePID(24, 0.5, 0.003, 0.3);
  turnPID(90, 0.06, 0.001, 0.3);
  drivePID(-3, 0.5, 0.003, 0.3);
  scoreTop(5000, false); // score to top for 5s (hopper reversed)
}

void skillsAuton() {

  /*
  drivePID(12, 0.4, 0.003, 0.3);
  turnPID(90, 0.06, 0.001, 0.3);
 

  drivePID(-12, 0.5, 0.003, 0.3);
  turnPID(90, 0.06, 0.001, 0.3);
  drivePID(6, 0.5, 0.003, 0.3);
  */
  // Example skill sequence using helpers (adjust timings as needed):
  // drivePID(12, 0.4, 0.003, 0.3);
  // pickupBalls(1200);
  // turnPID(90, 0.06, 0.001, 0.3);

  // drivePID(-12, 0.5, 0.003, 0.3);
  // turnPID(90, 0.06, 0.001, 0.3);
  // drivePID(6, 0.5, 0.003, 0.3);
}
