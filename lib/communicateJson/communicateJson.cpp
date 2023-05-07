#include <communicateJson.h>

void communicateJson::sendJsonMessage(StaticJsonDocument<200> JsonMessage)
{
    serializeJson(JsonMessage, Serial);
    Serial.println();
}

StaticJsonDocument<300> communicateJson::getJsonMessage()
{
    StaticJsonDocument<200> doc;
    deserializeJson(doc, Serial);
    return doc;
}