#ifndef _74HC595_DRIVER_H
#define _74HC595_DRIVER_H

#pragma once

#include <stdint.h>
#include <WString.h>

enum class Mode;

class HC595
{
    public:
    HC595();
    void SetMode(Mode mode);
    Mode GetMode();
    void SetInterval(uint32_t interval);
    uint32_t GetInterval();
    void init();
    void update();

    private:
    void Write(uint8_t data);
    void On();
    void Off();
    void RTL();
    void LTR();
    void Cascade();

    Mode _mode;
    unsigned long _previousMillis;
    unsigned long _currentMillis;
    unsigned long _interval;
    uint8_t _buffer;
    uint8_t _index;
};

Mode StringtoMode(String str);

extern HC595 hc595;

#endif // _74HC595_DRIVER_H