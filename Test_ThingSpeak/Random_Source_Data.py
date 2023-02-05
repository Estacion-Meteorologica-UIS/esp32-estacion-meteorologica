# -*- coding: utf-8 -*-
"""
Created on Sat Feb  4 15:42:45 2023

@author: User
"""

import requests
import random
import time

####Funciones #### 
def change_data(inicial):      
    '''
    Toma el valor actual de la medida y lo actualiza aleatoriamente. Regresa el nuevo valor

    Parameters
    ----------
    inicial : TYPE float
        DESCRIPTION. Es el valor del que parte

    Returns
    -------
    TYPE float
        DESCRIPTION. es el nuevo valor. 

    '''
    return round(inicial+random.random()*4-2,2) #(desde -2 a 2)

######### MAIN ####################

variables=["Temperatura","Humedad","Material Particulado","UV","CO2"]  
valores=[25.0, 50.0, 100.0, 20.0, 410.0 ] #con estos valores  inicia
    
while True:
    isanswer=False
    print("--------------------------")
    
    
    valores=[change_data(numero) for numero in valores] #hace una modificacion aleatoria a cada numero    
    
    http_send=('https://api.thingspeak.com/update?api_key=QFNSJOW53EFZ9Q3Y'+
               '&field1='+str(valores[0])+
               '&field2='+str(valores[1])+
               '&field3='+str(valores[2])+
               '&field4='+str(valores[3])+
               '&field5='+str(valores[4]))
       
    while not isanswer: # mientras no tenga la respuesta, seguira intentandolo cada 5 segs
        time.sleep(5)
        try:
            x = requests.get(http_send, timeout=10) # Hacer peticion por 10 segs como mucho 
            if x.text==0:
                isanswer=False
                print("intento fallo, el servidor nego la peticion (peticiones frecuentes)")
            else:
                isanswer=True               
            
        except:
            print("intento fallo, el servidor no responde")
            isanswer=False     
   
    print("Datos enviados") #imprimir los datos
    for palabra,numero in zip(variables,valores):
        print(palabra+": ",+numero)
        
    
    print("Respuesta del servidor: "+ str(x.text))
    print("Durmiendo...")
    time.sleep(60)
    print("...desperte")
    


