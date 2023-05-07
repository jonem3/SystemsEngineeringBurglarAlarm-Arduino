//LED class, turns on LEDS and turns them off

#ifndef LED_H
#define LED_H

class LED
{
private:
  int pins[3];

public:
  LED(int redPin, int orangePin, int greenPin);
  void setup();
  void turnOnRed();
  void turnOnGreen();
  void turnOnOrange();
  void turnOffAll();
  void setLED(int state);
};

#endif