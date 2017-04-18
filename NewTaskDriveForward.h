#define MOTOR_LEFT  motorC
#define MOTOR_RIGHT motorB


void TaskDriveForward(float distance, int power)
{
	int encoder_left = 0;
  int encoder_right = 0;
  float delta = 0.0;
  nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;
  distance = (distance + 2.54) / .0256;
	// Start by driving both motors at same speed
	// A static integer is initialised only the first
	// time this code is executed, then keeps its
	// value until changed.
	while (nMotorEncoder[MOTOR_LEFT] < distance) {
    encoder_left  = nMotorEncoder[MOTOR_LEFT];
  	encoder_right = nMotorEncoder[MOTOR_RIGHT];
	  static int state = 0;

	  /* First Half: Ramping up */
		if (nMotorEncoder[MOTOR_LEFT] < (0.45 * distance)) {
  		if (delta < 60) {
  			delta += 0.25;
  			nxtDisplayString(1, "Delta: %lf", delta);

  		}
  		else {
  			delta = 60;
  		}
  	}
  	/* Second Half: Ramping down */
  	else if (nMotorEncoder[MOTOR_LEFT] < 4000) {
  		if (delta > 0) {
  			delta -= 0.25;
  		}
  		else {
  			delta = 0;
  		}
  	}

	  switch (state)
	  {
	  case 0:  // going straight
		  motor[MOTOR_LEFT]= power + delta;
		  motor[MOTOR_RIGHT]= power + delta;
		  break;

	  case 1:   // drifting to the right
		  motor[MOTOR_LEFT]= (power - 10) + delta;
		  motor[MOTOR_RIGHT]= (power + 5) + delta;
		  nxtDisplayString(4, "LEFT");
		  break;

	  case 2:     // drifting to the left
		  motor[MOTOR_LEFT]= power + delta;
		  motor[MOTOR_RIGHT]= (power - 10) + delta;
		  nxtDisplayString(4, "RIGHT");
		  break;
	  } // end switch

	// Read Motor Encoders and chose next movement
	  if (nMotorEncoder[MOTOR_LEFT] == nMotorEncoder[MOTOR_RIGHT])  { state = 0; }  // Go straight
	  else if (nMotorEncoder[MOTOR_LEFT] > nMotorEncoder[MOTOR_RIGHT])  { state = 1; } // Turn left
	  else if (nMotorEncoder[MOTOR_LEFT] < nMotorEncoder[MOTOR_RIGHT])  { state = 2; } // Turn right
	  //nxtDisplayString(1, "L rot cnt: %i", encoder_left);
		//nxtDisplayString(2, "R rot cnt: %i", encoder_right);
	  //wait1Msec(40);
		//eraseDisplay();
	  wait10Msec(2);
	}
	nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;
	motor[MOTOR_LEFT] = 0;
	motor[MOTOR_RIGHT] = 0;
	wait1Msec(20);
	return;
}
