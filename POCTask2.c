#pragma config(Sensor, S1,     Touch,          sensorTouch)
#pragma config(Sensor, S2,     GYRO_SENSOR,    sensorAnalog)
#pragma config(Sensor, S4,     HALL_EFFECT,    sensorAnalog)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// drive_forward_straight_line.c
// RobotC for Mindstorms NXT
//
// Drive forward in a straight line
// [David Butterworth, 2012]
//
// This program will loop forever.
// Both motors are driven at the same speed,
// but if one motor is rotating faster than
// the other, the opposite motor will be
// driven faster to compensate.
//
// The result is that the robot drives
// forward with a slight wiggling motion,
// but the resulting motion is much straighter
// than without using the encoders.

#define MOTOR_PORT_LEFT  motorC
#define MOTOR_PORT_RIGHT motorB
#define BIN_MOTOR motorA
#define PI (4.0 * atan(1.0))
void TaskDriveForward(float distance, int power);
void TaskTurnLeft(float angle);
void TaskTurnRight(float angle);
void TaskDropOneBin();
int GetCoordinates(int height, float* x, float* y);
void TaskTurnCircle(float radius, float fraction, char direction);
float Reset(float x_coor, float y_coor);
void TaskBeaconSearch();
void TaskBeep(int numBeeps);
void TaskDriveBackward(float distance, int power);
task main()
{
float angle = 0.0;
angle = Reset(135, 15);
TaskTurnLeft(90 + angle);
TaskDriveForward(72, 80);
TaskBeep(4);
TaskDriveBackward(72, 80);
TaskTurnLeft(90);
TaskDriveForward(110, 80);
TaskBeep(3);
}
void TaskDriveForward(float distance, int power)
{
	int encoder_left = 0;
  int encoder_right = 0;
  nMotorEncoder[MOTOR_PORT_LEFT] = 0;
	nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
  distance = (distance + 2.54) / .0256;
	// Start by driving both motors at same speed
	// A static integer is initialised only the first
	// time this code is executed, then keeps its
	// value until changed.
	while (nMotorEncoder[MOTOR_PORT_LEFT] < distance) {
    encoder_left  = nMotorEncoder[MOTOR_PORT_LEFT];
  	encoder_right = nMotorEncoder[MOTOR_PORT_RIGHT];
	  static int state = 0;

	  switch (state)
	  {
	  case 0:  // going straight
		  motor[MOTOR_PORT_LEFT]= power;
		  motor[MOTOR_PORT_RIGHT]= power;
		  displayText(4, "FWD");
		  break;

	  case 1:   // drifting to the right
		  motor[MOTOR_PORT_LEFT]= power - 20;
		  motor[MOTOR_PORT_RIGHT]= power + 10;
		  nxtDisplayString(4, "LEFT");
		  break;

	  case 2:     // drifting to the left
		  motor[MOTOR_PORT_LEFT]= power;
		  motor[MOTOR_PORT_RIGHT]= power - 20;
		  nxtDisplayString(4, "RIGHT");
		  break;
	  } // end switch

	// Read Motor Encoders and chose next movement
	  if (nMotorEncoder[MOTOR_PORT_LEFT] == nMotorEncoder[MOTOR_PORT_RIGHT])  { state = 0; }  // Go straight
	  else if (nMotorEncoder[MOTOR_PORT_LEFT] > nMotorEncoder[MOTOR_PORT_RIGHT])  { state = 1; } // Turn left
	  else if (nMotorEncoder[MOTOR_PORT_LEFT] < nMotorEncoder[MOTOR_PORT_RIGHT])  { state = 2; } // Turn right
	  nxtDisplayString(1, "L rot cnt: %i", encoder_left);
		nxtDisplayString(2, "R rot cnt: %i", encoder_right);
	  wait1Msec(40);
		eraseDisplay();
	}
	nMotorEncoder[MOTOR_PORT_LEFT] = 0;
	nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
	motor[MOTOR_PORT_LEFT] = 0;
	motor[MOTOR_PORT_RIGHT] = 0;
	wait10Msec(2);
	return;
}
void TaskDriveBackward(float distance, int power)
{
	int encoder_left = 0;
  int encoder_right = 0;
  nMotorEncoder[MOTOR_PORT_LEFT] = 0;
	nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
  distance = (distance + 2.54) / .0256;
	// Start by driving both motors at same speed
	// A static integer is initialised only the first
	// time this code is executed, then keeps its
	// value until changed.
	while (abs(nMotorEncoder[MOTOR_PORT_LEFT]) < distance) {
    encoder_left  = nMotorEncoder[MOTOR_PORT_LEFT];
  	encoder_right = nMotorEncoder[MOTOR_PORT_RIGHT];
	  static int state = 0;

	  switch (state)
	  {
	  case 0:  // going straight
		  motor[MOTOR_PORT_LEFT]= -power;
		  motor[MOTOR_PORT_RIGHT]= -power;
		  displayText(4, "FWD");
		  break;

	  case 1:   // drifting to the right
		  motor[MOTOR_PORT_LEFT]= -(power - 20);
		  motor[MOTOR_PORT_RIGHT]= -(power + 10);
		  nxtDisplayString(4, "LEFT");
		  break;

	  case 2:     // drifting to the left
		  motor[MOTOR_PORT_LEFT]= -power;
		  motor[MOTOR_PORT_RIGHT]= -(power - 20);
		  nxtDisplayString(4, "RIGHT");
		  break;
	  } // end switch

	// Read Motor Encoders and chose next movement
	  if (abs(nMotorEncoder[MOTOR_PORT_LEFT]) == abs(nMotorEncoder[MOTOR_PORT_RIGHT]))  { state = 0; }  // Go straight
	  else if (abs(nMotorEncoder[MOTOR_PORT_LEFT]) > abs(nMotorEncoder[MOTOR_PORT_RIGHT]))  { state = 1; } // Turn left
	  else if (abs(nMotorEncoder[MOTOR_PORT_LEFT]) < abs(nMotorEncoder[MOTOR_PORT_RIGHT]))  { state = 2; } // Turn right
	  nxtDisplayString(1, "L rot cnt: %i", encoder_left);
		nxtDisplayString(2, "R rot cnt: %i", encoder_right);
	  wait1Msec(40);
		eraseDisplay();
	}
	nMotorEncoder[MOTOR_PORT_LEFT] = 0;
	nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
	motor[MOTOR_PORT_LEFT] = 0;
	motor[MOTOR_PORT_RIGHT] = 0;
	wait10Msec(2);
	return;
}
void TaskTurnLeft(float angle) {
	float encoder_left = 0;
  float encoder_right = 0;
  angle = angle * 4.65  + 9.33;
  nmotorEncoder[MOTOR_PORT_LEFT] = 0;
  nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
  while (abs(encoder_left) < angle) {
  	encoder_left  = nMotorEncoder[MOTOR_PORT_LEFT];
  	encoder_right = nMotorEncoder[MOTOR_PORT_RIGHT];
    motor[MOTOR_PORT_LEFT] = -80;
  	motor[MOTOR_PORT_RIGHT] = 80;
  	nxtDisplayString(1, "L rot cnt: %i", encoder_left);
		nxtDisplayString(2, "R rot cnt: %i", encoder_right);
		wait1Msec(40);
		eraseDisplay();
  }
  nMotorEncoder[MOTOR_PORT_LEFT] = 0;
	nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
	return;
}
void TaskTurnRight(float angle) {
	float encoder_left = 0;
  float encoder_right = 0;
  nMotorEncoder[MOTOR_PORT_LEFT] = 0;
  nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
  angle = angle * 4.65 + 9.33;
  while (abs(encoder_right) < angle) {
  	encoder_left  = nMotorEncoder[MOTOR_PORT_LEFT];
  	encoder_right = nMotorEncoder[MOTOR_PORT_RIGHT];
  	motor[MOTOR_PORT_LEFT] = 80;
  	motor[MOTOR_PORT_RIGHT] = -80;
  	nxtDisplayString(1, "L rot cnt: %i", encoder_left);
		nxtDisplayString(2, "R rot cnt: %i", encoder_right);
		wait1Msec(40);
		eraseDisplay();
  }
  nMotorEncoder[MOTOR_PORT_LEFT] = 0;
	nMotorEncoder[MOTOR_PORT_RIGHT] = 0;
  motor[MOTOR_PORT_LEFT] = 0;
  motor[MOTOR_PORT_RIGHT] = 0;
	return;
}
void TaskDropOneBin()
{
	int encoder_next = 0;
  int encoder_bin = 1;
  motor[MOTOR_PORT_LEFT] = 0;
	motor[MOTOR_PORT_RIGHT] = 0;
	while ((sensorValue[Touch]) == 0) {
		encoder_bin = nMotorEncoder[BIN_MOTOR];
		motor[BIN_MOTOR] = -30;
	}
	nMotorEncoder[BIN_MOTOR] = 0;
	while (encoder_bin < 610) {
		encoder_bin = nMotorEncoder[BIN_MOTOR];
		motor[BIN_MOTOR] = 20;
	}
	while ((sensorValue[Touch]) == 0) {
		encoder_bin = nMotorEncoder[BIN_MOTOR];
		motor[BIN_MOTOR] = -20;
	}
	return;
}
int GetCoordinates(int height, float* x, float* y) {
  int x_coor = 0;
  int y_coor = 0;
  short i = 0;
  int value = 0;
  int state = 0;
  ClearMessage();
  sendMessage(height);
  while (message == 0) {
	  nxtDisplayString(1, "Waiting for message");
	  wait1Msec(40);
	  eraseDisplay();
  }
  nxtDisplayString(1, "Message Recieved");
  wait(3);
  eraseDisplay();
  value = messageParm[0];
  for(i = 1 ; i <= 32; i *= 2) {
	  switch (i & value) {
	  	case (1) :
	  	  nxtDisplayString(1,"No error");
	  	  state = 1;
	  	  break;
	  	case (2) :
	  	  nxtDisplayString(1,"Error: MO");
	  	  state = 1;
	  	  break;
	  	case (4) :
	  	  nxtDisplayString(2,"Error: OB XY INV");
	  	  state = 0;
	  	  break;
	  	case (8) :
	  	  nxtDisplayString(3,"Error: NM XY INV");
	  	  state = 0;
	  	  break;
	  	case (16):
	  	  nxtDisplayString(4,"Error: SE XY INV");
	  	  state = 0;
	  	  break;
	  	case (32):
	  	  nxtDisplayString(5,"Busy XY INV");
	  	  state = 0;
	  	  break;
	  	}
	  }
  wait(3);
  eraseDisplay();
  nxtDisplayString(1, "%i", messageParm[0]);
  *x = messageParm[1];
  *y = messageParm[2];
  x_coor = messageParm[1];
  y_coor = messageParm[2];
  ClearMessage();
  nxtDisplayString(1, "x = %i", x_coor);
  nxtDisplayString(2, "y = %i", y_coor);
  wait(3);
  eraseDisplay();
  return state;
}
float Reset(float x_coor, float y_coor){
	float x = 0.0;
  float y = 0.0;
  float dx = 0.0;
  float dy = 0.0;
  float angle = 0.0;
  float distance = 0.0;
  int state = 0;
  while (state == 0) {
    state = GetCoordinates(50, &x, &y);
    if (state == 0) {
    	wait(5);
    }
  }
  dx = x_coor - x / 10.0;
  dy = y / 10.0 - y_coor;
  angle = atan(dy / dx);
  distance = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
  angle = angle * (180 / PI);
  nxtDisplayString(1, "Angle = %.02lf", angle);
  nxtDisplayString(2, "Distance = %.02lf", distance);
  wait(1);
  eraseDisplay();
  TaskTurnRight(angle);
  TaskDriveForward(distance, 80);
  return angle;
}
void TaskTurnCircle(float radius, float fraction, char direction) {
  float ratio = 0.0;
  float distance = 0.0;
  distance = ((radius + 0.5 * 6.78) * fraction * PI);
  distance =  (distance + 2.54) / .0235;
  if (direction == 'R') {
  	while (nMotorEncoder[MOTOR_PORT_LEFT] < distance) {
  	  ratio = (radius + 6.78) / (radius - 6.78);
  		motor[MOTOR_PORT_LEFT] = 80 * ratio;
  		motor[MOTOR_PORT_RIGHT] = 80 / ratio;
  	}
  }
  else {
  	while (nMotorEncoder[MOTOR_PORT_LEFT] < distance) {
  		ratio = (radius + 6.78) / (radius - 6.78);
  		motor[MOTOR_PORT_RIGHT] = 80 * ratio;
  		motor[MOTOR_PORT_LEFT] = 80 / ratio;
  	}
  }
  motor[MOTOR_PORT_LEFT] = 0;
  motor[MOTOR_PORT_RIGHT] = 0;
}
void TaskBeaconSearch() {
 int state = 1;
 motor[MOTOR_PORT_LEFT] = 0;
 motor[MOTOR_PORT_RIGHT] = 0;
 while (state) {
    int sensorVal = 0;
  	sensorVal = SensorValue[HALL_EFFECT];
  	motor[MOTOR_PORT_LEFT] = 50;
  	motor[MOTOR_PORT_RIGHT] = 50;
    nxtDisplayString(1, "HALL VALUE: %d", sensorVal);
    if (sensorVal < 469) {
    	nxtDisplayString(2, "BEACON DETECTED. PERFORMING SEARCH.");
    	wait1Msec(40);
    	eraseDisplay();
    	motor[MOTOR_PORT_LEFT] = 40;
    	motor[MOTOR_PORT_RIGHT] = 40;
    	nMotorEncoder[MOTOR_PORT_LEFT] = 0;
    	while (nMotorEncoder[MOTOR_PORT_LEFT] < 411.7) {
    		sensorVal = SensorValue[HALL_EFFECT];
    		if (sensorVal > 600) {
    			motor[MOTOR_PORT_LEFT] = 0;
    			motor[MOTOR_PORT_RIGHT] = 0;
    		  nxtDisplayString(1, "BEACON LOCATED!!! DROPPING BIN");
    		  wait(1);
    		  eraseDisplay();
    		  TaskTurnRight(180);
    		  TaskDropOneBin();
    			state = 0;
    		}
    	}
    	motor[MOTOR_PORT_LEFT] = 0;
    	motor[MOTOR_PORT_RIGHT] = 0;
    	nxtDisplayString(1, "NO BEACON FOUND! DROPPING");
    	wait(1);
    	eraseDisplay();
      TaskTurnRight(180);
      TaskDropOneBin();
      TaskDriveForward(20, 80);
    	state = 0;
    }
    wait1Msec(40);
    eraseDisplay();
 }
}
void TaskBeep(int numBeeps) {

  while(numBeeps > 0)  // while a sound is actively playing:
  {
	  playSound(soundBlip);
	  wait(1);
	  numBeeps = numBeeps - 1;
	}
  // do not continue until finished playing sound
}