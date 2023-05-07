#include <sensor.h>

sensor::sensor(int pin, String name)
{
    SensorName = name;
    SensorPin = pin;
}

sensor::sensor(int pin, String name, bool mirror)
{
    SensorName = name;
    SensorPin = pin;
    isMirrored = mirror;
}

void sensor::setup()
{
    pinMode(SensorPin, INPUT_PULLUP);
}

int sensor::readSensor()
{
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
    return SensorName;
}