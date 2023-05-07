#include <Arduino.h>
#include <EEPROM.h>
#include <communicateJson.h>

class pinEntry
{
private:
    communicateJson JsonComms;
    int pin = 1234;

    void loadPin();
    void savePin();

public:
    pinEntry();
    bool getUserPin(int attempts);
    void changeUserPin();
};