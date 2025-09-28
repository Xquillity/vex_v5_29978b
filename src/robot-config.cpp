// src/robot-config.cpp
#include "robot-config.h"

//Configuration!

/*Reminders: 
Make sure that all your ports are different and correct! 
Make sure all of your motor + piston names are different and not confusing.
If it seems like some of your motors are running against eachother in the drivetrain, try switching around the true/false

*/

vex::brain Brain;
vex::controller Controller(vex::controllerType::primary);
// Motors for movement
vex::motor LB(vex::PORT6, vex::gearSetting::ratio6_1, true); //Left Back Motor
vex::motor LM(vex::PORT8, vex::gearSetting::ratio6_1, true); //Left Middle Motor
vex::motor LF(vex::PORT10, vex::gearSetting::ratio6_1, true); //Left Front Motor
vex::motor RB(vex::PORT3, vex::gearSetting::ratio6_1, false); //Right Back Motor (1/6TH SPEED OF 3600 RPM)
vex::motor RM(vex::PORT1, vex::gearSetting::ratio6_1, false); //Right Middle Motor
vex::motor RF(vex::PORT2, vex::gearSetting::ratio6_1, false); //Right Front Motor
// Motor groups for drivetrain
vex::motor_group LeftDrive(LF, LM, LB);
vex::motor_group RightDrive(RF, RM, RB);

// Drivetrain: wheel travel = 320mm, track width = 280mm, wheelbase = 300mm (adjust as needed)
vex::drivetrain Drivetrain(LeftDrive, RightDrive, 320, 280, 300);
// Intake motors
vex::motor IT(vex::PORT21, vex::gearSetting::ratio18_1, false); //Top Intake Motor
vex::motor IB(vex::PORT9, vex::gearSetting::ratio18_1, false); //Bottom Intake Motor
vex::motor_group Intake(IT, IB);




vex::digital_out DoubleActingPiston(Brain.ThreeWirePort.A);
vex::digital_out SingleActingPiston(Brain.ThreeWirePort.B);

vex::inertial InertialSensor(vex::PORT7); // Inertial Sensor on port 7

void vexcodeInit() {
  InertialSensor.calibrate();
  DoubleActingPiston.set(false); // retracted
  SingleActingPiston.set(false); // off
  while (InertialSensor.isCalibrating()) {
    vex::task::sleep(100);
  }
}
