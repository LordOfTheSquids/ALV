#pragma config(Sensor, S2,     GYRO_SENSOR,    sensorAnalog)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{int gyro_val = 0;
  while (1) {
  	gyro_val = SensorValue[GYRO_SENSOR];
  	gyro_val = gyro_val - 598;
    nxtDisplayString(3, "Gyro Read: %i", gyro_val);
		wait1Msec(40);
		eraseDisplay();
	}
}