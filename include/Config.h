#pragma once

#include <Arduino.h>

//==== Pin Definitions ====
// Remote Receiver Pin
#define RECEIVER_PIN 2

// 74HC595 Pin Definitions
#define LATCH_PIN 5
#define OE_PIN 4    // For Dimming Outputs
//==== End of Pin Definitions ====



//==== API Paths & Methods ====
#define WIFI_SETTING_API     "/api/wifi", HTTP_PUT
#define HC595_SETMODE_API    "/api/driver/setmode", HTTP_PUT
#define HC595_BRIGHTNESS_API "/api/driver/brightness", HTTP_PUT
#define RF_REMOTE_PAIR_API   "/api/remote/pair", HTTP_PUT
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



//==== RF Remote Configurations ====
inline uint32_t RFRemoteCode;
#define CODE_SHIFT_VALUE 16U
#define DATA_VALUE_MASK 0xFFFF
//==== End of RF Remote Configurations ====



//==== Storage Paths ====
// WiFi Config Path
#define WIFI_FILE "/wifi.json"

// 74HC595 Config Path
#define HC595_FILE "/hc595.json"

// RF Remote Config Path
#define RFREMOTE_FILE "/rfremote.json"
//==== End of Storage Paths ====



//==== Other Configurations ====
// StatusLED Default Blinking Interval
#define DEFAULT_INTERVAL 1000
#define MIN_INTERVAL 200
//==== End of Other Configuration ====