#include "API_Manager.h"

#include "Config.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Webserver_Manager.h"
#include "Filesystem_Manager.h"
#include "74HC595_Driver.h"

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

    void handle_HC595SetMode()
    {
        String body = Webserver_Manager::GetServerArg();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        // Check Invalid Input
        if(error) {
            Webserver_Manager::SendJsonResponse(400, "ERROR", "Invalid JSON");
            return;
        }

        if(doc["Mode"].is<String>())
        {
            hc595.SetMode(StringtoMode(doc["Mode"]));
            Serial.println("Mode Set to: " + doc["Mode"].as<String>());
            doc.clear();
            doc["Mode"] = hc595.GetMode();
            if(Filesystem_Manager::SaveJson(HC595_MODE_FILE, doc))
            {
                Serial.println("New Mode Did Not Saved");
            }
        }

        if(doc["Interval"].is<uint32_t>())
        {
            hc595.SetInterval(doc["Interval"].as<uint32_t>());
            Serial.println("Interval Set to: " + doc["Interval"].as<String>());
            doc.clear();
            doc["Interval"] = hc595.GetInterval();
            if(!Filesystem_Manager::SaveJson(HC595_INTERVAL_FILE, doc))
            {
                Serial.println("New Interval Did Not Saved");
            }
        }


        Webserver_Manager::SendJsonResponse(200, "SUCCESS", "Settings Updated");
    }
}