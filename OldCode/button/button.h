#include <Arduino.h>
#include <sensor.h>

class Button : public sensor{

    public:

    //constructor as button is input 
    Button(int pin):sensor(pin)
    {
        pinMode(pin,OUTPUT);
    }
};

