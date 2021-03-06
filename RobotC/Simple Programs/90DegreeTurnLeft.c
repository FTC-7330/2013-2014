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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int encoderTicksPerDegree = 26;

void waitForStop()
	{
	while(nMotorRunState[rightDrive] != runStateIdle && nMotorRunState[leftDrive] != runStateIdle)
		{
		}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
	}

void turn90(int degrees)
	{
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;
	nMotorEncoderTarget[rightDrive] = -degrees*encoderTicksPerDegree;
	nMotorEncoderTarget[leftDrive] = degrees*encoderTicksPerDegree;
	if (degrees < 0)
		{
		motor[rightDrive] = 90;
		motor[leftDrive] = -90;
  	}
  else
  	{
		motor[rightDrive] = -90;
		motor[leftDrive] = 90;
  	}
	waitForStop();
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;
	}

task main()
	{
	while(true)
		{
		if(nNxtButtonPressed == 3)
			{
			wait1Msec(1000);
			turn90(-90);
			wait1Msec(100);
			turn90(-90);
			wait1Msec(100);
			turn90(-90);
			wait1Msec(100);
			turn90(-90);
			}
		if(nNxtButtonPressed == 1)
			encoderTicksPerDegree--;
		if(nNxtButtonPressed == 2)
			encoderTicksPerDegree++;
		}
	}
