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
//*!!Code automatically generated by 'ROBOTC' configuration wizard                !!*//
// This is for the NXT model, not TETRIX

/************************************\
|*  Robot Virtual World Template    *|
|*                                  *|
|*  DO NOT OVERWRITE THIS FILE      *|
|*  MAKE SURE TO "SAVE AS" INSTEAD  *|
\************************************/

task main() {}

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
const int encoderTicksPer10Degrees = 260;
int sonarDistance = 0;
// right turn is positive degrees, left turn is negative.
void Turn(int degrees)
{
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;

	nMotorEncoderTarget[rightDrive] = -degrees*encoderTicksPer10Degrees / 10;
	nMotorEncoderTarget[leftDrive] = degrees*encoderTicksPer10Degrees / 10;

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

void drive(int distanceRight, int distanceLeft,int speed)
{
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;

	nMotorEncoderTarget[rightDrive] = distanceRight;
	nMotorEncoderTarget[leftDrive] = distanceLeft;

		motor[rightDrive] = speed;
		motor[leftDrive] = speed;


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
	driveArm(1700, 40);
}
