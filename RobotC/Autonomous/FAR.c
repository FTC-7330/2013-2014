#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     gHook,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    gripper,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

// Full Autonomous Right
// Pursues the maximum amount of points, starting from the right side.
// Drops the block in the bucket with the IR beacon and proceeds to
// drive on the ramp. Wait time before execution begins can also be specified.
// Boolean competion must be set to true before a competitive match.
//
// Total time - ?? seconds
// Time for dropping block - ?? seconds
// Maximum points - 80

#include "JoystickDriver.c"
#include "Autonomous Functions.h"

const int waitTimeInSec = 0;
const bool competition = false;


task main()
{
	if(competition)
	{
		waitForStart();
	}
	wait1Msec(waitTimeInSec*1000);

	// closes grippet and raises arm
	servo[gripper] = closedGripper;
	wait1Msec(100);
	StartTask(display);
	StartTask(armRaise);

	int distanceRightForward = 0;
	int distanceLeftForward = 0;
	int turnDistanceRight = 0;
	int turnDistanceLeft = 0;

	// drives straight until the IR sensor reads "8"
	drive(0, 0, 90, true);
	while(SensorValue[irSensor] != 8)
	{
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

	// stores the distance each wheel moved forward
	distanceRightForward = nMotorEncoder[rightDrive];
	distanceLeftForward = nMotorEncoder[leftDrive];
	wait1Msec(200);

	// based on whether the bot is past halfway, drives an additional amount
	if(distanceRightForward < 5000)
	{
		distanceRightForward += 1000;
		distanceLeftForward += 1000;
		drive(1900, 1900, 90, false);
	}
	else
	{
		distanceRightForward -= 500;
		distanceLeftForward -= 500;
		drive(1200, 1200, 90, false);
	}

	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	wait1Msec(250);

	// drives toward the buckets until the sonar sensor is under the bucket
	Turn(90);
	motor[rightDrive] = 50;
	motor[leftDrive] = 50;
	while(SensorValue[sonar] > 25)
	{
	}
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;

	// drops the block
	wait1Msec(200);
	servo[gripper] = 240;
	wait1Msec(300);

	// drives back from the bucket
	drive(-2000, -2000, -90, false);
	Turn(90);

	// drves back from the bucket roughly the same distance the bot initially drove
	if(distanceRightForward < 5000)
	{
		drive(distanceRightForward, distanceLeftForward, 90, false);
	}
	else
	{
		drive(distanceRightForward, distanceLeftForward, 90, false);
	}

	// turns and drives on to the ramp
	Turn(-50);
	drive(7100, 7100, 90, false);
	Turn(-100);
	drive(8000, 8000, 90, false);
}
