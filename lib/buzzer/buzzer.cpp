#include <buzzer.h>

buzzer::buzzer(int buzzerPin)
{
  // Assign the pin property the value of the pin that the buzzer is attached to
  pin = buzzerPin;
}

void buzzer::setup()
{
  // Declare the buzzer as an output
  pinMode(pin, OUTPUT);
}

void buzzer::soundAlarm()
{
  // Play the alarm tone on the buzzer
  tone(pin, buzzerTone);
}

void buzzer::warningSound()
{
  // Play the warning sound on the buzzer
  tone(pin, buzzerStandByTone);
  delay(2000);
  buzzerOff();
}

void buzzer::buzzerOff()
{
  // Stop the buzzer making noise
  noTone(pin);
}