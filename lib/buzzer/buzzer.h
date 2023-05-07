#include <Arduino.h>

// this is buzzer class, controls the buzzer functionality
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