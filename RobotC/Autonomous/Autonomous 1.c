#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     gHook,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

#include "JoystickDriver.c"

task main()
{
	//rohansucks.org

	waitForStart();
	// goes forward
  motor[rightDrive] = 50;
	motor[leftDrive] = 50;
	wait1Msec(4700); // waits for 4.7 seconds
	// stops
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
}
