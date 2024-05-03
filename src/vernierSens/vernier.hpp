#pragma once

#include <Arduino.h>
#include <math.h>
#include <MCP3XXX.h>
#include "../queues/queues.hpp"

namespace Vernier
{
float calcCondut(float raw);
float calcLumen(float raw);
float calcNH4orNO3(float raw);
float calcORP(float raw);
float calcPAR(float raw);
float calcPH(float raw);
float calcSM(float raw);
float calcTemp(float raw);


void taskVernier (void * pvpar );
}