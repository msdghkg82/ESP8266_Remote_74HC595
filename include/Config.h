#pragma once

//==== Pin Definitions ====
// Remote Receiver Pin
#define RECEIVER_PIN 2

// 74HC595 Pin Definitions
#define DATA_PIN 12
#define CLOCK_PIN 13
#define LATCH_PIN 14
//==== End of Pin Definitions ====

//==== Other Configurations ====
// OTA Update Configuration
#define OTA_USERNAME "admin"
#define OTA_PASSWORD "admin"

// WiFi Configuration
// Access Point (AP) Configuration
#define AP_SSID_DEFAULT "ESP"
#define AP_PASSWORD_DEFAULT ""

// Station (STA) Configuration
#define STA_SSID ""
#define STA_PASSWORD ""
//==== End of Other Configuration ====

//==== Storage Paths ====
#define WIFI_FILE "/wifi.config"