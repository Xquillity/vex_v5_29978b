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
vex::motor LB(vex::PORT1, vex::gearSetting::ratio6_1, true); //Left Back Motor
vex::motor LF(vex::PORT2, vex::gearSetting::ratio6_1, true); //Left Front Motor
vex::motor RB(vex::PORT3, vex::gearSetting::ratio6_1, false); //Right Back Motor
vex::motor RF(vex::PORT4, vex::gearSetting::ratio6_1, false); //Right Front Motor
// 4-motor drivetrain (middle motors unplugged for now)
// Motor groups for drivetrain
vex::motor_group LeftDrive(LF, LB);
vex::motor_group RightDrive(RF, RB);

// Drivetrain: wheel travel = 320mm, track width = 280mm, wheelbase = 300mm (adjust as needed)
vex::drivetrain Drivetrain(LeftDrive, RightDrive, 320, 280, 300);
// Intake motors
// Intake motors (explicit ports provided)
vex::motor IT(vex::PORT5, vex::gearSetting::ratio6_1, false); //Top Intake Motor (port 5)
vex::motor IM(vex::PORT6, vex::gearSetting::ratio6_1, false); //Middle Intake Motor (port 6)
vex::motor IB(vex::PORT7, vex::gearSetting::ratio6_1, false); //Bottom Intake Motor (port 7)
vex::motor hopper(vex::PORT8, vex::gearSetting::ratio6_1, false); //Hopper Motor (port 8)
a 





vex::digital_out DoubleActingPiston(Brain.ThreeWirePort.A);
vex::digital_out SingleActingPiston(Brain.ThreeWirePort.B);

// Inertial sensor (if connected). If your inertial is on a different port, change the port here.
vex::inertial InertialSensor(vex::PORT7); // Inertial Sensor on port 7

void vexcodeInit() {
  InertialSensor.calibrate();
  DoubleActingPiston.set(false); // retracted
  SingleActingPiston.set(false); // off
  while (InertialSensor.isCalibrating()) {
    vex::task::sleep(100);
  }
}
