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
        pinMode(CLOCK_PIN, OUTPUT);
        pinMode(DATA_PIN, OUTPUT);

        SPI.begin();

        HC595_Write(0x00);
    }
}