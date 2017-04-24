#pragma config(Sensor, S1,     Touch,          sensorTouch)
#pragma config(Sensor, S2,     GYRO_SENSOR,    sensorAnalog)
#pragma config(Sensor, S4,     HALL_EFFECT,    sensorAnalog)
#include "Function_Library.h"
task main()
{/* 0: N
	 1: NE
	 2: E
	 3: SE
	 4: S
	 5: SW
	 6: W
	 7: NW
	 */
	float angle = 0.0;
	float x = 0.0;
	float y = 0.0;
	float temp_x = 0.0;
	float temp_y = 0.0;
	int direction = 7;
	TaskTurnEast(direction);
	wait(2);
	angle = Reset(60, 204, &x, &y);
	TaskTurnEncoder(-angle);
	TaskDriveBackward(10, 80);
	TaskDropOneBin();
	TaskDriveForward(10, 80);
	wait(1);
	temp_x = x;
	temp_y = y;
	//TaskBeaconSearch();
	angle = Reset(229, 205, &x, &y);
	TaskTurnEncoder(-angle);
	wait(1);
	angle = Reset(256, 147, &x, &y);
	TaskTurnEncoder(-angle);
	TaskDriveBackward(10, 80);
	TaskDropOneBin();
	TaskDriveForward(10, 80);
	wait(1);
	//TaskBeaconSearch();
	angle = Reset(320, 147, &x, &y);
	TaskTurnEncoder(-angle);
	wait(1);
	angle = Reset(320, 56, &x, &y);
	TaskTurnEncoder(-angle);
	wait(1);
	angle = Reset(301, 56, &x, &y);
	TaskTurnEncoder(-angle);
	TaskDriveBackward(10, 80);
	TaskDropOneBin();
	TaskDriveForward(10, 80);
	wait(1);
	//TaskBeaconSearch();
	angle = Reset(278, 20, &x, &y);
	TaskTurnEncoder(-angle);
	wait(1);
	angle = Reset(145, 20, &x, &y);
	TaskTurnEncoder(-angle);
	while ((fabs(temp_x - x) > 10.0) || (fabs(temp_y - x) > 10.0)) {
	    wait(1);
	    angle = Reset(temp_x, temp_y, &x, &y);
	    TaskTurnEncoder(-angle);
	  }
}
