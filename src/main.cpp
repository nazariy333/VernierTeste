#include <Arduino.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "vernierSens/vernier.hpp"


void setup() {
  Serial.begin(115200);
  pinMode(33, INPUT);
  xTaskCreate( taskVernier, "taskVernier", 4*1024, NULL, 1, NULL);
}

void loop() {
//? full of nothing
vTaskDelay(1000/portTICK_PERIOD_MS);
}

