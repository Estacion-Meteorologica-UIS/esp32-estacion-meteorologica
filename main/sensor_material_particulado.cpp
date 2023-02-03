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
// Definición de Pines
const int sharpLEDPin = 5;   // Arduino digital pin 18 connectado al LED del sensor.
const int sharpVoPin = 4;   // Arduino analog pin 15 connectado al Vo del sensor.

// Para promediar las últimas N lecturas de voltaje bruto.
#define N 100
static unsigned long VoRawTotal = 0;
static int VoRawCount = 0;

// Configure el voltaje de salida típico en voltios cuando no haya polvo.
static float Voc = 0.6;
// Use la sensibilidad típica en unidades de V por 100ug/m3.
const float K = 0.5;


/*******************************************************************************/
// Funciones auxiliares para imprimir un valor de datos en el monitor serie.

void printValue(String text, unsigned int value, bool isLast = false) {
  Serial.print(text);
  Serial.print("=");
  Serial.print(value);
  if (!isLast){
    Serial.print(", ");
  }
}

void printFValue(String text, float value, String units, bool isLast = false) {
  Serial.print(text);
  Serial.print("=");
  Serial.print(value);
  Serial.print(units);
  if (!isLast) {
    Serial.print(", ");
  }
}

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
    // Encienda el LED del sensor de polvo configurando el pin digital como LOW.
    digitalWrite(sharpLEDPin, LOW);
    
    // Espere 0,28 ms antes de tomar una lectura del voltaje de salida según las especificaciones.
    delayMicroseconds(280);
    
    // Registre el voltaje de salida. Esta operación tarda alrededor de 100 microsegundos.
    int VoRaw = analogRead(sharpVoPin);
    
    // Apague el LED del sensor de polvo configurando el pin digital HIGH.
    digitalWrite(sharpLEDPin, HIGH);
    
    // Espere el resto del ciclo de 10 ms => 10000 - 280 - 100 = 9620 microsegundos.
    delayMicroseconds(9620);
    
    // Imprime el valor de voltaje sin procesar (número de 0 a 1023), mediante la función printValue()
    // printValue("VoRaw", VoRaw, true);
    // Serial.println("");
    
    VoRawTotal += VoRaw;
    VoRawCount++;
  }
  float Vo = 1.0 * VoRawTotal / N;
  Vo = Vo / 1024.0 * 5.0;  // Calcule el voltaje de salida en voltios.
  
  printFValue("Vo", Vo*1000.0, "mV");

  // Convertir a Densidad de Polvo en unidades de ug/m3.
  float dV = Vo - Voc;
  if (dV < 0){  // Se corrige el límite de no polvo
    dV = 0;
    Voc = Vo;
  }
  // imprime la densidad de polvo mediante la función printFvalue
  float dustDensity = dV / K * 100.0;
  printFValue("DustDensity", dustDensity, "ug/m3", true);
  Serial.println("");
  
  return dustDensity;
}
