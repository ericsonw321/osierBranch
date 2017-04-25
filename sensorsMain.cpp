#include "sensor.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    Sensor temp;
    Sensor light;

    cout << "Fahrenheit: " << temp.degreesF(temp.readAnalog(1)) << endl;
    cout << "Celsius: " << temp.degreesC(temp.readAnalog(1)) << endl;

    cout << "Light " << light.readAnalog(0) << endl;

    return 0;
}