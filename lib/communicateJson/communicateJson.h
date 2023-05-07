//this is an inherited child class of communicate, allowing communication of Json data
#include <communicate.h>
class communicateJson : public communicate
{
public:
    StaticJsonDocument<300> getJsonMessage();
    void sendJsonMessage(StaticJsonDocument<200> JsonMessage);
};