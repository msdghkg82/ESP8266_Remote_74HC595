#include "74HC595_Driver.h"

#include "Config.h"
#include <Arduino.h>
#include <SPI.h>

namespace HC595_Driver
{
    void HC595_Write(uint8_t data)
    {
        digitalWrite(LATCH_PIN, LOW);
        SPI.transfer(data);
        digitalWrite(LATCH_PIN, HIGH);
    }

    void init()
    {
        pinMode(LATCH_PIN, OUTPUT);
        digitalWrite(LATCH_PIN, LOW);
        
        SPI.setBitOrder(MSBFIRST);
        SPI.setDataMode(SPI_MODE0);
        SPI.begin();

        HC595_Write(0x00);
    }
}