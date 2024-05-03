#include <Arduino.h>
#include <math.h>
#include <MCP3XXX.h>

#include "freertos/FreeRTOS.h"
#include "vernierSens/vernier.hpp"
#include "queues/queues.hpp"
#include "Network/Network.hpp"
#include "MQTT/MQTT.hpp"

MCP3008 adc;

TaskHandle_t TaskNetwork;
TaskHandle_t TaskVernier;
TaskHandle_t TaskMQTT;

void setup() {
  Serial.begin(115200);
  adc.begin();

  queues::setup();


  pinMode(33, INPUT);
  xTaskCreate( Network::taskNetwork, "taskNetwork", 5*1024, NULL, 1, &TaskNetwork);
  xTaskCreate( Vernier::taskVernier, "taskVernier", 5*1024, NULL, 1, &TaskVernier);
  xTaskCreate(MQTT::taskMQTT, "TaskMQTT", 5 * 1024, NULL, 1, &TaskMQTT);
}

void loop() {
//? full of nothing
vTaskDelay(1000/portTICK_PERIOD_MS);
}

