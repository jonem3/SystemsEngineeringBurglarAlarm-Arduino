#include <session.h>
#include <Arduino.h>

void session::setup()
{
    LEDs.setup();
    LEDs.setLED(2);
    comms.setup();
    Buzzer.setup();
    Solenoid.setup();
    Solenoid.powerOn();
    Button.setup();

    for (sensor i : Sensors)
    {
        i.setup();
    }
}

StaticJsonDocument<200> session::checkSensors()
{
    String states[2] = {"NORMAL", "TRIPPED"};
    StaticJsonDocument<200> sensorReadings;
    JsonArray array = sensorReadings.to<JsonArray>();
    StaticJsonDocument<100> currentReading;
    for (sensor currentSensor : Sensors)
    {
        currentReading.clear();
        String sensorState;
        if (currentSensor.readSensor())
        {
            sensorState = states[1];
        }
        else
        {
            sensorState = states[0];
        }
        String sensorName = currentSensor.getName();
        currentReading[sensorName] = sensorState;
        array.add(currentReading);
    }
    return sensorReadings;
}

bool session::internalCheckSensors()
{
    bool isTriggered = false;
    for (sensor currentSensor : Sensors)
    {
        if (currentSensor.readSensor())
        {
            isTriggered = true;
            activatedSensor = currentSensor.getName();
        }
    }
    return isTriggered;
}

bool session::sendAlarmState(String AlarmState)
{
    if (comms.isAvailable())
    {
        String response = comms.getMessage();

        return true;
    }
    StaticJsonDocument<200> sensorReadingSET;
    sensorReadingSET["sensors"] = checkSensors();
    sensorReadingSET["state"] = AlarmState;
    JsonComms.sendJsonMessage(sensorReadingSET);
    return false;
}

void session::runAlarm()
{

    bool isActive = true;
    int stage = 0;
    String alarmMessage = "WAITING FOR USER TO LEAVE";

    while (stage < 2)
    {
        Serial.flush();

        if (sendAlarmState(alarmMessage))
        {
            LEDs.setLED(0);
            isActive = !PinEntry.getUserPin(3);
        }

        if (stage == 0)
        {
            if (Sensors[0].readSensor())
            {
                stage++;
                LEDs.setLED(1);
                Buzzer.warningSound();
            }
        }
        else if (stage == 1)
        {
            if (!Sensors[0].readSensor())
            {
                stage++;
            }
        }
    }

    Buzzer.buzzerOff();

    bool soundAlarm = false;
    long start = millis();

    while (isActive)
    {
        if (Button.readSensor())
        {
            Buzzer.warningSound();
            LEDs.turnOnGreen();
            LEDs.turnOnOrange();
            LEDs.turnOnRed();
            Solenoid.powerOff();
            delay(1000);
        }
        Serial.flush();
        if (sendAlarmState(alarmMessage))
        {
            isActive = !PinEntry.getUserPin(3);
        }
        if (!soundAlarm)
        {
            LEDs.setLED(2);
            Buzzer.buzzerOff();
            Solenoid.powerOn();
            alarmMessage = "IDLE";
        }
        else
        {
            if ((millis() - start) < 5000)
            {
                LEDs.setLED(1);
                Buzzer.warningSound();
                alarmMessage = activatedSensor + " DETECTED";
            }
            else
            {
                LEDs.setLED(0);
                Buzzer.soundAlarm();
                Solenoid.powerOff();
                alarmMessage = "ALARM SOUNDING";
            }

            if (((millis() - start) / 1000) >= (20))
            {
                soundAlarm = false;
                digitalWrite(13, LOW);
            }
        }
        if (!soundAlarm)
        { //&& (millis()-start) >= 20000
            soundAlarm = internalCheckSensors();
            start = millis();
        }
    }
    LEDs.setLED(0);
    Buzzer.buzzerOff();
    Solenoid.powerOn();
}

void session::mainMenu()
{
    LEDs.setLED(2);
    while (!comms.isAvailable())
        ;
    String response = comms.getMessage();
    if (response == "CP")
    {
        PinEntry.changeUserPin();
    }
    else if (response == "PO")
    {
        runAlarm();
    }
}