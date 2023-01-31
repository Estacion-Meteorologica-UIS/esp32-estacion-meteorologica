#include "material_particulado.h"
#include "sensorhum.h"
#include "UV.h"
void setup() {
  Serial.begin(9600);
  setup_material_particulado();
  setup_sensorhum();
  setupUV();
  // put your setup code here, to run once:

}

void loop() {
  delay(1000);  
  float MaterialParticulado = LeerSensorMaterialParticulado(); //tiempo de ejecucion de 1 seg (N*10 ms)
  float Ultra_Violeta = LeerSensorUV();
  float Humedad = leerhumedad();
  float Temperatura = leertemperatura(); 
  
  // put your main code here, to run repeatedly:

}
