/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       rishinalem                                                */
/*    Created:      2/23/2024, 5:42:33 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
vex::competition Competition;
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller;
motor LF = vex::motor(PORT13, vex::gearSetting::ratio6_1, false);
motor LB = vex::motor(PORT15, vex::gearSetting::ratio6_1, true);
motor RF = vex::motor(PORT20, vex::gearSetting::ratio6_1, true);
motor RB = vex::motor(PORT16, vex::gearSetting::ratio6_1, false);
vex::rotation rotationSensor = vex::rotation(PORT10);
int currentDegree = rotationSensor.position(degrees);
int targetDegree = 90;
motor Intake = vex::motor(PORT18, vex::gearSetting::ratio6_1, true);
motor Outtake = vex::motor(PORT11, vex::gearSetting::ratio36_1, true);
digital_out solenoid_right = digital_out(Brain.ThreeWirePort.H);
digital_out solenoid_left = digital_out(Brain.ThreeWirePort.G);

int leftpower = 0;
int rightpower = 0;
int initialPosition = 0;


// Here is the function to collect the triball from the field
void toggle_intake(void) {
while (1) {
    //Intake.spin(forward, 100, pct);
    Intake.spin(reverse, 12, volt);
}
}

// Here is the function to put the triball into the field goal
void toggle_opposite_intake(void) {
while (1) {
    //Intake.spin(forward, 100, pct);
    Intake.spin(forward, 12, volt);
}
}

// Here is the usercontrol function
void usercontrol(void) {
// User control code here, inside the loop
while (1) {
// Get joystick values with curve adjustment
if (abs(Controller.Axis3.position(percent)) > 10) {
    leftpower = Controller.Axis3.position(percent);
} else {
    leftpower = 0;
}
if (abs(Controller.Axis2.position(percent)) > 10) {
    rightpower = Controller.Axis2.position(percent);
} else {
    rightpower = 0;
}
//int leftJoy = Controller1.Axis3.position(percent) * abs(Controller1.Axis3.position(percent)) / 100;
///int rightJoy = Controller1.Axis2.position(percent) * abs(Controller1.Axis2.position(percent)) / 100;


   // Calculate motor powers for left and right motor groups
   //int leftpower = leftJoy + rightJoy;
   //int rightpower = leftJoy - rightJoy;


// Apply power to the motor groups with appropriate polarity for direction control
LF.spin(forward, leftpower, pct);
LB.spin(forward, leftpower, pct);
RF.spin(forward, rightpower, pct);
RB.spin(forward, rightpower, pct);


// Control intake motor
/*
bool buttonAPressed = Controller1.ButtonA.pressing();
int intakeSpeed = buttonAPressed ? 50 : 0;
Intake.spin(forward, intakeSpeed, pct);
*/


wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
}
}

// Here is the code for the wings
void toggle_wings_1(void) {
while (1) {
solenoid_left.set(true);
}
}

void toggle_wings_2(void) {
while(1) {
solenoid_right.set(true);
}
}

//Here is the code for the outtake
void toggle_outtake(void) {
while(1) {
//Outtake.spin(forward, 100, pct);
Outtake.spin(forward, 12, volt);
}
}

int main() {
rotationSensor.setPosition(targetDegree, vex::rotationUnits::deg);
Competition.drivercontrol(usercontrol);
Controller.ButtonR1.pressed([]{ toggle_intake (); });
Controller.ButtonL1.pressed([]{ toggle_opposite_intake (); });
Controller.ButtonR2.pressed([] { toggle_outtake (); });
Controller.ButtonY.pressed([] {toggle_wings_1 (); });
Controller.ButtonRight.pressed([] {toggle_wings_2 (); });
Controller.ButtonL2.pressed([] {toggle_outtake (); });


 //Competition.autonomous(autonomous);


 // Run the pre-autonomous function.
 //pre_auton();


// Prevent main from exiting with an infinite loop.
while (true) {
wait(100, msec);

    }
}