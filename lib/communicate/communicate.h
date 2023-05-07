// the communicate class is used to communicate between the arduino and the GUI
// using the serial protocol
#include <Arduino.h>
#include <ArduinoJson.h>

class communicate
{
private:
    String incoming;
    void handshake();
    void awaitSerial();
    void clearBuffer();
    void serialRead();

public:
    void setup(); // Instead of constructor as Arduino does not allow for Serial or Pin setting before setup
    void changePin();
    String getMessage();
    void sendMessage(String message);
    bool isAvailable();
};
