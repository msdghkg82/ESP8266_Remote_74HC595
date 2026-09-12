#include "Webserver_Manager.h"

#include "Config.h"
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoJson.h>
#include "API_Manager.h"

namespace Webserver_Manager
{
    static ESP8266WebServer server(80);
    static ESP8266HTTPUpdateServer httpUpdater;

    void SendJsonResponse(int code, const String& stat, const String& msg)
    {
        JsonDocument doc;
        doc["status"] = stat;
        doc["message"] = msg;
        String response;
        serializeJson(doc, response);
        server.send(code, "application/json", response);
    }

    String GetServerArg()
    {
        return server.arg("plain");
    }

    static void ConnectAPIs()
    {
        server.on("/", []() {
            SendJsonResponse(200, "OK", "Hello from ESP8266 Webserver.");
        });
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