#include "74HC595_Driver.h"

#include "Config.h"
#include <Arduino.h>
#include <SPI.h>
#include <Ticker.h>

enum class Mode
{
    ON,
    OFF,
    RTL,
    LTR,
    CASCADE
};

HC595::HC595()
{
    _mode = Mode::OFF;
    _previousMillis = 0;
    _interval = 0;
}

void HC595::Write(uint8_t data)
{
    digitalWrite(LATCH_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(LATCH_PIN, HIGH);
}

void HC595::On()
{
    Write(0xFF);
}

void HC595::Off()
{
    Write(0x00);
}

void HC595::RTL()
{
    _currentMillis = millis();
    if(_currentMillis - _previousMillis >= _interval)
    {
        _previousMillis = _currentMillis;
        _buffer |= (1 << (7 - _index));
        Write(_buffer);
        _index++;
        if(_index >= 8)
        {
            _buffer = 0;
            _index = 0;
        }
    }
}

void HC595::LTR()
{
    _currentMillis = millis();
    if(_currentMillis - _previousMillis >= _interval)
    {
        _previousMillis = _currentMillis;
        _buffer |= (1 << _index);
        Write(_buffer);
        _index++;
        if(_index >= 8)
        {
            _buffer = 0;
            _index = 0;
        }
    }
}

void HC595::Cascade()
{

}

void HC595::SetMode(Mode mode)
{
    _mode = mode;
    if(_mode == Mode::OFF) Off();
    else if(_mode == Mode::ON) On();
}

Mode HC595::GetMode()
{
    return _mode;
}

void HC595::SetInterval(uint32_t interval)
{
    _interval = interval;
}

uint32_t HC595::GetInterval()
{
    return _interval;
}

Mode StringtoMode(String str)
{
    if(str == "ON")
    {
        return Mode::ON;
    }
    else if(str == "OFF")
    {
        return Mode::OFF;
    }
    else if(str == "RTL")
    {
        return Mode::RTL;
    }
    else if(str == "LTR")
    {
        return Mode::LTR;
    }
    else if(str == "Cascade")
    {
        return Mode::CASCADE;
    }
    else return Mode::OFF;
}

void HC595::init()
{
    pinMode(LATCH_PIN, OUTPUT);
    digitalWrite(LATCH_PIN, LOW);
        
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin();

    Write(0x00);
}

void HC595::update()
{
    switch(_mode)
    {
        case Mode::ON: return;
        case Mode::OFF: return;
        case Mode::RTL: RTL(); break;
        case Mode::LTR: LTR(); break;
        case Mode::CASCADE: Cascade(); break;
    }
}

HC595 hc595;