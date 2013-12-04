#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     gHook,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    gripper,              tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

void rightTurn()
{
	while(nMotorEncoder[rightDrive] < 2200)
	{
		motor[rightDrive] = 30;
		motor[leftDrive] = -30;
	}
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
}

task main()
	{
	//waitForStart();
	int forwardDistanceRight = 0;
	int forwardDistanceLeft = 0;

	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	// turning when IR is 2 and 8(?)
	while(SensorValue[irSensor] != 2)
	{
		motor[rightDrive] = 20;
		motor[leftDrive] = 20;

		int display = SensorValue[irSensor];
		int right = nMotorEncoder[rightDrive];
		int left = nMotorEncoder[leftDrive];

		nxtDisplayString(0,"%d",display);
		nxtDisplayString(1, "Right: %d                      ", right);
		nxtDisplayString(2, "Left: %d                       ", left);
	}

	wait1Msec(400);

		//motor[rightDrive] = -30;
		//motor[leftDrive] = -30;

	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	wait1Msec(400);

	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;

	rightTurn();

	while(true)
	{
		int display = SensorValue[irSensor];
		int right = nMotorEncoder[rightDrive];
		int left = nMotorEncoder[leftDrive];
		nxtDisplayString(0,"%d",display);
		nxtDisplayString(1, "Right: %d                      ", right);
		nxtDisplayString(2, "Left: %d                       ", left);
	}
}
