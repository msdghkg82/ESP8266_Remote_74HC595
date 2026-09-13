#include "Filesystem_Manager.h"

#include "Config.h"
#include <LittleFS.h>
#include <ArduinoJson.h>

namespace Filesystem_Manager
{
    bool SaveJson(const char * path, const JsonDocument& doc)
    {
        String tempPath = String(path) + ".tmp";
        File file = LittleFS.open(tempPath, "w");
        if(!file) return false;

        size_t written = serializeJson(doc, file);

        file.flush();
        file.close();

        if(written == 0)
        {
            LittleFS.remove(tempPath);
            return false;
        }

        if(!LittleFS.rename(tempPath, path))
        {
            return false;
        }

        return true;
    }


    bool LoadJson(const char * path, JsonDocument& doc)
    {
        if(!LittleFS.exists(path)) return false;

        File file = LittleFS.open(path, "r");
        if(!file) return false;

        doc.clear();
        DeserializationError err = deserializeJson(doc, file);
        file.flush();
        file.close();

        if(err)
        {
            doc.clear();
            return false;
        }

        return true;
    }

    static bool LoadConfigs()
    {
        JsonDocument doc;

        // Load WiFi Config
        LoadJson(WIFI_FILE, doc);
        AP_SSID = doc["AP_SSID"];
        AP_PASSWORD = doc["AP_PASSWORD"];
        doc.clear();

        // Load ...
    }

    void init()
    {
        if(!LittleFS.begin())
        {
            Serial.println("Failed to Mount LittleFS");
        }
        else Serial.println("LittleFS Mounted Successfuly");

        if(!LoadConfigs())
        {
            Serial.println("Failed to Load Configs");
        }
        else Serial.println("Configs Loaded Successfuly");
    }
}