#include <Arduino.h>
#include <session.h>

session newSession;

void setup()
{
  newSession.setup();
}

void loop()
{
  newSession.mainMenu();
}