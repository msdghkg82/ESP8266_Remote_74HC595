#include "RF_Remote_Driver.h"

#include "Config.h"
#include <Arduino.h>
#include <RCSwitch.h>

namespace RF_Remote_Driver
{
    static RCSwitch mySwitch = RCSwitch();

    static bool CheckCode(unsigned long value)
    {
        if(RFRemoteCode == (value >> CODE_SHIFT_VALUE))
        {
            return true;
        }
        else return false;
    }

    static unsigned long CheckData(unsigned long value)
    {
        unsigned long data;
        data = value & DATA_VALUE_MASK;
        return data;
    }

    static void Actions(unsigned long data)
    {
        switch(data)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    }

    void init()
    {
        mySwitch.enableReceive(digitalPinToInterrupt(RECEIVER_PIN));
    }

    void loop()
    {
        if(mySwitch.available())
        {
            unsigned long value = mySwitch.getReceivedValue();
            if(value == 0)
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

            if(CheckCode(value))
            {
                Actions(CheckData(value));
            }

            mySwitch.resetAvailable();
        }
    }
}