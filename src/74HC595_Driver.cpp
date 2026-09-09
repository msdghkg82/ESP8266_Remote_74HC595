#include "74HC595_Driver.h"

#include "Config.h"
#include <Arduino.h>
#include <SPI.h>

namespace HC595_Driver
{
    void HC595_Write(uint8_t data)
    {
        // Set the latch pin low to start sending data
        digitalWrite(LATCH_PIN, LOW);
        // Send the data to the shift register
        SPI.transfer(data);
        // Set the latch pin high to update the output
        digitalWrite(LATCH_PIN, HIGH);
    }

    void init()
    {
        // Set the latch pin as an output
        pinMode(LATCH_PIN, OUTPUT);
        // Set the clock pin as an output
        pinMode(CLOCK_PIN, OUTPUT);
        // Set the data pin as an output
        pinMode(DATA_PIN, OUTPUT);

        // Initialize SPI
        SPI.begin();

        // Clear the shift register on initialization
        HC595_Write(0x00);
    }
}