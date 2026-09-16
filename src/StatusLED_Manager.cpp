#include "StatusLED_Manager.h"

#include "Config.h"
#include <Arduino.h>
#include <Ticker.h>

namespace StatusLED_Manager
{
    static Ticker LEDTicker;
    static Ticker ResetTicker;

    static void LEDTicker_CallBack()
    {
        digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    }

    static void ResetTicker_CallBack()
    {
        LEDTicker.detach();
        LEDTicker.attach(1.f, LEDTicker_CallBack);
    }

    void SetStatusLEDInterval(float interval)
    {
        LEDTicker.detach();
        LEDTicker.attach(interval, LEDTicker_CallBack);
    }

    void SetStatusLEDInterval(float interval, float seconds)
    {
        LEDTicker.detach();
        LEDTicker.attach(interval, LEDTicker_CallBack);
        ResetTicker.once(seconds, ResetTicker_CallBack);
    }

    void init()
    {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
        LEDTicker.attach(1.f, LEDTicker_CallBack);
    }
}