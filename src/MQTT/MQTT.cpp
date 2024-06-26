#include "MQTT.hpp"

namespace MQTT
{
    #define ENV_MQTT_BROKER "192.168.1.132" // endereço a ligar
    #define ENV_SEND_PERIOD_SEC 65

    WiFiClient espClient;
    PubSubClient client(espClient);

    queues::VernierReads_t rcv_vernier_reads;
    char packet[512];

    void callback(char *topic, byte *payload, unsigned int length)
    {
        Serial.print("Message arrived [");
        Serial.print(topic);
        Serial.print("] ");
        for (int i = 0; i < length; i++)
        {
            Serial.print((char)payload[i]);
        }
        Serial.println();
    }

    void reconnect()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
            // Create a random client ID
            String clientId = "ESP32-Nazariy1";
            clientId += String(random(0xffff), HEX);
            // Attempt to connect
            if (client.connect(clientId.c_str()))
            {
                process_data();
                client.publish("sensors/input", packet);
            }
            else
            {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
                vTaskDelay(2000 / portTICK_PERIOD_MS);
            }
        }
    }

    void process_data()
    {
        if(uxQueueMessagesWaiting(queues::dataVernier))
        {
            xQueuePeek(queues::dataVernier, &rcv_vernier_reads, 100 / portTICK_PERIOD_MS);
        }
        //Submerged sensors
        snprintf(packet,512, "{\"ref\":\"sensInVernier\", \"temp\":\"%.2f\", \"sm\":\"%.2f\", \"PAR\":\"%.2f\", \"ORP\":\"%.2f\", \"NO3\":\"%.2f\", \"NH4\":\"%.2f\", \"lum\":\"%.2f\", \"PH\":\"%.2f\", \"condut\":\"%.2f\" }"
        ,rcv_vernier_reads.dataTemp, rcv_vernier_reads.dataSM, rcv_vernier_reads.dataPAR, rcv_vernier_reads.dataORP, rcv_vernier_reads.dataNO3, rcv_vernier_reads.dataNH4, rcv_vernier_reads.dataLumen, rcv_vernier_reads.dataPH, rcv_vernier_reads.dataConduct);
    }
    
    void initialize_values()
    {
        rcv_vernier_reads.dataTemp = 0.0;
        rcv_vernier_reads.dataSM = 0.0;
        rcv_vernier_reads.dataPAR = 0.0;
        rcv_vernier_reads.dataORP = 0.0;
        rcv_vernier_reads.dataPH = 0.0;
        rcv_vernier_reads.dataNO3 = 0.0;
        rcv_vernier_reads.dataNH4 = 0.0;
        rcv_vernier_reads.dataLumen = 0.0;
        rcv_vernier_reads.dataConduct = 0.0;

    }

    void taskMQTT(void *pvParameters) // Task de envio de parametros para o broker
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        client.setServer(ENV_MQTT_BROKER, 1883);
        client.setCallback(callback);
        initialize_values();
        Serial.println("MQTT: Booted");
        while (true)
        {
            if (!client.connected())
            {
                reconnect();
            }
            client.loop();

            process_data();
            client.publish("sensors/input", packet);
            
                //Serial.printf("MQTT: Packet sent: %s",packet);
           
            vTaskDelay(100/portTICK_PERIOD_MS);

        
            vTaskDelay(ENV_SEND_PERIOD_SEC * 1000 / portTICK_PERIOD_MS);
        }
    }
}