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

// ===== SIMPLE SCORING FUNCTIONS FOR S-SHAPED INTAKE =====

void scoreTop(int intake_duration_ms = 3000, int speed_percent = 60) {
    // Score to top goal - IT spins clockwise (forward)
    // Parameter: intake_duration_ms = how long to run intake (default 3000ms = 3 seconds)
    IB.spin(forward, speed_percent, percent);  // pick up balls
    IM.spin(forward, speed_percent, percent);  // guide up S-shape
    IT.spin(forward, speed_percent, percent);  // clockwise to top
    if (intake_duration_ms > 0) wait(intake_duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

void scoreMid(int intake_duration_ms = 3000, int speed_percent = 60) {
    // Score to middle goal - IT spins counterclockwise (reverse)
    // Parameter: intake_duration_ms = how long to run intake (default 3000ms = 3 seconds)
    IB.spin(forward, speed_percent, percent);  // pick up balls
    IM.spin(forward, speed_percent, percent);  // guide up S-shape
    IT.spin(reverse, speed_percent, percent);  // counterclockwise to middle
    if (intake_duration_ms > 0) wait(intake_duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

void scoreBottom(int intake_duration_ms = 2000, int speed_percent = 60) {
    // Score to bottom goal - just run intake forward, no top roller
    // Parameter: intake_duration_ms = how long to run intake (default 2000ms = 2 seconds)
    IB.spin(reverse, speed_percent, percent);  // pick up and push balls
    IM.spin(forward, speed_percent, percent);  // help push balls
    IT.spin(forward, speed_percent, percent);  // top roller off - balls go to bottom
    if (intake_duration_ms > 0) wait(intake_duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

void intakeOnly(int intake_duration_ms = 2000, int speed_percent = 60) {
    // Just collect balls without scoring
    // Parameter: intake_duration_ms = how long to run intake (default 2000ms = 2 seconds)
    IB.spin(forward, speed_percent, percent);  // pick up balls
    IM.spin(forward, speed_percent, percent);  // guide up
    IT.stop();  // top roller off - balls stay in intake
    if (intake_duration_ms > 0) wait(intake_duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

// ===== START/STOP SCORING FUNCTIONS (6 FUNCTIONS TOTAL) =====

void startScoreTop(int speed_percent = 60) {
    // Start scoring to top goal - IT spins clockwise (forward)
    IB.spin(forward, speed_percent, percent);  // pick up balls
    IM.spin(forward, speed_percent, percent);  // guide up S-shape
    IT.spin(forward, speed_percent, percent);  // clockwise to top
}

void stopScoreTop() {
    // Stop scoring to top goal
    IB.stop();
    IM.stop();
    IT.stop();
}

void startScoreMiddle(int speed_percent = 60) {
    // Start scoring to middle goal - IT spins counterclockwise (reverse)
    IB.spin(forward, speed_percent, percent);  // pick up balls
    IM.spin(forward, speed_percent, percent);  // guide up S-shape
    IT.spin(reverse, speed_percent, percent);  // counterclockwise to middle
}

void stopScoreMiddle() {
    // Stop scoring to middle goal
    IB.stop();
    IM.stop();
    IT.stop();
}

void startScoreBottom(int speed_percent = 60) {
    // Start scoring to bottom goal - bottom and middle reverse, top forward
    IB.spin(reverse, speed_percent, percent);  // bottom roller spins reverse
    IM.spin(reverse, speed_percent, percent);  // middle roller spins reverse
    IT.spin(forward, speed_percent, percent);  // top roller spins forward
}

void stopScoreBottom() {
    // Stop scoring to bottom goal
    IB.stop();
    IM.stop();
    IT.stop();
}

    