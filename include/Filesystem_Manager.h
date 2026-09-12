#ifndef FILESYSTEM_MANAGER_H
#define FILESYSTEM_MANAGER_H

//class JsonDocument;

namespace Filesystem_Manager
{
    bool SaveJson(const char *path, const JsonDocument& doc);
    bool LoadJson(const char *path, JsonDocument& doc);
    void init();
}

#endif // FILESYSTEM_MANAGER_H