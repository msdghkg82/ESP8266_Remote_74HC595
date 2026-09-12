#include <Arduino.h>
#include "Webserver_Manager.h"
#include "WiFi_Manager.h"
#include "RF_Remote_Driver.h"
#include "74HC595_Driver.h"

// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  WiFi_Manager::init();
  Webserver_Manager::init();
  RF_Remote_Driver::init();
  HC595_Driver::init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Webserver_Manager::handleClient();
}

// put function definitions here:
