#include "vernier.hpp"

void taskVernier (void * pvpar )
{
    while (1)
    {
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}