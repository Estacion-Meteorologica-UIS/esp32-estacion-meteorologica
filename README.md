# ESP32-Estacion-Meteorologica
Dentro de la carpeta sensores encontraras varias carpetas:
## main
Este Codigo integra todos los sensores en un solo codigo. Se usa para probar la estacion completa. Encuentras los siguientes codigos

main: Lee todos los sensores llamando funciones que llaman disitintos ficheros.  
[sensor].cpp: fichero de cada sensor, contiene la inializacion de los sensores, librerias y ejecucion del codigo.  
[sensor].h: Header de cada sensor, le indica al main que funciones va llamar de forma directa.

## Carpetas de sensores.
Esta cada uno de los sensores programados como funcion por independiente. Se usa para probar sensores uno por uno