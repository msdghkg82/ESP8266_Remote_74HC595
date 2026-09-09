#include "WiFiManager.h"

#include "Config.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace WiFiManager
{
    void init()
    {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(AP_SSID, AP_PASSWORD);
    }

    void TurnOn()
    {
        WiFi.softAP(AP_SSID, AP_PASSWORD);
    }

    void TurnOff()
    {
        WiFi.softAPdisconnect();
    }
}
