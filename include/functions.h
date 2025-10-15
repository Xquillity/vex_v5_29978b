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

// S-shaped intake scoring functions (simple)
void scoreTop(int duration_ms = 3000);    // score to top goal (IT clockwise)
void scoreMid(int duration_ms = 3000);    // score to middle goal (IT counterclockwise)  
void intakeOnly(int duration_ms = 2000);  // collect balls without scoring

#endif //end of define