#include <Arduino.h>
#include <Wire.h>  
int UVOUT = 15;  // Se conecta eñ D15 a la salida del sensor 
int REF_3V3 = 2; //D4 se conecta con los 3.3V 
 
 int averageAnalogRead(int pinToRead)
{ byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
    runningValue /= numberOfReadings;
  return(runningValue);  
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{ return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }
//--------------------------------------------------------------------------------
void setupUV()
{ 
  
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT); 
  Serial.println(F("Sensor de UV entro configuro"));
}

float LeerSensorUV() 
{ int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  float outputVoltage = (3.3 / refLevel) * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.89 , 3, 0.0, 15.0); 
  return uvIntensity;
}
