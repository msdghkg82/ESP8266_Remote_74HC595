#include "Webserver_Manager.h"

#include "Config.h"
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoJson.h>

namespace Webserver_Manager
{
    static ESP8266WebServer server(80);
    static ESP8266HTTPUpdateServer httpUpdater;

    static void SendJsonResponse(int code, const String& stat, const String& msg)
    {
        JsonDocument doc;
        doc["status"] = stat;
        doc["message"] = msg;
        String response;
        serializeJson(doc, response);
        server.send(code, "application/json", response);
    }
    
    static void handleRoot()
    {
        SendJsonResponse(200, "OK", "Hello from ESP8266 Webserver.");
    }

    static void ConnectAPIs()
    {
        server.on("/", handleRoot);
        server.onNotFound([]() {
            SendJsonResponse(404, "ERROR", "404: Not Found");
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