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

task display()
{

    while (true)
    {
			int display = SensorValue[irSensor];
			int right = nMotorEncoder[rightDrive];
			int left = nMotorEncoder[leftDrive];
			int sonarValue = SensorValue[sonar];

			nxtDisplayString(0,"%d",display);
			nxtDisplayString(1, "Right: %d                      ", right);
			nxtDisplayString(2, "Left: %d                       ", left);
			nxtDisplayString(3, "Sonar: %d       ", sonarValue);
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
const int encoderTicksPerDegree = 24;
int sonarDistance = 0;
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
void driveNoWait(int distanceRight, int distanceLeft,int speed, bool forward)
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
}
void driveArm(int distanceUp, int speed)
{
	nMotorEncoder[arm] = 0;

	nMotorEncoderTarget[arm] = distanceUp;

	motor[arm]=speed;

	while(nMotorRunState[arm]!=runStateIdle)
	{
	}
	motor[arm]=0;

	nMotorEncoder[arm] = 0;
}

task armRaise()
{
	driveArm(1800, 40);
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

	int distanceForwardRight = 0;
	int distanceForwardLeft = 0;
	int turnDistanceRight = 0;
	int turnDistanceLeft = 0;

	// turning when IR is 2 and 8(?)
	//motor[leftDrive]=90;
	//motor[rightDrive]=90;
	driveNoWait(19000,19000,90,true);
	while(SensorValue[irSensor] != 8)
	{
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
	wait1Msec(200);
	distanceForwardRight = nMotorEncoder[rightDrive];
	distanceForwardLeft = nMotorEncoder[leftDrive];

	if(distanceForwardRight < 5000)
	{
		drive(750, 750, 90, true);
		sonarDistance = 25;
	}
	else
	{
		drive(-750,-750,90,false);
		sonarDistance = 30;
	}

	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	wait1Msec(250);

	Turn(90);

	motor[rightDrive] = 50;
	motor[leftDrive] = 50;
	//driveNoWait(2000,2000,50,true);
	while(SensorValue[sonar] > sonarDistance)
	{
	}
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	turnDistanceRight = nMotorEncoder[rightDrive];
	turnDistanceLeft = nMotorEncoder[leftDrive];
	wait10Msec(100);
	servo[gripper] = 240;
	wait1Msec(300);
	drive(-turnDistanceRight, -turnDistanceLeft, 90, false);
	Turn(90);
	drive(distanceForwardRight + 700, distanceForwardLeft + 700, 90, true);
	Turn(-55);
	drive(6000, 6000, 90, true);
	Turn(-120);
	drive(7800, 7800, 90, true);
}
