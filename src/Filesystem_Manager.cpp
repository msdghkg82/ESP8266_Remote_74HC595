#include "Filesystem_Manager.h"

#include "Config.h"
#include <LittleFS.h>
//#include <ArduinoJson.h>

namespace Filesystem_Manager
{
    static bool Recover(const char * path)
    {
        /*
         * Possible situations after an unexpected reset:
         *
         * 1. config.json exists
         *    -> normal situation
         *
         * 2. config.json doesn't exist but config.bak exists
         *    -> previous save was interrupted
         *       restore backup
         *
         * 3. config.json exists and config.bak exists
         *    -> save probably completed, clean old backup
         *
         * 4. config.tmp exists
         *    -> incomplete/unused temporary file
         */

        if(path == nullptr) return false;

        String tempPath = String(path) + ".tmp";
        String backupPath = String(path) + ".bak";

        if(!LittleFS.exists(path))
        {
            if(LittleFS.exists(backupPath))
            {
                if(!LittleFS.rename(backupPath, path)) return false;
            }
            else
            {
                // No config and no backup
                return false;
            }
        }
        else
        {
            // Main config exists, so backup is unnecessary
            if (LittleFS.exists(backupPath))
            {
                LittleFS.remove(backupPath);
            }
        }

        // Temporary file is no longer needed after recovery
        if (LittleFS.exists(tempPath))
        {
            LittleFS.remove(tempPath);
        }

        return true;
    }

    bool Save(const char * path, const JsonDocument& doc)
    {
        if(path == nullptr) return false;


        // ---------------------------------------------
        // Generate temporary and backup paths
        // ---------------------------------------------

        String tempPath = String(path) + ".tmp";
        String backupPath = String(path) + ".bak";


        // ---------------------------------------------
        // Remove old temporary file
        // ---------------------------------------------

        if (LittleFS.exists(tempPath))
            LittleFS.remove(tempPath);


        // ---------------------------------------------
        // 1. Write new JSON to temporary file
        // ---------------------------------------------

        File tempFile = LittleFS.open(tempPath, "w");

        if (!tempFile) return false;

        size_t bytesWritten = serializeJson(doc, tempFile);

        tempFile.close();

        if (bytesWritten == 0)
        {
            LittleFS.remove(tempPath);
            return false;
        }


        // ---------------------------------------------
        // 2. Remove old backup
        // ---------------------------------------------

        if (LittleFS.exists(backupPath))
        {
            LittleFS.remove(backupPath);
        }


        // ---------------------------------------------
        // 3. Rename current file to backup
        // ---------------------------------------------

        if (LittleFS.exists(path))
        {
            if (!LittleFS.rename(path, backupPath))
            {
                LittleFS.remove(tempPath);
                return false;
            }
        }


        // ---------------------------------------------
        // 4. Rename temporary file to real file
        // ---------------------------------------------

        if (!LittleFS.rename(tempPath, path))
        {
            // Restore previous configuration

            if (LittleFS.exists(backupPath))
            {
                LittleFS.rename(backupPath, path);
            }

            return false;
        }


        // ---------------------------------------------
        // 5. New file successfully installed
        // ---------------------------------------------

        if (LittleFS.exists(backupPath))
        {
            LittleFS.remove(backupPath);
        }

        return true;
    }

    bool Load(const char * path, JsonDocument& doc)
    {
        if(!LittleFS.exists(path)) 
        {
            if(!Recover(path))
            {
                return false;
            }
        }
        
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

    template <typename T>
    bool Update(const char * path, const char * key, const T& value)
    {
        JsonDocument doc;

        // Load current configuration
        if (!Load(path, doc)) return false;

        // Change only requested key
        doc[key] = value;

        // Save updated configuration
        return Save(path, doc);
    }

    bool Update(const char * path, JsonDocument& updates)
    {
        JsonDocument doc;
        if(!Load(path, doc)) return false;
        for(JsonPair item : updates.as<JsonObject>())
        {
            doc[item.key()] = item.value();
        }
        return Save(path, doc);
    }

    static bool LoadConfigs()
    {
        JsonDocument doc;

        // Load WiFi Config
        if(Load(WIFI_FILE, doc))
        AP_SSID = doc["AP_SSID"].as<String>();
        AP_PASSWORD = doc["AP_PASSWORD"].as<String>();
        doc.clear();

        // Load ...

        return true;
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