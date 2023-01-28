#include <DHT.h>
#include <DHT_U.h>
#include <dummy.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(9600);
Serial.println(F("DHTxx test!"));

dht.begin();
}

void loop() {
delay(2000); //Es un sensor lento, por lo que hay que darle tiempo.
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
Serial.println(F("Failed to read from DHT sensor!"));
return;
}

Serial.print(F("Humedad: "));
Serial.print(h);
Serial.print(F("% Temperatura: "));
Serial.print(t);
Serial.println(F("°C "));
}
