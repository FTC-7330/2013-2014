#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          gripperMotor,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightMotor,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftMotor,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armMotor,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     spinnerMotor,  tmotorTetrix, openLoop, encoder)
#include "JoystickDriver.c"



task main()
	{
	int counter = 0;
	motor[rightMotor] = 75;
	motor[leftMotor] = 0;
	wait1Msec(1000);
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	motor[rightMotor] = 75;
	motor[leftMotor] = 75;
	wait1Msec(500);
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	motor[rightMotor] = 75;
	motor[leftMotor] = 0;
	wait1Msec(750);
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	motor[rightMotor] = 75;
	motor[leftMotor] = 75;
	wait1Msec(1000);
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	motor[rightMotor] = 0;
	motor[leftMotor] = 75;
	wait1Msec(770);
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;


	while(SensorValue[IRSeeker] != 8)
		{
		motor[rightMotor] = 100;
		motor[leftMotor] = 100;
		wait1Msec(1);
		counter++;
		}
		motor[rightMotor] = 100;
		motor[leftMotor] = 100;
		wait1Msec(900);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		// dropping off the block
		motor[armMotor] = 30;
		wait1Msec(2000);
		motor[armMotor] = 0;

		motor[rightMotor] = -75;
		motor[leftMotor] = 75;
		wait1Msec(1000);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		motor[armMotor] = -30;
		wait1Msec(100);
		motor[armMotor] = 0;
		motor[gripperMotor] = -75;
		wait1Msec(333);
		// getting back
		motor[gripperMotor] = 50;
		wait1Msec(500);
		motor[armMotor] = 30;
		wait1Msec(100);
		motor[armMotor] = 0;

		motor[rightMotor] = 75;
		motor[leftMotor] = -75;
		wait1Msec(970);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		motor[armMotor] = -30;
		wait1Msec(1500);
		motor[armMotor] = 0;

		motor[rightMotor] = -100;
		motor[leftMotor] = -100;
		wait1Msec(2000+counter);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		// getting on the ramp
		motor[rightMotor] = -75;
		motor[leftMotor] = 75;
		wait1Msec(1000);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		motor[rightMotor] = 100;
		motor[leftMotor] = 100;
		wait1Msec(2000);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		motor[rightMotor] = 75;
		motor[leftMotor] = -75;
		wait1Msec(1000);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		motor[rightMotor] = 75;
		motor[leftMotor] = 75;
		wait1Msec(3000);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
	}
