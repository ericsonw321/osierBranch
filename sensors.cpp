#include "sensor.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
using std::stringstream;
using std::fstream;

Sensor::Sensor()
{
    cur_voltage = 0;
	diff_degreesC = 0;
	ain = 0;
}

int Sensor::readAnalog(int number)
{
    stringstream ss;
    ss << LDR_PATH << number << "_raw";
    fstream fs;
    fs.open(ss.str().c_str(), fstream::in);
    fs >> number;
    fs.close();
    return number;
}

float Sensor::degreesC(float adc_value)
{
	float degrees;
    float cur_voltage = adc_value * (1.80f/4096.0f);
    float diff_degreesC = (cur_voltage-0.75f)/0.01f;
    degrees = (25.0f + diff_degreesC);
    return degrees;
}

float Sensor::degreesF(float adc_value)
{
	float degrees;
    float cur_voltage = adc_value * (1.80f/4096.0f);
    float diff_degreesC = (cur_voltage-0.75f)/0.01f;
    degrees = (25.0f + diff_degreesC);
    degrees = (degrees * 1.8) + 32;
    return degrees;
}