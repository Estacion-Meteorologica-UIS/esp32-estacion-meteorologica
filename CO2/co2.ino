//Código inicial, creado usando como referencia la documentación proporcionada por Adafruit
//Programado por: Sergio Sebastián Oliveros Sepúlveda y Jorge Angarita
//El uso de este código fue utilizado para una de las asignaciones de laboratorio

#include <Wire.h>
#include <Adafruit_SGP30.h> //Libreria del sensor de CO2

Adafruit_SGP30 sgp;
int counter = 0;

void setup() {
  Serial.begin(9600);
  if(! sgp.begin()){ //Alerta por si la ESP no detecta el sensor
    Serial.println("Sensor no encontrado.");    
    while(1);
  }
}

float leerco2(){
  if(! sgp.IAQmeasure()){ //Mensaje de error por si hay problemas al sensar 
    Serial.println("Medición fallida.");
    return -1;
  }

  //Medir los compuestos orgánicos volátiles totales (Compuestos perjudiciales para la salud) en partes por billón:
  Serial.print("TVOC: "); Serial.print(sgp.TVOC); Serial.println(" ppb/t.");  
  //Medir el dióxido de carbono equivalente calculado (de 0 a 60000 partes por millón):
  Serial.print("eCO2: "); Serial.print(sgp.eCO2); Serial.println(" ppm");

  if(! sgp.IAQmeasureRaw()){ //Indicar errores en caso de falla en la medición
    Serial.println("Medición sin procesar fallida.");
    return -1;
  }
  //El sensor usa medidiciones de H2 para estimar el valor del eCO2:
  //Falta revisar bien estas funciones:
  //Obtener medidas brutas de H2 y etanol: 
  Serial.print("Raw H2: "); Serial.print(sgp.rawH2); Serial.print(" /t");
  Serial.print("Raw etanol: "); Serial.println(sgp.rawEthanol); 

  delay(100);

  counter++;

  //Revisar funcionalidad en la documentación
  if (counter == 30){ //Contador para (LLENAR)
    counter = 0;
    uint16_t TVOC_base, eCO2_base;
    if(! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)){  //Indicar errores en caso de falla en la medición
      Serial.println("Error al obtener las lecturas de referencia.");
      return -1;
    }
    Serial.print("****Lecturasde referencia: eCO2: 0x"); Serial.print(eCO2_base, HEX); 
    Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
  }
  return sgp.eCO2;
  

}

void loop() {
  float c02 = leerco2();
  Serial.print("Returned: "+ String(c02));
  
}
