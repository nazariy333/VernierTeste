#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include "../queues/queues.hpp"

namespace Network
{
    void setup_wifi();

    void taskNetwork(void *pvParameters);
}