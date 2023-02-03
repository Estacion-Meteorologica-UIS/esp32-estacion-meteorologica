/*******************************************************************************
 * Sharp GP2Y1014AU0F Dust Sensor Demo
 * 
 * Board Connection:   
 *   GP2Y1014    Arduino
 *   V-LED       Between R1 and C1
 *   LED-GND     C1 and GND
 *   LED         Pin 7
 *   S-GND       GND
 *   Vo          A5
 *   Vcc         5V
 *
 * Codigo base de: https://github.com/sharpsensoruser/sharp-sensor-demos/blob/master/sharp_gp2y1014au0f_demo/sharp_gp2y1014au0f_demo.ino
 * Codigo adaptado por:
 *  - Juan Sebastian Guerrero
 *  - Juan Carlos Rondon
 *  - Andres Leonardo Tarazona
*******************************************************************************/

#include <Arduino.h>

// Definicion de Pines
const int sharpLEDPin = 5;   // Arduino digital pin 18 connectado al LED del sensor.
const int sharpVoPin = 4;   // Arduino analog pin 15 connectado al Vo del sensor.

// Para promediar las ultimas N lecturas de voltaje bruto.
#define N 100
static unsigned long VoRawTotal = 0;
static int VoRawCount = 0;

// Configure el voltaje de salida tipico en voltios cuando no haya polvo.
static float Voc = 0.6;
// Use la sensibilidad tipica en unidades de V por 100ug/m3.
const float K = 0.5;


/*******************************************************************************/
void setupSensorMaterialParticulado(){
  pinMode(sharpLEDPin, OUTPUT);
  
  delay(2000);  // Espere dos segundos para el inicio.
  Serial.println("Sensor de Material Particulado Configuardo");
}

float leerSensorMaterialParticulado(){
  VoRawCount = 0;
  VoRawTotal = 0;
  while (VoRawCount < N){ // Tomar N cantidad de muestras
    
    digitalWrite(sharpLEDPin, LOW);  // Encienda el LED del sensor de polvo (Activacion en bajo)
    // Espere 0,28 ms antes de tomar una lectura del voltaje de salida segun las especificaciones
    delayMicroseconds(280);
    
    int VoRaw = analogRead(sharpVoPin);  // Registre el voltaje de salida.
    
    digitalWrite(sharpLEDPin, HIGH);  // Apague el LED del sensor de polvo
    // Espere el resto del ciclo de 10 ms => 10000 - 280 - 100 = 9620 microsegundos.
    delayMicroseconds(9620);
    
    // Aumentar contador para promedio
    VoRawTotal += VoRaw;
    VoRawCount++;
  }
  // Calcule el voltaje promedio de salida en voltios.
  float Vo = 1.0 * VoRawTotal / N;
  Vo = Vo / 1024.0 * 5.0;

  // Convertir a Densidad de Polvo en unidades de ug/m3.
  float dV = Vo - Voc;
  if (dV < 0){  // Se corrige el limite de no polvo
    dV = 0;
    Voc = Vo;
  }
  float dustDensity = dV / K * 100.0;
  
  return dustDensity;
}
