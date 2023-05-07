#include <Arduino.h>
class sensor
{
protected:
  String SensorName;
  int SensorPin;
  int SensorStatus;
  bool isMirrored = false;

public:
  sensor(int pin, String name);
  sensor(int pin, String name, bool mirror);
  void setup();
  int readSensor();
  String getName();
};
