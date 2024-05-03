#include "queues.hpp"

namespace queues
{

    QueueHandle_t dataVernier; // Mailbox

    void setup()
    {
        dataVernier = xQueueCreate(1, sizeof(VernierReads_t));

    }}