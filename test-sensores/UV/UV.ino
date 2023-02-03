/////////////////////////////////////////////////////////////////////////////
// Sensor UV
//
// Board Connection:
//
// Serial monitor setting:
//   9600 baud
/////////////////////////////////////////////////////////////////////////////
// Codigo base de: 
// Codigo modificado por: 
// David Fontalvo
// Codigo Revisado por:
// Juan Sebastian Guerrero
/////////////////////////////////////////////////////////////////////////////
// Definición de pines.
#include <Wire.h>  
 int UVOUT = 15;  // Se conecta eñ D15 a la salida del sensor 
 int REF_3V3 = 4; //D4 se conecta con los 3.3V 
 
float LeerSensorUV() 
{ int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  float outputVoltage = (3.3 / refLevel) * uvLevel;

//Convierte el voltaje leído por el senor a un nivel de intensidad UV en mW/cm^2.
  float uvIntensity = mapfloat(outputVoltage, 0.89 , 2.8, 0.0, 15.0); 
//Sin luz UV (0.0mW/cm^2) la salida del sensor es aproximadamente 1V, pero me lee 0.89V
//Con máximo valor que puede leer es 15mW/cm^2 da 2.8V a la salida del sensor.

//También se imprime el voltaje de salida del sensor, -------------------------
//pero es poder verlo y tenerlo de referencia en la conversión en mapfloat():
  Serial.println("Lectura: "+String("ML8511 voltage: ")+ 
  outputVoltage+String(" ----- UV Intensity (mW/cm^2): ")+uvIntensity);
  delay(500); }
  
//Toma un promedio de lecturas en un pin dado------------------------------------
//Retorna el promedio
int averageAnalogRead(int pinToRead)
{ byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
    runningValue /= numberOfReadings;
  return(runningValue);  }

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{ return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }
//--------------------------------------------------------------------------------
void setup()
{ Serial.begin(9600); 
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT); }

 
void loop()
{
  float Ultra_Violeta = LeerSensorUV();  }

// ---- uvIntensity es el valor de lz UV en mW/cm^2 ----
