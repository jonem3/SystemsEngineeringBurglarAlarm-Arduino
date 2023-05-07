#include <sensor.h>

sensor::sensor(int pin, String name)
{
    //setting variables to inputed data
    SensorName = name;
    SensorPin = pin;
}

sensor::sensor(int pin, String name, bool mirror)
{
    // construcor 2 for if output of sensor needs to be inverted
    SensorName = name;
    SensorPin = pin;
    isMirrored = mirror;
}

void sensor::setup()
{
    //assigning pin to input with internal resistace 
    pinMode(SensorPin, INPUT_PULLUP);
}

int sensor::readSensor()
{
    //returns the sensor output, inverts if needed
    SensorStatus = digitalRead(SensorPin);
    if (!isMirrored)
    {
        return SensorStatus;
    }
    else
    {
        return !SensorStatus;
    }
}

String sensor::getName()
{
    //this returns which sensor is being read
    return SensorName;
}