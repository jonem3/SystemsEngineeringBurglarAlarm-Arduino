#include <solenoid.h>
solenoid::solenoid(int solenoidPin)
{
    // Assign the pin property the value of the pin the solenoid is attached to
    pin = solenoidPin;
}

void solenoid::setup()
{
    // Run Pin Mode Declaration
    pinMode(pin, OUTPUT);
}

void solenoid::powerOff()
{
    // Extend Solenoid Pin
    digitalWrite(pin, LOW);
}

void solenoid::powerOn()
{
    // Retract Solenoid Pin
    digitalWrite(pin, HIGH);
}