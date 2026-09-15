#include "API_Manager.h"

#include "Config.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Webserver_Manager.h"
#include "Filesystem_Manager.h"

namespace API_Manager
{
    void handle_WiFiSetting()
    {
        String body = Webserver_Manager::GetServerArg();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        // Check Invalid Input
        if(error) {
            Webserver_Manager::SendJsonResponse(400, "ERROR", "Invalid JSON");
            return;
        }

        // Check Both AP_SSID & AP_PASSWORD Are Entered And Are String
        if(!doc["AP_SSID"].is<String>() || !doc["AP_PASSWORD"].is<String>())
        {
            Webserver_Manager::SendJsonResponse(400, "ERROR", "Both AP_SSID & AP_PASSWORD Must Be Entered And Be String");
            return;
        }

        // Check AP_SSID Length
        if(std::strlen(doc["AP_SSID"]) > 32 || std::strlen(doc["AP_SSID"]) == 0)
        {
            Webserver_Manager::SendJsonResponse(400, "ERROR", "Invalid AP_SSID Length");
            return;
        }

        // Check AP_PASSWORD Length
        if((std::strlen(doc["AP_PASSWORD"]) > 63 || std::strlen(doc["AP_PASSWORD"]) < 8)
         && std::strlen(doc["AP_PASSWORD"]) != 0)
        {
            Webserver_Manager::SendJsonResponse(400, "ERROR", "Invalid AP_PASSWORD Length");
            return;
        }

        AP_SSID = doc["AP_SSID"].as<String>();
        AP_PASSWORD = doc["AP_PASSWORD"].as<String>();
        doc.clear();
        doc["AP_SSID"] = AP_SSID;
        doc["AP_PASSWORD"] = AP_PASSWORD;

        if(!Filesystem_Manager::SaveJson(WIFI_FILE, doc))
        {
            Webserver_Manager::SendJsonResponse(500, "ERROR", "Changes Did Not Saved");
            return;
        }

        Webserver_Manager::SendJsonResponse(200, "SUCCESS", "WiFi Settings Changes After Reset");
    }
}