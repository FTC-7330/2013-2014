#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     gHook,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    gripper,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task display()
{

    while (true)
    {
			int display = SensorValue[irSensor];
			int right = nMotorEncoder[rightDrive];
			int left = nMotorEncoder[leftDrive];

			nxtDisplayString(0,"%d",display);
			nxtDisplayString(1, "Right: %d                      ", right);
			nxtDisplayString(2, "Left: %d                       ", left);
			wait10Msec(10);
	  }
}

void waitForStop()
{
	while(nMotorRunState[rightDrive] != runStateIdle && nMotorRunState[leftDrive] != runStateIdle)
	{
	}

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;


}

// competition value: 20
// test value: 23
const int encoderTicksPerDegree = 23;

// right turn is positive degrees, left turn is negative.
void Turn(int degrees)
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
void drive(int distanceRight, int distanceLeft,int speed, bool forward)
{
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;

	nMotorEncoderTarget[rightDrive] = distanceRight;
	nMotorEncoderTarget[leftDrive] = distanceLeft;

	if(forward)
	{
		motor[rightDrive] = speed;
		motor[leftDrive] = speed;
	}
	else
	{
		motor[rightDrive] = -speed;
		motor[leftDrive] = -speed;
	}

	waitForStop();

	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;
}

task armRaise()
{
	motor[arm] = -30;
	wait1Msec(1400);
	motor[arm] = 0;
}
task main()
{
	//waitForStart();
	servo[gripper] = 85;
	wait1Msec(100);
	StartTask(display);
	StartTask(armRaise);

	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	drive(2000, 2000, 90, true);
	wait1Msec(300);
	servo[gripper] = 240;
	drive(-500, -500, -90, true);
	Turn(-90);
	drive(500, 500, 90, true);
	Turn(90);
	drive(1000, 1000, 90, true);
}