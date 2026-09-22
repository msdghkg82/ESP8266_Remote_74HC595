#include "API_Manager.h"

#include "Config.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Webserver_Manager.h"
#include "Filesystem_Manager.h"
#include "74HC595_Driver.h"

namespace API_Manager
{
    // ---------------------------------------------
    // WiFi Setting API Handler
    // ---------------------------------------------
    void handle_WiFiSetting()
    {
        String body = Webserver_Manager::GetServerArg();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        // Check Invalid Input
        if(error) {
            Webserver_Manager::SendJsonResponse(400, "Invalid JSON");
            return;
        }

        // Check Both AP_SSID & AP_PASSWORD Are Entered And Are String
        if(!doc["AP_SSID"].is<String>() || !doc["AP_PASSWORD"].is<String>())
        {
            Webserver_Manager::SendJsonResponse(400, "Both AP_SSID & AP_PASSWORD Must Be Entered And Be String");
            return;
        }

        // Check AP_SSID Length
        if(std::strlen(doc["AP_SSID"]) > 32 || std::strlen(doc["AP_SSID"]) == 0)
        {
            Webserver_Manager::SendJsonResponse(400, "Invalid AP_SSID Length");
            return;
        }

        // Check AP_PASSWORD Length
        if((std::strlen(doc["AP_PASSWORD"]) > 63 || std::strlen(doc["AP_PASSWORD"]) < 8)
         && std::strlen(doc["AP_PASSWORD"]) != 0)
        {
            Webserver_Manager::SendJsonResponse(400, "Invalid AP_PASSWORD Length");
            return;
        }

        AP_SSID = doc["AP_SSID"].as<String>();
        AP_PASSWORD = doc["AP_PASSWORD"].as<String>();
        doc.clear();
        doc["AP_SSID"] = AP_SSID;
        doc["AP_PASSWORD"] = AP_PASSWORD;

        if(!Filesystem_Manager::Update(WIFI_FILE, doc))
        {
            Webserver_Manager::SendJsonResponse(500, "Changes Did Not Saved");
            return;
        }

        Webserver_Manager::SendJsonResponse(200, "WiFi Settings Changes After Reset");
    }

    // ---------------------------------------------
    // 74HC595 Set Mode API Handler
    // ---------------------------------------------
    void handle_HC595SetMode()
    {
        String body = Webserver_Manager::GetServerArg();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        // Check Invalid Input
        if(error) {
            Webserver_Manager::SendJsonResponse(400, "Invalid JSON");
            return;
        }

        bool updatedMode = false;
        bool updatedInterval = false;

        if(doc["Mode"].is<String>())
        {
            String mode = doc["Mode"].as<String>();
            if(!HasAnimation(StringtoMode(mode)))
            {
                // if Mode hasnt Animation (ON or OFF)
                hc595.SetMode(StringtoMode(mode));
                Serial.println("Mode Set to: " + mode);
                if(!Filesystem_Manager::Update(HC595_FILE, "Mode", ModeToString(hc595.GetMode())))
                {
                    Serial.println("New Mode Did Not Saved");
                }
                updatedMode = true;
            }
            else
            {
                // if Mode has Animation
                if(!doc["Interval"].is<uint32_t>())
                {
                    Webserver_Manager::SendJsonResponse(400, "Interval is Required for this Mode");
                    return;
                }
                hc595.SetMode(StringtoMode(mode));
                Serial.println("Mode Set to: " + mode);
                hc595.SetInterval(doc["Interval"].as<uint32_t>());
                Serial.println("Interval Set to: " + doc["Interval"].as<String>());
                doc.clear();
                doc["Mode"] = ModeToString(hc595.GetMode());
                doc["Interval"] = hc595.GetInterval();
                if(!Filesystem_Manager::Update(HC595_FILE, doc))
                {
                    Serial.println("New Mode & Interval Did Not Saved");
                }
                updatedMode = true;
                updatedInterval = true;
            }
        }

        if(doc["Interval"].is<uint32_t>() && updatedInterval == false)
        {
            hc595.SetInterval(doc["Interval"].as<uint32_t>());
            Serial.println("Interval Set to: " + doc["Interval"].as<String>());
            if(!Filesystem_Manager::Update(HC595_FILE, "Interval", hc595.GetInterval()))
            {
                Serial.println("New Interval Did Not Saved");
            }
            updatedInterval = true;
        }

        if(!updatedMode && !updatedInterval)
        {
            Webserver_Manager::SendJsonResponse(400, "No Valid Settings Provided");
            return;
        }

        Webserver_Manager::SendJsonResponse(200, "Settings Updated");
    }

    // ---------------------------------------------
    // 74HC595 Set Brightness API Handler
    // ---------------------------------------------
    void handle_HC595SetBrightness()
    {
        String body = Webserver_Manager::GetServerArg();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        // Check Invalid Input
        if(error) {
            Webserver_Manager::SendJsonResponse(400, "Invalid JSON");
            return;
        }

        if(!doc["Brightness"].is<uint8_t>())
        {
            Webserver_Manager::SendJsonResponse(400, "Invalid Brightness Type");
            return;
        }
        hc595.SetBrightness(doc["Brightness"].as<uint8_t>());
        Serial.println("Brightness Set to: " + String(hc595.GetBrightness()));
        if(!Filesystem_Manager::Update(HC595_FILE, "Brightness", hc595.GetBrightness()))
        {
            Serial.println("New Brightness Did Not Saved");
        }

        Webserver_Manager::SendJsonResponse(200, "Brightness Changed");
    }

    void handle_RFRemotePair()
    {
        String body = Webserver_Manager::GetServerArg();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        // Check Invalid Input
        if(error) {
            Webserver_Manager::SendJsonResponse(400, "Invalid JSON");
            return;
        }

        if(!doc["Code"].is<String>())
        {
            Webserver_Manager::SendJsonResponse(400, "Invalid Code Type");
            return;
        }
        RFRemoteCode = doc["Code"].as<uint32_t>();
        Serial.println("Pair Code Set to: " + doc["Code"].as<String>());
        if(!Filesystem_Manager::Update(RFREMOTE_FILE, "Code", RFRemoteCode))
        {
            Serial.println("New Brightness Did Not Saved");
        }

        Webserver_Manager::SendJsonResponse(200, "Remote Paired");
    }
}