#include <Arduino.h>
#include <math.h>
#include <MCP3XXX.h>

#include "freertos/FreeRTOS.h"
#include "vernierSens/vernier.hpp"

MCP3008 adc;

void setup() {
  Serial.begin(115200);
  adc.begin();

  //pinMode(33, INPUT);
  xTaskCreate( taskVernier, "taskVernier", 4*1024, NULL, 1, NULL);
}

void loop() {
//? full of nothing
vTaskDelay(1000/portTICK_PERIOD_MS);
}

