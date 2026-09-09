#include "Remote_Driver.h"

#include "Config.h"
#include <Arduino.h>
#include <RCSwitch.h>

namespace RemoteDriver
{
    RCSwitch mySwitch = RCSwitch();

    void init()
    {
        mySwitch.enableReceive(digitalPinToInterrupt(RECEIVER_PIN));
    }

    void loop()
    {
        if (mySwitch.available())
        {
            unsigned long value = mySwitch.getReceivedValue();
            if (value == 0)
            {
                Serial.print("Unknown encoding / Noise");
            }
            else
            {
                Serial.print("Received ");
                Serial.print(value);
                Serial.print(" / ");
                Serial.print(mySwitch.getReceivedBitlength());
                Serial.print("bit ");
                Serial.print("Protocol: ");
                Serial.println(mySwitch.getReceivedProtocol());
                Serial.print("Delay: ");
                Serial.println(mySwitch.getReceivedDelay());
            }

            mySwitch.resetAvailable();
        }
    }
}