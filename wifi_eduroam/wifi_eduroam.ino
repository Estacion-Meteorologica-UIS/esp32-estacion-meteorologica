/* Credits: https://github.com/martinius96/ESP32-eduroam
 */

#include <WiFi.h>
#include <esp_wpa2.h>
#include <ThingSpeak.h>

byte mac[6];

// Configuracion WiFi
const char* ssid = "eduroam";
#define EAP_ANONYMOUS_IDENTITY ""  // Dejar campo vacio
#define EAP_IDENTITY "<codigo>@uis.edu.co"  // Ejemplo: "2191472@uis.edu.co"
#define EAP_PASSWORD "<contrasena>"  // Contraseña sistema UIS

// Configuracion ThingSpeak
unsigned long channelID = 2007719;
const char* WriteAPIKey = "62SBQSM99SCRXMQT";
WiFiClient cliente;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // WiFi setup
  Serial.print(F("Connecting to network: "));
  Serial.println(ssid);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_ANONYMOUS_IDENTITY, EAP_IDENTITY, EAP_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  
  Serial.println("");
  Serial.println(F("WiFi is connected!"));
  Serial.print(F("IP address set: "));
  Serial.println(WiFi.localIP());

  // Print MAC Address (Optional)
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[0], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.println(mac[5], HEX);
  
  // ThingSpeak setup
  ThingSpeak.begin(cliente);
}

void loop() {
  ThingSpeak.setField (1,random(25,29));
  ThingSpeak.setField (2,random(50,60));
  // Ejemplo del uso del campo "Status"
  // Se podría usar para enviar errores o información de la ESP como informacion de la bateria
  ThingSpeak.setStatus("Connected from UIS with ESP32");
  
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Data sent to ThingSpeak!");
  delay(20000);
}
