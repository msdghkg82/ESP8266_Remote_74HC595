#include "RF_Remote_Driver.h"

#include "Config.h"
#include <Arduino.h>
#include <RCSwitch.h>

static RCSwitch mySwitch = RCSwitch();

bool RF_Remote::CheckCode(unsigned long value)
{
    if(RFRemoteCode == (value >> CODE_SHIFT_VALUE))
    {
        return true;
    }
    else return false;
}

unsigned long RF_Remote::CheckData(unsigned long value)
{
    unsigned long data;
    data = value & DATA_VALUE_MASK;
    return data;
}

void RF_Remote::Actions(unsigned long data)
{
    if(data == _buttons[0].Code)
    {
        _buttons[0].Action;
    }
    else if(data == _buttons[1].Code)
    {
        _buttons[1].Action;
    }
    else if(data == _buttons[2].Code)
    {
        _buttons[2].Action;
    }
    else if(data == _buttons[3].Code)
    {
        _buttons[3].Action;
    }
}

RF_Remote::RF_Remote()
{
    _buttons[0] = {0x1234, off};
    _buttons[1] = {0x1235, off};
    _buttons[2] = {0x1236, off};
    _buttons[3] = {0x1237, off};
}

void RF_Remote::init()
{
    mySwitch.enableReceive(digitalPinToInterrupt(RECEIVER_PIN));
}

void RF_Remote::loop()
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

RF_Remote remote;

static void off();