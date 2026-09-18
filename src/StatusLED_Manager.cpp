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
        LEDTicker.attach_ms(DEFAULT_INTERVAL, LEDTicker_CallBack);
    }

    void SetInterval(uint32_t interval)
    {
        LEDTicker.detach();
        ResetTicker.detach();
        LEDTicker.attach_ms(interval, LEDTicker_CallBack);
    }

    void SetInterval(uint32_t interval, uint32_t seconds)
    {
        LEDTicker.detach();
        LEDTicker.attach_ms(interval, LEDTicker_CallBack);
        ResetTicker.detach();
        ResetTicker.once(seconds, ResetTicker_CallBack);
    }

    void init()
    {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
        LEDTicker.attach_ms(DEFAULT_INTERVAL, LEDTicker_CallBack);
    }
}