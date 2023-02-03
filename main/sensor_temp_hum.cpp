/*******************************************************************************
 * Sharp DHT11 Sensor de Temperatura y Humedad
 * 
 * Tiempo estimado de ejecucion: +2 Segs
 * 
 * Board Connection: https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/04/dht_esp32_bb.png?w=714&quality=100&strip=all&ssl=1  
 * 
 * Codigo base de: https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/
 * Codigo dado por:
 *  - Daniel Cerro
 * Codigo modificado por:
 *  - Juan Sebastian Guerrero
*******************************************************************************/

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

// Definición de Pines
#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

/*******************************************************************************/
void setupSensorTempHum(){
  dht.begin();
  Serial.println("Sensor de Temperatura y Humedad Configurado");
}

float leerSensorHumedad(){
  return dht.readHumidity();	
}

float leerSensorTemperatura(){
  return dht.readTemperature();
}
