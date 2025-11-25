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


//----------------- DRIVETRAIN MOTORS ----------------//
vex::motor LB(vex::PORT1, vex::gearSetting::ratio6_1, true); //Left Back Motor
vex::motor LF(vex::PORT2, vex::gearSetting::ratio6_1, true); //Left Front Motor
vex::motor LM(vex::PORT3, vex::gearSetting::ratio6_1, true); //Left Middle Motor
vex::motor RB(vex::PORT4, vex::gearSetting::ratio6_1, false); //Right Back Motor
vex::motor RF(vex::PORT5, vex::gearSetting::ratio6_1, false); //Right Front Motor
vex::motor RM(vex::PORT6, vex::gearSetting::ratio6_1, false); //Right Middle Motor

// Motor groups for drivetrain
vex::motor_group LeftDrive(LF, LM, LB);
vex::motor_group RightDrive(RF, RM, RB);

// Drivetrain: wheel travel = 320mm, track width = 280mm, wheelbase = 300mm (adjust as needed)
vex::drivetrain Drivetrain(LeftDrive, RightDrive, 320, 280, 300);




//----------------- Intake Motors ----------------//
// Ramp intake motors (2 motors, 11w each)
vex::motor BottomIntake(vex::PORT7, vex::gearSetting::ratio18_1, false); //Bottom Intake Roller (port 5, 11w)
vex::motor TopIntake(vex::PORT8, vex::gearSetting::ratio18_1, false); //Top Intake Roller (port 6, 11w)




//----------------- PNEUMATICCS ---------------------------//
//----------------- Matchloader and Descorer pistons -----------------//

vex::digital_out Matchloader(Brain.ThreeWirePort.D);    // Matchloader piston
vex::digital_out Descorer(Brain.ThreeWirePort.E);       // Descorer piston
vex::digital_out Middle(Brain.ThreeWirePort.F);         // Middle scoring piston




//----------------- INERTIAL SENSOR ----------------//        
// Inertial sensor (if connected). If your inertial is on a different port, change the port here.
vex::inertial InertialSensor(vex::PORT10); // Inertial Sensor on port 10



//----------------------CALIBRATION-------------------//
void vexcodeInit() {
  InertialSensor.calibrate();
  Matchloader.set(false); // retracted
  Descorer.set(false); // retracted
  Middle.set(false); // retracted
  while (InertialSensor.isCalibrating()) {
    vex::task::sleep(100);
  }
}
