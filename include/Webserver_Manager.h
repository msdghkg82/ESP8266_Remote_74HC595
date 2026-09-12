#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

class String;

namespace Webserver_Manager
{
    void init();
    void handleClient();
    void SendJsonResponse(int code, const String& stat, const String& msg);
    String GetServerArg();
}

#endif // WEBSERVERMANAGER_H