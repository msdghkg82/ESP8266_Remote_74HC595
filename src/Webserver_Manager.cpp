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

    void SendJsonResponse(int code, const String& msg)
    {
        JsonDocument doc;
        switch(code)
        {
            case 200:
                doc["status"] = "SUCCESS";
                break;
            case 400:
                doc["status"] = "ERROR";
                break;
            case 404:
                doc["status"] = "ERROR";
        }
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
            SendJsonResponse(200, "Hello from ESP8266 Webserver.");
        });
        server.onNotFound([]() {
            SendJsonResponse(404, "404: Not Found");
        });
        server.on(WIFI_SETTING_API, API_Manager::handle_WiFiSetting);
        server.on(HC595_SETMODE_API, API_Manager::handle_HC595SetMode);
        server.on(HC595_BRIGHTNESS_API, API_Manager::handle_HC595SetBrightness);
    }

    void init()
    {
        // Start the web server
        ConnectAPIs();
        httpUpdater.setup(&server, "/update", OTA_USERNAME, OTA_PASSWORD);
        server.begin();
        Serial.println("HTTP server started");
    }

    void loop()
    {
        server.handleClient();
    }
}