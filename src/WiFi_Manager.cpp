#include "WiFi_Manager.h"

#include "Config.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace WiFi_Manager
{
    void init()
    {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(AP_SSID_DEFAULT, AP_PASSWORD_DEFAULT);
    }

    void TurnOn()
    {
        WiFi.softAP(AP_SSID_DEFAULT, AP_PASSWORD_DEFAULT);
    }

    void TurnOff()
    {
        WiFi.softAPdisconnect();
    }
}