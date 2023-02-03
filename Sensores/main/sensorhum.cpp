
#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup_sensorhum() {
dht.begin();
Serial.println(F("Sensor de humo entro configuracion"));
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
float leerhumedad(){
  return dht.readHumidity();	
}
float leertemperatura(){
  return dht.readTemperature();

}
