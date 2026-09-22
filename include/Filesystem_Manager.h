#ifndef FILESYSTEM_MANAGER_H
#define FILESYSTEM_MANAGER_H

#pragma once
#include <ArduinoJson.h>
#include <LittleFS.h>

namespace Filesystem_Manager
{
    bool Save(const char * path, const JsonDocument& doc);
    bool Load(const char * path, JsonDocument& doc);
    template <typename T>
    bool Update(const char * path, const char * key, const T& value)
    {
        JsonDocument doc;
        // Load current configuration
        if(LittleFS.exists(path))
        {
            if(!Load(path, doc)) return false;
        }
        // Change only requested key
        doc[key] = value;
        // Save updated configuration
        return Save(path, doc);
    }
    bool Update(const char * path, JsonDocument& updates);
    void init();
}

#endif // FILESYSTEM_MANAGER_H