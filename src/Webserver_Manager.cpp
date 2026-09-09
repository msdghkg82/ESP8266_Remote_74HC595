#include "Webserver_Manager.h"

#include "Config.h"
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
//#include <ArduinoJson.h>

namespace WebserverManager
{
    static ESP8266WebServer server(80);
    static ESP8266HTTPUpdateServer httpUpdater;

    static void handleRoot()
    {
        server.send(200, "text/plain", "Hello from ESP8266 Web Server!");
    }

    static void ConnectAPIs()
    {
        server.on("/", handleRoot);
        server.onNotFound([]() {
            server.send(404, "text/plain", "404: Not Found");
        });
    }

    void init()
    {
        // Start the web server
        ConnectAPIs();
        httpUpdater.setup(&server, "/update", OTA_USERNAME, OTA_PASSWORD);
        server.begin();
        Serial.println("HTTP server started");
    }

    void handleClient()
    {
        server.handleClient();
    }
}