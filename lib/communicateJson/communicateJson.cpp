#include <communicateJson.h>

// this allows arduino to send Json data to GUI
void communicateJson::sendJsonMessage(StaticJsonDocument<200> JsonMessage)
{
    serializeJson(JsonMessage, Serial);
    Serial.println();
}

// this allows arduino to get Json data from GUI
StaticJsonDocument<300> communicateJson::getJsonMessage()
{
    StaticJsonDocument<200> doc;
    deserializeJson(doc, Serial);
    return doc;
}