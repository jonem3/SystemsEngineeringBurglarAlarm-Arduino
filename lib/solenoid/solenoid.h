//class to control solenoid, turns it on and off

#include <Arduino.h>
class solenoid
{
private:
    int pin;

public:
    solenoid(int solenoidPin);
    void setup();
    void powerOn();
    void powerOff();
};