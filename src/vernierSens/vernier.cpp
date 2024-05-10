#include "vernier.hpp"

namespace Vernier
{

float calcCondut(float raw) { //Sensor de Condutividade
  float slope = 65.70;
  float intercept = 0.00;
  float aux = intercept + raw * slope;
return aux;
}

float calcLumen(float raw) { //Sensor de luminosidade
  float slope = 1692.00;
  float intercept = 0.00;
  float aux = intercept + raw * slope;
 return aux;
}

float calcNH4orNO3(float raw) { //Sensor de ioes de NH4 e NO3
 float aux = (137.55 * raw - 168.20);
 return aux;
}

float calcORP(float raw) {  //Sensor ORP (Oxidation-Reduction Potencial)
  float slope = 108.00;
  float intercept = -42.00;
 float aux = intercept + raw * slope;
 return aux;
}

float calcPAR(float raw) {  //Sensor PAR (Photosynthetically Active Radiation)
  float slope = 500.00;
  float intercept = 0.00;
  float aux = intercept + raw * slope;
 return aux;
}

float calcPH(float raw) {  //Sensor de PH
  float slope = -3.78;
  float intercept = 13.56;
  float aux = intercept + raw * slope;
 return aux;
}

float calcSM(float raw) {  //Sensor de Humidade de Solo
  float slope = 108.00;
  float intercept = -42.00;
 float aux = intercept + raw * slope;
 return aux;
}

float calcTemp(float raw){ //NTC
    float _logR;
    float _resistor;
    float logR;
    float aux;
    _resistor = 15000;// 15k resistor in series with thermistor
    long _resistance = (_resistor * raw ) / (5.0- raw);
    _logR = log(_resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
    aux = 1 / (0.00102119 + (0.000222468 * _logR + (0.000000133342 * _logR * _logR * _logR)));
    aux =  aux - 273.15;  // Convert Kelvin to Celsius
    return aux;
}

void taskVernier (void * pvpar )
{
  queues::VernierReads_t readings;

  MCP3008 adc;
    while (1)
    {
    int numAv = 10; //Average
    float rawCount;
    float voltage;
    float sum = 0.0;
//----------------------------------------------------------    
    for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = adc.analogRead(0);
        sum = sum + rawCount;
    }
  voltage = sum / numAv / 1023.0 * 5.0; 
  sum = 0.0;
  readings.dataTemp = calcTemp(voltage);

  Serial.print("temperatura--->"); //DEBUG PRINT
  Serial.println(readings.dataTemp);
//-----------------------------------------------------------
  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
      rawCount = adc.analogRead(1);
      sum = sum + rawCount;
    }
  voltage = sum / numAv / 1023.0 * 5.0; 
  sum = 0.0;
  readings.dataSM = calcSM(voltage);

  Serial.print("humidade de solo--->");
  Serial.println(readings.dataSM);
//------------------------------------------------------------
  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = adc.analogRead(2);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 1023.0 * 5.0;  
    sum = 0.0;
    readings.dataPAR = calcPAR(voltage);

    Serial.print("PAR--->");
    Serial.println(readings.dataPAR);
//------------------------------------------------------------
  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = adc.analogRead(3);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 1023.0 * 5.0; 
    sum = 0.0;
    readings.dataLumen = calcLumen(voltage);

    Serial.print("luminocidade--->");
    Serial.println(readings.dataLumen);
//------------------------------------------------------------
  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = adc.analogRead(4);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 1023.0 * 5.0; 
    sum = 0.0;
    readings.dataORP = calcORP(voltage);

    Serial.print("ORP--->");
    Serial.println(readings.dataORP);
//------------------------------------------------------------

  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = adc.analogRead(5);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 1023.0 * 5.0; 
    sum = 0.0;
    readings.dataNH4 = calcNH4orNO3(voltage);

    Serial.print("NH4--->");
    Serial.println(readings.dataNH4);
//------------------------------------------------------------

  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = adc.analogRead(6);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 1023.0 * 5.0; 
    sum = 0.0;
    readings.dataNO3 = calcNH4orNO3(voltage);

    Serial.print("NO3--->");
    Serial.println(readings.dataNO3);
//------------------------------------------------------------

  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = adc.analogRead(7);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 1023.0 * 5.0; 
    sum = 0.0;
    readings.dataConduct = calcCondut(voltage);

    Serial.print("Condutividade--->");
    Serial.println(readings.dataConduct);
//------------------------------------------------------------

  for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = analogRead(33);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 1023.0 * 5.0; 
    sum = 0.0;
    readings.dataPH = calcPH(voltage);

    Serial.print("PH--->");
    Serial.println(readings.dataPH);
//------------------------------------------------------------

    xQueueOverwrite(queues::dataVernier, &readings);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}}