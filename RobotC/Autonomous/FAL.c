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

// Full Autonomous Left
// Pursues the maximum amount of points, starting from the left side.
// Drops the block in the bucket with the IR beacon and proceeds to
// drive on the ramp. Wait time before execution begins can also be specified.
// Boolean competion must be set to true before a competitive match.
//
// Total time - 20 seconds
// Time for dropping block - 10 seconds
// Maximum points - 80

#include "JoystickDriver.c"
#include "Autonomous Functions.h"

const bool competition = false;
const int waitTimeInSec = 0;

task main()
{
	if(competition)
	{
		waitForStart();
	}
	wait1Msec(waitTimeinSec*1000);

	// closes gripper and raises arm
	servo[gripper] = closedGripper;
	wait1Msec(100);
	StartTask(display);
	StartTask(armRaise);

	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	int distanceForwardRight = 0;
	int distanceForwardLeft = 0;
	int turnDistanceRight = 0;
	int turnDistanceLeft = 0;

	// drive straight until the IR sensor reads "2"
	drive(0, 0, 90, true);
	while(SensorValue[irSensor] != 2)
	{
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
	wait1Msec(200);

	// store the distance each wheel drives forward
	distanceForwardRight = nMotorEncoder[rightDrive];
	distanceForwardLeft = nMotorEncoder[leftDrive];

	// based on whether the bot is past halfway, drives an additional amount
	if(distanceForwardRight < 5000)
	{
		drive(1200, 1200, 90, false);
	}
	else
	{
		drive(400, 400, 90, false);
	}

	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	wait1Msec(250);

	Turn(-90);

	motor[rightDrive] = 50;
	motor[leftDrive] = 50;

	// drives toward the buckets until the sonar sensor is under the bucket
	while(SensorValue[sonar] > 25)
	{
	}
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;

	// stores the distance driven
	turnDistanceRight = nMotorEncoder[rightDrive] - 300;
	turnDistanceLeft = nMotorEncoder[leftDrive] - 300;

	// drops the block in the bucket
	wait10Msec(100);
	servo[gripper] = 240;
	wait1Msec(300);

	// drves back from the bucket roughly the same distance the bot initially drove
	drive(-turnDistanceRight - 500, -turnDistanceLeft - 500, -90, false);
	Turn(-90);

	// drives back to the starting location roughly the same distance the bot initially drove
	drive(distanceForwardRight + 800, distanceForwardLeft + 800, 90, false);

	// turns and drives on to the ramp
	Turn(70);
	drive(6000, 6000, 90, false);
	Turn(110);
	drive(6800, 6800, 90, false);
}
