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

// competition value: 20
// test value: 23
//right test value:270
//left test value: 260
const int encoderTicksPer10DegreesLeft = 257;
const int encoderTicksPer10DegreesRight = 270;
const int sonarDistance = 0;
const int armRaiseDistance = 1700;
const int armRaiseSpeed = 40;
const int rollingAvgWindow = 5;
const int rollingAvgInterval = 50;

// displays value of the IR sensor, the right and left encoders, and the sonar sensor
task display()
{
    while (true)
    {
    	//Displays information about encoders and IR and sonar sensors
			int display = SensorValue[irSensor];
			int right = nMotorEncoder[rightDrive];
			int left = nMotorEncoder[leftDrive];
			int sonarValue = SensorValue[sonar];

			nxtDisplayString(0,"%d", display);
			nxtDisplayString(1, "Right: %d", right);
			nxtDisplayString(2, "Left: %d", left);
			nxtDisplayString(3, "Sonar: %d", sonarValue);
	  }
}
//continues driving until encoders reach destination, then resets motor speed.
void waitForStop()
{
	while(nMotorRunState[rightDrive] != runStateIdle && nMotorRunState[leftDrive] != runStateIdle)
	{
	}

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}

//resets encoder values; if inputed degree value is positive robot turns right, if negative then the robot turns left.
void Turn(int degrees)
{
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;

	if(degrees>0)
	{
		nMotorEncoderTarget[rightDrive] = -degrees*encoderTicksPer10DegreesRight / 10;
		nMotorEncoderTarget[leftDrive] = degrees*encoderTicksPer10DegreesRight / 10;
	}
	else
	{
		nMotorEncoderTarget[rightDrive] = -degrees*encoderTicksPer10DegreesLeft / 10;
		nMotorEncoderTarget[leftDrive] = degrees*encoderTicksPer10DegreesLeft / 10;
	}

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
// reset encoder values; drives for the distance given at the given speed;
//if runForever is true, drives forever
void drive(int distanceRight, int distanceLeft, int speed, bool runForever)
{
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;


	if (!runForever) //sets encoder targets if not running forever
	{
		nMotorEncoderTarget[rightDrive] = distanceRight;
		nMotorEncoderTarget[leftDrive] = distanceLeft;
	}
	else
	{
		nMotorEncoderTarget[rightDrive] = 0;
		nMotorEncoderTarget[leftDrive] = 0;
	}

	motor[rightDrive] = speed;
	motor[leftDrive] = speed;

	if (!runForever) //stops when target is reached.
	{
		waitForStop();
	}

	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;
}

// drives arm for given distance for given speed
void driveArm(int distanceUp, int speed)
{
	nMotorEncoder[arm] = 0;
	nMotorEncoderTarget[arm] = distanceUp;
	motor[arm] = speed;

	while(nMotorRunState[arm]!=runStateIdle)
	{
	}
	motor[arm] = 0;

	nMotorEncoder[arm] = 0;
}


//raises arm as a task, allowing it to be done while driving forwards
// calls driveArm method as a task with parameters defined as constants
task armRaise()
{
	driveArm(armRaiseDistance, armRaiseSpeed);
}

// uses rolling averages to detect when the motors are in danger (they are running
// but the robot isn't moving); if this situation is detected the motors are stopped
task driveFailSafe()
{
	// *** need to add more zeros when window changes
	int encoderChange[rollingAvgWindow] = {0, 0, 0, 0, 0};
	int index = 0;
	int oldEncoderValue = nMotorEncoder[leftDrive];
	int oldPower = motor[leftDrive];
	int rollingSum = 0;

	wait1Msec(rollingAvgInterval);

	while(true)
	{
		// sets the "new" values
		int newEncoderValue = nMotorEncoder[leftDrive];
		int newPower = motor[leftDrive];

		// updates the average and the array that keeps track of the rolling sum
		rollingSum += (oldEncoderValue - newEncoderValue) - encoderChange[index];
		encoderChange[index] = oldEncoderValue - newEncoderValue;

		// if the power has changed, fills the array with the most recent encoder
		// change
	  if (oldPower != newPower)
		{
			for (int i = 0; i < rollingAvgWindow; i++)
			{
				encoderChange[i] = encoderChange[index];
			}
			rollingSum = encoderChange[index] * rollingAvgWindow;
		}

		// breaks from the loop if the most recent encoder change is significantly
		// lower than expected
		if(encoderChange[index] < (rollingSum / rollingAvgWindow) * 0.5)
		{
			break;
	 	}

	 	// updates the index that signifies which element of the array to change
		if (index < rollingAvgWindow)
	  {
			index++;
		}
		else
		{
			index = 0;
	  }

	  // sets "old" values to the "new" values and waits
  	oldEncoderValue = newEncoderValue;
  	oldPower = newPower;
  	wait1Msec(rollingAvgInterval);
	}

	// sets the motors to zero
	while (true)
	{
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}
}
