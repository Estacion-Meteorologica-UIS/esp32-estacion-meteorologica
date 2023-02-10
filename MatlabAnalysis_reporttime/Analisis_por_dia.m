% Read temperature data from a ThingSpeak channel over the past 24 hours 
% to calculate the high and low temperatures and write to another channel. 
   
% Channel ID to read data from 
readChannelID = 2026238;    %Estación Meteorológica UIS 3-hora
TemperatureFieldID = 1;
HumidityFieldID = 2; 
MaterialparticuladoFieldID = 3; 
UVFieldID = 4; 
COFieldID = 5;
maximostemperaturaID=6;
minimostemperaturaID=7;
maximosuvID=8;
   
readAPIKey = 'RTVUH9H2BB5SYAGS'; %Estación Meteorológica UIS 3-hora
   
%son 1440 minutos en un dia
tempF1 = thingSpeakRead(readChannelID,'Fields',[maximostemperaturaID,minimostemperaturaID], ...
                                                'NumMinutes',1440,'ReadKey',readAPIKey); 

maxTempF = max(tempF1(:,1)); 
minTempF = min(tempF1(:,2));


uvF = thingSpeakRead(readChannelID,'Fields',maximosuvID, ...
                                                'NumMinutes',1440,'ReadKey',readAPIKey); 

maxuv = max(uvF); 
 
datos = thingSpeakRead(readChannelID,'Fields',[1,2,3,4,5],'NumMinutes',1440,'ReadKey',readAPIKey);

avg=mean(datos);

writeChannelID = 2026239;       %Estación Meteorológica UIS 3-dia
writeAPIKey = '0DV7UFOL90UAOVP3';       %Estación Meteorológica UIS 3-dia
   
thingSpeakWrite(writeChannelID,[avg,maxTempF,minTempF,maxuv],'Fields',[1,2,3,4,5,6,7,8],'WriteKey',writeAPIKey);
