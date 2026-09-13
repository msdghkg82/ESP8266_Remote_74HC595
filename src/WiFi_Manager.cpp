#include "WiFi_Manager.h"

#include "Config.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace WiFi_Manager
{
    void init()
    {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(AP_SSID, AP_PASSWORD);
    }

    void Connect()
    {
        WiFi.softAP(AP_SSID, AP_PASSWORD);
    }

    void Disconnect()
    {
        WiFi.softAPdisconnect();
    }
}