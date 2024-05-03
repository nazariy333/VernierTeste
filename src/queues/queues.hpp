#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

// Mailbox = Task Overwrite ->[]-> Task Peek

// When sending pointers to allocated memory free them on the receiving task, or if its a mailbox queue free it before overwriting

namespace queues
{
    void setup();

    struct VernierReads_t
    {
        float dataTemp;
        float dataSM;
        float dataPAR;
        float dataLumen;
        float dataORP;
        float dataNH4;
        float dataNO3;
        float dataConduct;
        float dataPH;
    };

 /*  struct I2C_readings_t
    {
        char ph[10];
        char ec[10];
    };
    struct Modbus_readings_t
    {
        float temperature;
        float turbidity;
        float COD;
        float EM_readings[12];
        int pump_RMP;
    };*/

    extern QueueHandle_t dataVernier; // Mailbox
    /*extern QueueHandle_t sta_cred;
    extern QueueHandle_t i2c_readings; // Mailbox
    extern QueueHandle_t modbus_readings; // Mailbox
    extern QueueHandle_t pump_rpm;*/
}