#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  
  drivePID(29.45, 0.155, 0, 0.4);   
  turnPID(-32.85, 0.5, 0, 0.01);
  


  
  
}

void leftAuton() {
  // No autonomous - empty function
}

void skillsAuton() {
  // No autonomous - empty function
}
