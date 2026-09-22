#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

#pragma once

#include <WString.h>

namespace Webserver_Manager
{
    void init();
    void loop();
    void SendJsonResponse(int code, const String& msg);
    String GetServerArg();
}

#endif // WEBSERVERMANAGER_H