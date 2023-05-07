#include <pinEntry.h>

pinEntry::pinEntry()
{
    // This is the constructor for the class, it loads any available pin codes from the EEPROM and sets it to the main pin
    loadPin();
    savePin();
}

void pinEntry::loadPin()
{
    // This function loads a pin out of the EEPROM
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
    // This function saves a pin to the EEPROM
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
    // This function communicates with the GUI to allow the user to enter a pin and will respond if it is correct or not
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
    // This function allows the user to change the pin stored on the Arduino and saves it to memory
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