#pragma once

#include <Arduino.h>

//==== Pin Definitions ====
// Remote Receiver Pin
#define RECEIVER_PIN 2

// 74HC595 Pin Definitions
#define LATCH_PIN 4
//==== End of Pin Definitions ====



//==== API Paths & Methods ====
#define WIFI_SETTING_API    "/api/wifi", HTTP_PUT
#define HC595_SETMODE_API    "/api/setmode", HTTP_PUT
//==== End of API Paths & Methods ====



//==== WebServer Configurations ====
// OTA Update Configuration
#define OTA_USERNAME "admin"
#define OTA_PASSWORD "admin"

// WiFi Configuration
// Access Point (AP)
inline String AP_SSID = "ESP";
inline String AP_PASSWORD = "";
// Station (STA)
//inline String STA_SSID = "";
//inline String STA_PASSWORD = "";
//==== End of WebServer Configuration ====



//==== Storage Paths ====
// WiFi Config Path
#define WIFI_FILE "/wifi.json"

// 74HC595 Config Path
#define HC595_MODE_FILE "/hc595_mode.json"
#define HC595_INTERVAL_FILE "/hc595_interval.json"
//==== End of Storage Paths ====



//==== Other Configurations ====
// StatusLED Default Blinking Interval
#define DEFAULT_INTERVAL 1000
//==== End of Other Configuration ====