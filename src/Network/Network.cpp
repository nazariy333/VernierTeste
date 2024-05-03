#include "Network.hpp"

#define ENV_SSID "TP-Link_24E3"
#define ENV_PASSWORD "35677529"

namespace Network
{


    void setup_wifi()
    {
        Serial.println();
        Serial.print("Connecting to STA");
        Serial.println(ENV_SSID);

        WiFi.mode(WIFI_AP_STA);
        WiFi.begin(ENV_SSID, ENV_PASSWORD);

        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Network: Trying to connect");
            vTaskDelay(750/portTICK_PERIOD_MS);
        }
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
      
    }

    void taskNetwork(void *pvParameters)
    {
        setup_wifi();

        Serial.println("Network: Booted");
        while (true)
        {
            vTaskDelay(2500 / portTICK_PERIOD_MS);
        }
    }
}