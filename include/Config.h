#pragma once

#include <Arduino.h>

//==== Pin Definitions ====
// Remote Receiver Pin
#define RECEIVER_PIN 2

// 74HC595 Pin Definitions
#define DATA_PIN 12
#define CLOCK_PIN 13
#define LATCH_PIN 14
//==== End of Pin Definitions ====



//==== API Paths & Methods ====
#define WIFI_API     "/api/wifi", HTTP_PUT
//==== End of API Paths & Methods ====



//==== Other Configurations ====
// OTA Update Configuration
#define OTA_USERNAME "admin"
#define OTA_PASSWORD "admin"

// WiFi Configuration
// Access Point (AP) Configuration
inline String AP_SSID = "ESP";
inline String AP_PASSWORD = "";

// Station (STA) Configuration
#define STA_SSID ""
#define STA_PASSWORD ""
//==== End of Other Configuration ====



//==== Storage Paths ====
// WiFi Config Path
#define WIFI_FILE "/wifi.json"
//==== End of Storage Paths ====