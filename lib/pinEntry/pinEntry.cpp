#include <pinEntry.h>

pinEntry::pinEntry()
{
    loadPin();
    savePin();
}

void pinEntry::loadPin()
{
    String loadPin = "";
    char currentCharacter;
    bool isSaved;
    EEPROM.get(0, isSaved);
    if (isSaved)
    {
        for (int i = 1; i < 5; i++)
        {
            EEPROM.get(i, currentCharacter);
            loadPin += currentCharacter;
        }
        pin = loadPin.toInt();
    }
}

void pinEntry::savePin()
{
    String pinSave = (String)pin;
    int index = 1;
    for (char pinDigit : pinSave)
    {
        EEPROM.put(index, pinDigit);
        index++;
    }
    EEPROM.put(0, true);
}

bool pinEntry::getUserPin(int attempts)
{
    int timeAvailable = 30000;
    int start = millis();
    int timeElapsed;
    bool pinCorrect = false;
    StaticJsonDocument<300> messageData;
    do
    {
        if (attempts > 0)
        {
            timeElapsed = millis() - start;
            messageData.clear();
            messageData["timeRemaining"] = timeAvailable - timeElapsed;
            messageData["attemptsRemaining"] = attempts;
            if (JsonComms.isAvailable())
            {
                StaticJsonDocument<200> response = JsonComms.getJsonMessage();
                if (response["pin"] == pin)
                {
                    messageData["passwordResponse"] = "Correct";
                    pinCorrect = true;
                    timeElapsed = timeAvailable + 1;
                }
                else
                {
                    messageData["passwordResponse"] = "Incorrect";
                    attempts--;
                    start = millis();
                }
            }
            JsonComms.sendJsonMessage(messageData);
            delay(200);
        }
        else
        {
            messageData.clear();
            timeElapsed = timeAvailable + 1;
            messageData["message"] = "OUT OF ATTEMPTS";
            JsonComms.sendJsonMessage(messageData);
        }

    } while (timeElapsed <= timeAvailable);
    if (!pinCorrect)
    {
        messageData.clear();
        messageData["message"] = "OUT OF TIME";
        JsonComms.sendJsonMessage(messageData);
    }
    return pinCorrect;
}

void pinEntry::changeUserPin()
{
    if (getUserPin(1))
    {
        while (!JsonComms.isAvailable())
            ;
        StaticJsonDocument<200> response = JsonComms.getJsonMessage();
        if (response["verification"] == "success")
        {
            pin = response["newPin"];
            savePin();
        }
    }
    else
    {
        digitalWrite(3, HIGH);
    }
}