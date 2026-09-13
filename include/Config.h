#pragma once

#include <Arduino.h>

//==== Pin Definitions ====
// Remote Receiver Pin
inline constexpr uint8_t RECEIVER_PIN = 2;

// 74HC595 Pin Definitions
inline constexpr uint8_t DATA_PIN = 12;
inline constexpr uint8_t CLOCK_PIN = 13;
inline constexpr uint8_t LATCH_PIN = 14;
//==== End of Pin Definitions ====



//==== Other Configurations ====
// OTA Update Configuration
inline constexpr char * OTA_USERNAME = "admin";
inline constexpr char * OTA_PASSWORD = "admin";

// WiFi Configuration
// Access Point (AP) Configuration
inline char * AP_SSID = "ESP";
inline char * AP_PASSWORD = "";

// Station (STA) Configuration
inline constexpr char * STA_SSID = "";
inline constexpr char * STA_PASSWORD = "";
//==== End of Other Configuration ====



//==== Storage Paths ====
// WiFi Config Path
inline constexpr char * WIFI_FILE = "/wifi.json";
//==== End of Storage Paths ====