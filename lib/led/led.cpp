#include <led.h>
#include <Arduino.h>

using namespace std;

LED::LED(int redPin, int orangePin, int greenPin)
{
  pins[0] = redPin;
  pins[1] = orangePin;
  pins[2] = greenPin;
}

void LED::setup()
{
  for (int pin : pins)
  {
    pinMode(pin, OUTPUT);
  }
  digitalWrite(pins[2], HIGH);
}

void LED::setLED(int index)
{
  // turn all the LEDs off now to avoid repeating code (optimisation is kinda cool :P )
  turnOffAll();
  // RED LED - 0
  // ORANGE LED - 1
  // GREEN LED - 2
  digitalWrite(pins[index], HIGH);
}

void LED::turnOnGreen()
{
  digitalWrite(pins[2], HIGH);
}

void LED::turnOnOrange()
{
  digitalWrite(pins[1], HIGH);
}

void LED::turnOnRed()
{
  digitalWrite(pins[0], HIGH);
}

void LED::turnOffAll()
{
  for (int pin : pins)
  {
    digitalWrite(pin, LOW);
  }
}