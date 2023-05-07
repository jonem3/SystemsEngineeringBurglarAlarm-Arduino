#include <communicate.h>
class communicateJson : public communicate
{
public:
    StaticJsonDocument<300> getJsonMessage();
    void sendJsonMessage(StaticJsonDocument<200> JsonMessage);
};