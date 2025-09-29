//These prevent header files from being included multiple times
#ifndef FUNCTIONS_H //if header file is not defined
#define FUNCTIONS_H // define it

double inchesToDegrees(double inches);
void setDTPosition(double inches);
void spinDT(double velocity);
void stopDT();
void spinRightDT(double velocity);
void spinLeftDT(double velocity);

void spinDTPosition(double velocity, double targetInches);
void turnForTime(double velocity, double time);

// Intake / scoring helpers
void pickupBalls(int duration_ms = 1000); // run IB+IM to pick up balls for duration
// hopperForward: true = spin hopper forward, false = spin hopper reverse
void scoreTop(int duration_ms = 7000, bool hopperForward = true);    // run pattern to score to top
void scoreMid(int duration_ms = 7000, bool hopperForward = true);    // run pattern to score to middle
void reverseIntake(int duration_ms = 5000); // run all intake motors in reverse
void hopperIntake(int duration_ms = 5000, bool hopperForward = true); // run pattern to move balls into hopper

#endif //end of define