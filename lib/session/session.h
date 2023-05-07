// this class manages all major functions in the system, it is the central hub.

#include <buzzer.h>
#include <solenoid.h>
#include <led.h>
#include <sensor.h>

#include <pinEntry.h>

class session
{
private:
    communicate comms;
    communicateJson JsonComms;
    buzzer Buzzer = buzzer(6);
    solenoid Solenoid = solenoid(2);
    LED LEDs = LED(3, 4, 5);
    sensor Sensors[2] = {sensor(8, "DOOR"), sensor(9, "MOTION")};
    sensor Button = sensor(7, "BUTTON", 1);
    pinEntry PinEntry;
    String activatedSensor;

    StaticJsonDocument<200> checkSensors();
    bool internalCheckSensors();
    int deactivateAlarm();
    bool sendAlarmState(String AlarmState);

public:
    void setup(); // DONE
    void runAlarm();
    void mainMenu();
};