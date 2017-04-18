#define MOTOR_LEFT  motorC
#define MOTOR_RIGHT motorB

void TaskDriveForwardEncoder(float distance);

task main() {
	TaskDriveForwardEncoder(75.0); // cm
}

void TaskDriveForwardEncoder(float distance) {
	/* Declare and initialize constants and variables */
	float const diamWheel = 8.274; // cm
	float const gearRatio = 0.333;
	float const startMotor = 20.0;
	float delta = 0.0;
	float ticks = 0.0;
	float targetTicks = 0.0;
	int n = 0;
	int k = 0;

	/* Reset encoders and calculate target ticks */
  nMotorEncoder[MOTOR_LEFT] = 0;
  nMotorEncoder[MOTOR_RIGHT] = 0;
  //targetTicks = (360.0 * abs(distance)) / (diamWheel * gearRatio);
  targetTicks = (distance + 2.54) / .0256

	/* Drive forward algorithm to ramp motor power linearly based on time */
	ticks = 0.0;
	delta = 0.0;
	n = 0;
	k = 0;
	while (ticks < targetTicks) {
    nxtDisplayString(1, "Ticks: %lf" , ticks);
		/* Adjust motor powers based on encoder values */
		if(fabs(nMotorEncoder[MOTOR_LEFT] - nMotorEncoder[MOTOR_RIGHT]) == 0) {}
  	else if (abs(nMotorEncoder[MOTOR_LEFT]) < abs(nMotorEncoder[MOTOR_RIGHT])) {
  		++n;
  		--k;
  	}
  	else {
  		--n;
  		++k;
    }
  	motor[MOTOR_LEFT] = startMotor + delta + n;
  	motor[MOTOR_RIGHT] = startMotor + delta + k;

  	/* First Half: Ramping up */
		if (ticks < 0.45 * targetTicks) {
  		if (delta < 60) {
  			delta += 0.5;
  		}
  		else {
  			delta = 60;
  		}
  	}
  	/* Second Half: Ramping down */
  	else {
  		if (delta > 0) {
  			delta -= 0.5;
  		}
  		else {
  			delta = 0;
  		}
  	}
  	/* Wait and find avaerage ticks between encoders */
  	wait1Msec(200);
  	ticks = (abs(nMotorEncoder[MOTOR_LEFT])
	         + abs(nMotorEncoder[MOTOR_RIGHT])) / 2;
  }
  /* Motor powers to zero and reset encoders */
  motor[MOTOR_LEFT] = 0;
  motor[MOTOR_RIGHT] = 0;
  nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;

  return;
}
