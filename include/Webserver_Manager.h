#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

namespace Webserver_Manager
{
    void init();
    void handleClient();
    void SendJsonResponse(int code, const String& stat, const String& msg);
}

#endif // WEBSERVERMANAGER_H