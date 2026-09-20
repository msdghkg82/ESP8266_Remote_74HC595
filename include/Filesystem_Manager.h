#ifndef FILESYSTEM_MANAGER_H
#define FILESYSTEM_MANAGER_H

#pragma once
#include <ArduinoJson.h>

namespace Filesystem_Manager
{
    bool Save(const char * path, const JsonDocument& doc);
    bool Load(const char * path, JsonDocument& doc);

    template <typename T>
    bool Update(const char * path, const char * key, const T& value);
    bool Update(const char * path, JsonDocument& updates);
    void init();
}

#endif // FILESYSTEM_MANAGER_H