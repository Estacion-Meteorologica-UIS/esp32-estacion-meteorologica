#include "material_particulado.h"
#include "sensorhum.h"
#include "UV.h"
#include "co2.h"

void setup() {
  Serial.begin(115200);
  setup_material_particulado();
  setup_sensorhum();
  setupUV();
  //setup_co2();
  // put your setup code here, to run once:

}

void loop() {
  delay(1000);  
  float MaterialParticulado = LeerSensorMaterialParticulado(); //tiempo de ejecucion de 1 seg (N*10 ms)
  float Ultra_Violeta = LeerSensorUV();
  float Humedad = leerhumedad();
  float Temperatura = leertemperatura();
  
  //float co2=10;
  float co2 = leerco2();

  Serial.println("-------------------RESUMEN-------------------");
  Serial.println("Material Particulado: "+String(MaterialParticulado)+" Ultra Violeta: "+String(Ultra_Violeta)+" Humedad: "+String(Humedad)+" Temperatura: "+String(Temperatura)+" C02: "+String(co2));
  // put your main code here, to run repeatedly:

}
