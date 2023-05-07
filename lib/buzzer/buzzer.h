#include <Arduino.h>

class buzzer
{
private:
    int pin;
    const int buzzerStandByTone = 500;
    const int buzzerTone = 2000;

public:
    buzzer(int buzzerPin);
    void setup();
    void soundAlarm();
    void warningSound();
    void buzzerOff();
};