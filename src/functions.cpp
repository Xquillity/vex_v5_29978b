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




// ===== RAMP INTAKE FUNCTIONS FOR AUTONOMOUS =====//

void startPickupBalls(int speed) {
    // Pickup balls only - run only bottom intake motor
    BottomIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    TopIntake.stop();
}

void startScoreTop(int speed) {
    // Score top - run everything forward
    BottomIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    TopIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}

void startScoreBottom(int speed) {
    // Score bottom - reverse everything
    BottomIntake.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
    TopIntake.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
}

void stopIntake() {
    // Stop both intake motors
    BottomIntake.stop();
    TopIntake.stop();
}

// ===== TIMED INTAKE FUNCTIONS FOR AUTONOMOUS =====

void pickupBallsForTime(int speed, int time_ms) {
    // Pickup balls for specified time and speed
    startPickupBalls(speed);
    wait(time_ms, msec);
    stopIntake();
}

void scoreTopForTime(int speed, int time_ms) {
    // Score top for specified time and speed
    startScoreTop(speed);
    wait(time_ms, msec);
    stopIntake();
}

void scoreBottomForTime(int speed, int time_ms) {
    // Score bottom for specified time and speed
    startScoreBottom(speed);
    wait(time_ms, msec);
    stopIntake();
}

// ===== MATCHLOADER FUNCTIONS =====

void extendMatchloader() {
    // Extend matchloader piston
    Matchloader.set(true);
}

void retractMatchloader() {
    // Retract matchloader piston
    Matchloader.set(false);
}

void toggleMatchloader() {
    // Toggle matchloader piston state
    Matchloader.set(!Matchloader.value());
}

// ===== DESCORER FUNCTIONS =====

void extendDescorer() {
    // Extend descorer piston
    Descorer.set(true);
}

void retractDescorer() {
    // Retract descorer piston
    Descorer.set(false);
}

void toggleDescorer() {
    // Toggle descorer piston state
    Descorer.set(!Descorer.value());
}

// ===== MIDDLE SCORING FUNCTIONS =====

void startScoreMiddle(int speed) {
    // Start middle scoring - extend piston and spin motors forward (same as top scoring)
    Middle.set(true);
    BottomIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    TopIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}

void stopScoreMiddle() {
    // Stop middle scoring - retract piston and stop motors
    Middle.set(false);
    BottomIntake.stop();
    TopIntake.stop();
}

void scoreMiddleForTime(int speed, int time_ms) {
    // Score middle for specified time and speed
    startScoreMiddle(speed);
    wait(time_ms, msec);
    stopScoreMiddle();
}

    