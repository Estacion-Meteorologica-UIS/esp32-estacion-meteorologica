/////////////////////////////////////////////////////////////////////////////
// Sharp DHT11 Sensor de Temperatura y Humedad
//
//Tiempo estimado de ejecucion: +2 Segs
//
// Board Connection: https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/04/dht_esp32_bb.png?w=714&quality=100&strip=all&ssl=1
//   
//
// Serial monitor setting:
//   9600 baud
/////////////////////////////////////////////////////////////////////////////
// Codigo base de: https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/
// Codigo dado por: Daniel Cerro
// Codigo modificado por: Juan Sebastian Guerrero
/////////////////////////////////////////////////////////////////////////////

#include <DHT.h>
#include <DHT_U.h>
//#include <dummy.h>

#define DHTPIN 34
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(115200);
Serial.println(F("DHTxx test!"));

dht.begin();
}

void imprimirTyH(float t, float h) {	
	
	if(isnan(h) || isnan(t)){
		Serial.println(F("Failed to read from DHT sensor!"));
		return;
	}
	
	Serial.print(F("Humedad: "));
	Serial.print(h);
	Serial.print(F("% Temperatura: "));
	Serial.print(t);
	Serial.println(F("°C "));	
}

void loop() {

  
	delay(2000); //Es un sensor lento, por lo que hay que darle tiempo.
	float h = dht.readHumidity();
	float t = dht.readTemperature();
  imprimirTyH(t, h); //imprimir en serial
	if(isnan(h) || isnan(t)){ //Si no lee correctamente dar codigo error;
		h = -1; //Codigo de error en la lectura humedad
		t = -1; //Codigo de erro en la lectura temperatria		
	}		
	
}
