#include <communicate.h>

void communicate::setup()
{
    // Begins Serial Connection and runs handshake method
    Serial.begin(9600);
    handshake();
}

void communicate::handshake()
{
    /*
    this allows the GUI and arduino to cominicate
    */
    bool handshook = false;
    do
    {
        getMessage();
        if (incoming == "BURGLAR CONNECTION REMOTE")
        {
            sendMessage("BURGLAR CONNECTION LOCAL");
            handshook = true;
        }
    } while (!handshook);
}

void communicate::awaitSerial()
{
    while (!Serial.available())
        ; // Loops while no data available
}

void communicate::clearBuffer()
{
    // This function clears out the incoming data buffer
    awaitSerial();
    serialRead();
}

void communicate::serialRead()
{
    //this function gets a message from the GUI
    incoming = "";
    if (Serial.available())
    {
        incoming = Serial.readStringUntil('\n');
    }
}

String communicate::getMessage()
{
    // Retrieves incoming message from Python based UI
    awaitSerial();
    serialRead();
    return incoming;
}

void communicate::sendMessage(String message)
{
    // Sends a message to the python based UI
    Serial.println(message);
}

bool communicate::isAvailable()
{
    // this is checking that arduino can reach the GUI
    return Serial.available();
}