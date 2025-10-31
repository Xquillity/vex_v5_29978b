#include "robot-config.h"
#include "vex.h"
#include "PID.h"

#include "functions.h"

using namespace vex;


void rightAuton() {
  
         // Start scoring to top at 60% speed
  
  // Non-PID movement - slow and simple
  //drivePID(26.9, 0.155, 0, 0.4);
  drivePID(29.45, 0.155, 0, 0.4);   
  turnPID(-32.85, 0.5, 0, 0.01);
  
  //pick up
  startScoreTop(70);
  spinDT(30);                     // Start moving forward at 30% speed
  wait(2, sec);                   // Drive for 3 seconds
  stopDT();      
  wait(345, msec);  
  stopScoreTop();  

   
  // turn to score 
  drivePID(-23, 0.155, 0, 0.4); 
  turnPID(79.2, 0.5, 0, 0.01);

  // forward+score
  drivePID(17, 0.155, 0, 0.4);
  startScoreBottom(100);
  wait(4, sec);
  stopScoreBottom();

  

  
  
}

void leftAuton() {
  // No autonomous - empty function
}

void skillsAuton() {
  // No autonomous - empty function
}
