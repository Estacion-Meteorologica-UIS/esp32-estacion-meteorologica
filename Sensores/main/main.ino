/* Codigo para ESP32 para hacer la medición de todos los sensores
 * en conjunto. Los resultados de las mediciones son mostrados
 * por comunicación serial
 */

#include "material_particulado.h"
#include "sensorhum.h"
#include "UV.h"

// Sensor CO2
#include <Adafruit_SGP30.h>
int counter = 0;
Adafruit_SGP30 sgp;

void setup(){
  Serial.begin(115200);

  // -------------- Setup Sensores --------------
  setupSensorMaterialParticulado();
  setupSensorTempHum();
  setupSensorUV();
  // CO2
  if (!sgp.begin()) { // Alerta por si la ESP no detecta el sensor
    Serial.println("Sensor de CO2 no encontrado.");
  }

}

void loop(){
  delay(1000);
  
  Serial.println("MEDICIÓN MATERIAL PARTICULADO");
  float material_particulado = leerSensorMaterialParticulado(); // tiempo de ejecucion de 1 seg (N*10 ms)
  Serial.println("MEDICIÓN UV");
  float ultra_violeta = leerSensorUV();
  float humedad = leerSensorHumedad();
  float temperatura = leerSensorTemperatura();
  Serial.println("MEDICIÓN CO2");
  float co2 = leerCO2();

  Serial.println("");
  Serial.println("-----------------------------------------------");
  Serial.println("------------------- RESUMEN -------------------");
  Serial.println("Material Particulado: " + String(material_particulado) +
                 " Ultra Violeta: " + String(ultra_violeta) +
                 " Humedad: " + String(humedad) +
                 " Temperatura: " + String(temperatura) +
                 " C02: " + String(co2));
  Serial.println("");
}


float leerCO2(){
  if (!sgp.IAQmeasure()){  // Alerta en caso de error
    Serial.println("Medición CO2 fallida.");
    return -1;
  }
  // Medir los compuestos orgánicos volátiles totales (Compuestos perjudiciales para la salud) en partes por billón:
  Serial.print("TVOC: "); Serial.print(sgp.TVOC); Serial.println(" ppb/t.");
  // Medir el dióxido de carbono equivalente calculado (de 0 a 60000 partes por millón):
  Serial.print("eCO2: "); Serial.print(sgp.eCO2); Serial.println(" ppm");

  if (!sgp.IAQmeasureRaw()){ // Alerta en caso de error
    Serial.println("Medición CO2 sin procesar fallida.");
    return -1;
  }
  // El sensor usa medidiciones de H2 para estimar el valor del eCO2:
  // Falta revisar bien estas funciones:
  // Obtener medidas brutas de H2 y etanol:
  Serial.print("Raw H2: "); Serial.print(sgp.rawH2); Serial.print(" /t");
  Serial.print("Raw etanol: "); Serial.println(sgp.rawEthanol);

  delay(1000);
  counter++;

  // Revisar funcionalidad en la documentación
  if (counter == 30){ // Contador para (LLENAR)
    counter = 0;
    uint16_t TVOC_base, eCO2_base;
    if (!sgp.getIAQBaseline(&eCO2_base, &TVOC_base)){ // Indicar errores en caso de falla en la medición
      Serial.println("Error al obtener las lecturas de referencia.");
      return -1;
    }
    Serial.print("***Lecturas de referencia: eCO2: 0x");
    Serial.print(eCO2_base, HEX);
    Serial.print(" & TVOC: 0x");
    Serial.println(TVOC_base, HEX);
  }
  return sgp.eCO2;
}
