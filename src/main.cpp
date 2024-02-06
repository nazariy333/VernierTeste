#include <Arduino.h>
#include <math.h>

float calcCondut(float raw) {
  float slope = 65.70;
  float intercept = 0.00;
 float aux = intercept + raw * slope;
 return aux;
}

float calcLumen(float raw) {
  float slope = 1692.00;
  float intercept = 0.00;
  float aux = intercept + raw * slope;
 return aux;
}

float calcNH4orNO3(float raw) {
 float aux = (137.55 * raw - 168.20);
 return aux;
}

float calcORP(float raw) {
  float slope = 108.00;
  float intercept = -42.00;
 float aux = intercept + raw * slope;
 return aux;
}

float calcPAR(float raw) {
  float slope = 500.00;
  float intercept = 0.00;
  float aux = intercept + raw * slope;
 return aux;
}

float calcPH(float raw) {
  float slope = -3.78;
  float intercept = 13.56;
  float aux = intercept + raw * slope;
 return aux;
}

float calcSM(float raw) {
  float slope = 108.00;
  float intercept = -42.00;
 float aux = intercept + raw * slope;
 return aux;
}

float calcTemp(float raw){
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

void setup() {
  Serial.begin(115200);
  pinMode(33, INPUT);
}

void loop() {
 int numAv = 10; //Average
 float rawCount;
 float voltage;
 float _data;
 float sum = 0.0;
for (int i = 0; i < numAv; i++){
  rawCount = analogRead(33);
  sum = sum + rawCount;
}
voltage = sum / numAv / 4095.0 * 5.0;

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
}

