//These prevent header files from being included multiple times
#ifndef FUNCTIONS_H //if header file is not defined
#define FUNCTIONS_H // define it

double inchesToDegrees(double inches);
void setDTPosition(double inches);
void spinDT(double velocity);
void stopDT();
void spinRightDT(double velocity);
void spinLeftDT(double velocity);
void driveCurve(double leftSpeed, double rightSpeed, int timeMs);

void spinDTPosition(double velocity, double targetInches);
void turnForTime(double velocity, double time);

// Ramp intake functions for autonomous
void startPickupBalls(int speed);            // pickup balls only (bottom motor forward, top stopped)
void startScoreTop(int speed);               // score top (both motors forward)
void startScoreBottom(int speed);            // score bottom (both motors reverse)
void stopIntake();                           // stop both intake motors

// Timed intake functions for autonomous
void pickupBallsForTime(int speed, int time_ms);     // pickup balls for specified time and speed
void scoreTopForTime(int speed, int time_ms);        // score top for specified time and speed
void scoreBottomForTime(int speed, int time_ms);     // score bottom for specified time and speed

// Matchloader and Descorer functions
void extendMatchloader();
void retractMatchloader();
void toggleMatchloader();
void extendDescorer();
void retractDescorer();
void toggleDescorer();

// Middle scoring functions
void startScoreMiddle(int speed);
void stopScoreMiddle();
void scoreMiddleForTime(int speed, int time_ms);

#endif //end of define