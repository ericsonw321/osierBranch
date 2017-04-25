#pragma once

#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

class Sensor{
private:
	float cur_voltage;
	float diff_degreesC;
	int ain;
public:
	Sensor();
	int readAnalog(int);
	float degreesC(float);
	float degreesF(float);
};