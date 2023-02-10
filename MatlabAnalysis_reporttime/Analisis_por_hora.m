% Read temperature data from a ThingSpeak channel over the past 1 hour 
% to calculate the high and low temperatures and write to another channel. 
   
% Channel ID to read data from 
readChannelID = 2026237; %Estación Meteorológica UIS 3-live

TemperatureFieldID = 1;
HumidityFieldID = 2; 
MaterialparticuladoFieldID = 3; 
UVFieldID = 4; 
COFieldID = 5; 
   
readAPIKey = 'RTVUH9H2BB5SYAGS'; %Estación Meteorológica UIS 3-live
   
tempF = thingSpeakRead(readChannelID,'Fields',TemperatureFieldID, ...
                                                'NumMinutes',60,'ReadKey',readAPIKey); 

maxTempF = max(tempF); 
minTempF = min(tempF); 


uvF = thingSpeakRead(readChannelID,'Fields',UVFieldID, ...
                                                'NumMinutes',60,'ReadKey',readAPIKey); 

maxuv = max(uvF); 
minuv = min(uvF); 


datos = thingSpeakRead(readChannelID,'Fields',[1,2,3,4,5],'NumMinutes',60,'ReadKey',readAPIKey);

avg=mean(datos);

writeChannelID = 2026238;       %Estación Meteorológica UIS 3-hora
writeAPIKey = 'OQHJJ588QLCEV02T';       %Estación Meteorológica UIS 3-hora
   
thingSpeakWrite(writeChannelID,[avg,maxTempF,minTempF,maxuv],'Fields',[1,2,3,4,5,6,7,8],'WriteKey',writeAPIKey);
