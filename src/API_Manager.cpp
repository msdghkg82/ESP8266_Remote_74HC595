#include "API_Manager.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Webserver_Manager.h"

namespace API_Manager
{
    void handle()
    {
        String body = Webserver_Manager::GetServerArg();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            Webserver_Manager::SendJsonResponse(400, "ERROR", "Invalid JSON");
            return;
        }

        Webserver_Manager::SendJsonResponse(200, "OK", "Success");

    }
}