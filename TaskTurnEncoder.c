#define MOTOR_LEFT  motorC
#define MOTOR_RIGHT motorB

void TaskTurnEncoder(float angle);

task main() {
	TaskTurnEncoder(90); // degrees
	TaskTurnEncoder(-90);
	TaskTurnEncoder(180);
	TaskTurnEncoder(-180);
}

void TaskTurnEncoder(float angle) {
	/* Declare and initialize constants and variables */
	float const radiusALV = 6.913; // cm
	float const diamWheel = 8.274; // cm
	float const gearRatio = 0.333;
	float const startMotor = 20.0;
	float const offset = (9.0 / 90.0) * abs(angle);
	float delta = 0.0;
	float ticks = 0.0;
	float direction = 0.0;
	float targetTicks = 0.0;

	/* Reset encoders and calculate target ticks */
  nMotorEncoder[MOTOR_LEFT] = 0;
  nMotorEncoder[MOTOR_RIGHT] = 0;
  direction = angle / abs(angle);
  targetTicks = (2.0 * (abs(angle) + offset) * radiusALV) / (diamWheel * gearRatio);

	/* Turning algorithm to ramp motor power linearly based on time */
	ticks = 0.0;
	delta = 0.0;
	while (ticks < targetTicks) {
		motor[MOTOR_LEFT] = (startMotor + delta) * direction;
  	motor[MOTOR_RIGHT] = -(startMotor + delta) * direction;

  	/* First Half: Ramping up */
		if (ticks < 0.5 * targetTicks) {
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
  	wait1Msec(25);
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
