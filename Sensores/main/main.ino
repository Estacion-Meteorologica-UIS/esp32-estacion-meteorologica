/*Falta tomar tension en terminales(pcb)del sensonr de uv y la tension de salida del particulado-->>> Terminar de calibrar
 * Definir tiempo de sueño profundo de esp
 * Ya se corrigio errores de calibracion en sensor de humedad-temperatura y en co2 
 * PARA SUBIR CODIGO A ESP32, DECANECTAR DE FUENTE DE ALIMENTACION EXTERNA Y SELECCIONAR  ESP32 DEV MODULE SINO LA ESP32 WROVER MODULE 
 * Cambiar link de envio de datos 
 */


#include "material_particulado.h"
#include "sensorhum.h"
#include "UV.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

/////CO2//////
#include <Adafruit_SGP30.h> //Libreria del sensor de CO2
Adafruit_SGP30 sgp;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 10  // tiempo en segundo

const char* SSID = "";//Nombde de red wifi
const char* PASSWORD = "";//contraseña 

const char* serverName = "https://api.thingspeak.com/update?api_key=L62DGBD7ZYY9K02O";//definir link para server 

int counter = 0;
int counter1 = 0;

void setup() {
  Serial.begin(115200);
  setup_material_particulado();
  setup_sensorhum();
  setupUV();
  
  //////////////////CO2
  if(! sgp.begin()){ //Alerta por si la ESP no detecta el sensor
    Serial.println("Sensor no encontrado.");    
  }

  WiFi.begin(SSID, PASSWORD);
  Serial.println("conectando parapapapa...");
  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer puesto para un delay de 2 segundos, demora 2 segundos antes de mandar el primer dato.");
  delay(2000);
}


void loop() {
    float MaterialParticulado = LeerSensorMaterialParticulado(); //tiempo de ejecucion de 1 seg (N*10 ms)
    float Ultra_Violeta = LeerSensorUV();
    float Humedad = leerhumedad();
    float Temperatura = leertemperatura();
    float co2 = leerco2();
    delay(2000);
  
  if(isnan(Temperatura)or isnan(Humedad) or isnan(Ultra_Violeta)or co2==-1 or MaterialParticulado == 0){
    float MaterialParticulado = LeerSensorMaterialParticulado(); //tiempo de ejecucion de 1 seg (N*10 ms)
    delay(1000);
    float Ultra_Violeta = LeerSensorUV();
    float Humedad = leerhumedad();
    float Temperatura = leertemperatura();
    float co2 = leerco2();
    Serial.println("-------------------RESUMEN-------------------");
    Serial.println("Material Particulado: "+String(MaterialParticulado));
    Serial.println(" C02: "+String(co2));
    Serial.println(" Temperatura: "+String(Temperatura)+"°C");
    Serial.println(" Humedad: "+String(Humedad)+"%");
    Serial.println(" Ultra Violeta: "+String(Ultra_Violeta)+"mW/m2");
    }
   else{
    if(counter1<3){
      float MaterialParticulado = LeerSensorMaterialParticulado(); //tiempo de ejecucion de 1 seg (N*10 ms)
      delay(1000);
      float Ultra_Violeta = LeerSensorUV();
      float Humedad = leerhumedad();
      float Temperatura = leertemperatura();
      float co2 = leerco2();
      Serial.println("-------------------RESUMEN-------------------");
      Serial.println("Material Particulado: "+String(MaterialParticulado));
      Serial.println(" C02: "+String(co2));
      Serial.println(" Temperatura: "+String(Temperatura)+"°C");
      Serial.println(" Humedad: "+String(Humedad)+"%");
      Serial.println(" Ultra Violeta: "+String(Ultra_Violeta)+"mW/m2");
      counter1++;
      }
      else{
          if(WiFi.status() == WL_CONNECTED) {
            
            WiFiClient client;
            HTTPClient http;
            //Linea de envio de datos
            String data = "&field1=" + String(MaterialParticulado)+ "&field2="+String(co2)+ "&field3="+String(Temperatura)+ "&field4="+String(Humedad)+ "&field5="+String(Ultra_Violeta);
            //--------------------------------------------------------------------------------
            String serverPath = serverName + data;
            http.begin(serverPath.c_str());
            int httpResponseCode = http.GET();
                     
            Serial.print("Código de respuesta: ");
            Serial.println(httpResponseCode);
            http.end();
          }
         else{
            Serial.println("Desconectado de la red WiFi");
          }
        }
      
    counter1 = 0;
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);//inicio de conteo para despertar
    esp_deep_sleep_start();  
  }

}

////CO2//////
float leerco2(){
  if(! sgp.IAQmeasure()){ //Mensaje de error por si hay problemas al sensar 
    Serial.println("Medición fallida.");
    return -1;
  }

  if(! sgp.IAQmeasureRaw()){ //Indicar errores en caso de falla en la medición
    return -1;
  }
  delay(1000);

  counter++;

  //Revisar funcionalidad en la documentación
  if (counter == 30){ //Contador para (LLENAR)
    counter = 0;
    uint16_t TVOC_base, eCO2_base;
    if(! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)){  //Indicar errores en caso de falla en la medición
      Serial.println("Error al obtener las lecturas de referencia.");
      return -1;
    }
  }
  return sgp.eCO2;
}
