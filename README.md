# ESP32-Estacion-Meteorologica
Dentro de la carpeta sensores encontraras varias carpetas:
## main
Este Codigo integra todos los sensores en un solo codigo. Se usa para probar la estacion completa. Encuentras los siguientes codigos

main: Lee todos los sensores llamando funciones que llaman disitintos ficheros.  
[sensor].cpp: fichero de cada sensor, contiene la inializacion de los sensores, librerias y ejecucion del codigo.  
[sensor].h: Header de cada sensor, le indica al main que funciones va llamar de forma directa.

## Test sensores.
Esta cada uno de los sensores programados como funcion por independiente. Se usa para probar sensores uno por uno.

#   Requisitos y Librerias
Al usar por primera vez la ESP32 Hay que seguir los siguientes pasos:  
Instalar Drivers para que windows reconozca el dispositivo:
1. Descargar: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads : CP210x Universal Windows Driver
2. Instalar: Descomprimir el archivo / click derecho en silabser.inf / instalar.

Para que lea la ESP32 dentro del entorno de arduino es necesario: 
1. Agregar board manager: file/preference/Additional boards Manager URls... Agregar: https://dl.espressif.com/dl/package_esp32_index.json.
2. Instalar: tools/board/board manager ... Buscar ESP32.
3. Elegir Board: tools/boards/esp32/ESP32 Dev Module.   

Para poder correr el codigo es necesario la instalaccion de las siguientes librerias dentro del entorno de arduino:  
De la conexion al servidor:
- Conexión Wifi: WiFi by Arduiono (V 1.2.7).
- Conexión al ThinkSpeak: ThingSpeak by Mathworks (V 2.0.1). 

De los Sensores:

- CO2: Adafruit SGP30 Sensor by Adafruit. (V 2.0.0) y sus dependencias. 
- Humedad y Temperatura: DHT Sensor library by Adafruit. (V 1.4.4) y sus dependencias. 
- UV: Ninguna libreria.
- Material Particulado: Ninguna Libreria.
