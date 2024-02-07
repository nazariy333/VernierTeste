#include "vernier.hpp"

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
    while (1)
    {
    int numAv = 10; //Average
    float rawCount;
    float voltage;
    float _data;
    float sum = 0.0;
    for (int i = 0; i < numAv; i++){ //Media de 10 leituras
        rawCount = analogRead(33);
        sum = sum + rawCount;
    }
    voltage = sum / numAv / 4095.0 * 5.0; //!! Leituras sao interpretadas so para 5v 

    //_data = calcCondut(voltage);
    //_data = calcLumen(voltage);
    //_data = calcNH4orNO3(voltage);
    //_data = calcORP(voltage);
    //_data = calcPAR(voltage);
    //_data = calcPH(voltage);
    //_data = calcSM(voltage);
    _data = calcTemp(voltage);

    Serial.print("leitura--->");
    Serial.println(_data);

    vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}