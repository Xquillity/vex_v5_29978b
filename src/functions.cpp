#include "robot-config.h"
#include "vex.h"

using namespace vex;

double inchesToDegrees(double inches) {
  return (inches / (M_PI * 3.25)) * 600.0;
}

void setDTPosition(double inches) {
    double deg = inchesToDegrees(inches);
    LF.setPosition(deg, degrees);
    LM.setPosition(deg, degrees);
    LB.setPosition(deg, degrees);
    RF.setPosition(deg, degrees);
    RM.setPosition(deg, degrees);
    RB.setPosition(deg, degrees);
}

void stopDT() {
    LF.stop();
    LM.stop();
    LB.stop();
    RF.stop();
    RM.stop();
    RB.stop();
}


void spinRightDT(double velocity) {
    RF.spin(forward, velocity, percent);
    RM.spin(forward, velocity, percent);
    RB.spin(forward, velocity, percent);
}

void spinLeftDT(double velocity) {
    LF.spin(forward, velocity, percent);
    LM.spin(forward, velocity, percent);
    LB.spin(forward, velocity, percent);
}

void spinDT(double velocity) {
    spinRightDT(velocity);
    spinLeftDT(velocity);
}

void spinDTPosition(double Velocity, double targetInches) {
    setDTPosition(0);
    double targetDegrees = inchesToDegrees(targetInches);
    LF.spinToPosition(targetDegrees, degrees, Velocity, rpm, false);
    LM.spinToPosition(targetDegrees, degrees, Velocity, rpm, false);
    LB.spinToPosition(targetDegrees, degrees, Velocity, rpm, false);
    RF.spinToPosition(targetDegrees, degrees, Velocity, rpm, false);   
    RM.spinToPosition(targetDegrees, degrees, Velocity, rpm, false);
    RB.spinToPosition(targetDegrees, degrees, Velocity, rpm, true);



}

void turnForTime(double velocity, double time) {
    spinRightDT(velocity);
    spinLeftDT(-velocity);
    wait(time, msec);
    stopDT();
}

    