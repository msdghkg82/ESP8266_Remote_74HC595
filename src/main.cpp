#include <Arduino.h>
#include "Webserver_Manager.h"
#include "WiFi_Manager.h"
#include "Remote_Driver.h"
#include "74HC595_Driver.h"

// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  WiFiManager::init();
  WebserverManager::init();
  RemoteDriver::init();
  HC595Driver::init();
}

void loop() {
  // put your main code here, to run repeatedly:
  WebserverManager::handleClient();
}

// put function definitions here:
