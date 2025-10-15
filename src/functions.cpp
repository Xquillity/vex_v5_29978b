#include "robot-config.h"
#include "vex.h"

using namespace vex;

double inchesToDegrees(double inches) {
  return (inches / (M_PI * 3.25)) * 600.0;
}

void setDTPosition(double inches) {
    double deg = inchesToDegrees(inches);
    LF.setPosition(deg, degrees);
    LB.setPosition(deg, degrees);
    RF.setPosition(deg, degrees);
    RB.setPosition(deg, degrees);
}

void stopDT() {
    LF.stop();
    LB.stop();
    RF.stop();
    RB.stop();
}


void spinRightDT(double velocity) {
    RF.spin(forward, velocity, percent);
    RB.spin(forward, velocity, percent);
}

void spinLeftDT(double velocity) {
    LF.spin(forward, velocity, percent);
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
    LB.spinToPosition(targetDegrees, degrees, Velocity, rpm, false);
    RF.spinToPosition(targetDegrees, degrees, Velocity, rpm, false);   
    RB.spinToPosition(targetDegrees, degrees, Velocity, rpm, true);



}

void turnForTime(double velocity, double time) {
    spinRightDT(velocity);
    spinLeftDT(-velocity);
    wait(time, msec);
    stopDT();
}

// ===== Intake / Scoring Helpers =====
void pickupBalls(int duration_ms) {
    // Run intake into hopper: IB forward, hopper forward
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    hopper.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    hopper.stop();
}

void scoreTop(int duration_ms, bool hopperForward) {
    // Run IB/IM forward and IT reverse to score upwards, and run hopper outwards
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    IM.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    IT.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    if (hopperForward) {
        hopper.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    } else {
        hopper.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    }
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop(vex::brakeType::hold);
    IM.stop(vex::brakeType::hold);
    IT.stop(vex::brakeType::hold);
    hopper.stop(vex::brakeType::hold);
}

void scoreMid(int duration_ms, bool hopperForward) {
    // Score to middle: bottom forwards, middle reverse, top stopped, hopper out
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    IM.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    IT.stop();
    if (hopperForward) {
        hopper.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    } else {
        hopper.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    }
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    IM.stop();
    hopper.stop();
}

void reverseIntake(int duration_ms) {
    // Run all intake motors in reverse to eject or unjam
    IB.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    IM.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    IT.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    hopper.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
    hopper.stop();
}

// ===== SIMPLE SCORING FUNCTIONS FOR S-SHAPED INTAKE =====

void scoreTop(int duration_ms = 3000) {
    // Score to top goal - IT spins clockwise (forward)
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // pick up balls
    IM.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // guide up S-shape
    IT.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // clockwise to top
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

void scoreMid(int duration_ms = 3000) {
    // Score to middle goal - IT spins counterclockwise (reverse)
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // pick up balls
    IM.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // guide up S-shape
    IT.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);  // counterclockwise to middle
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

void scoreBottom(int duration_ms = 2000) {
    // Score to bottom goal - just run intake forward, no top roller
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // pick up and push balls
    IM.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // help push balls
    IT.stop();  // top roller off - balls go to bottom
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

void intakeOnly(int duration_ms = 2000) {
    // Just collect balls without scoring
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // pick up balls
    IM.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);  // guide up
    IT.stop();  // top roller off - balls stay in intake
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    IM.stop();
    IT.stop();
}

    void hopperIntake(int duration_ms, bool hopperForward) {
    // Move balls into hopper: IB forward, hopper forward (matching R2 usercontrol)
    IB.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    if (hopperForward) {
        hopper.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
    } else {
        hopper.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
    }
    if (duration_ms > 0) wait(duration_ms, msec);
    IB.stop();
    hopper.stop();
}

    