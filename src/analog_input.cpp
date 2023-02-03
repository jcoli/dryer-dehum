/**
Version: 0a
Tecnocoli - 02/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
Mega2560 - Dryer
**/
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "io_defines.h"
#include "defines.h"

#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

void analog_input_begin();
void readValues();
void mostra_endereco_sensor(DeviceAddress deviceAddress);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors_ds18b20(&oneWire);
// DeviceAddress ds18b20_ad;
//28 EE AF BD 21 16 02 B1 -- Sensor 1
DeviceAddress Probe01 = { 0x28, 0xEE, 0xAF, 0xBD, 0x21, 0x16, 0x02, 0xB1 };
//28 EE 48 C5 21 16 02 8E -- Sensor 2
DeviceAddress Probe02 = { 0x28, 0xEE, 0x48, 0xC5, 0x21, 0x16, 0x02, 0x8E };
DeviceAddress sensor1;

extern float tempProb1;
extern float tempProb2;
extern float hum_dht11;
extern float temp_dht11;;

void analog_input_begin(){
  sensors_ds18b20.begin();
  sensors_ds18b20.setResolution(Probe01, 12);
  sensors_ds18b20.setResolution(Probe02, 12);
   Serial.print(sensors_ds18b20.getDeviceCount(), DEC);
   Serial.println(" sensors_ds18b20");
   // Serial.print(sensors_ds18b20.getDeviceCount(), DEC);
  // Serial.println(" sensors_ds18b20");
  

  // Serial.println("Localizando sensores DS18B20...");
  // Serial.print("Foram encontrados ");
  // Serial.print(sensors_ds18b20.getDeviceCount(), DEC);
  // Serial.println(" sensores.");
  // if (!sensors_ds18b20.getAddress(sensor1, 0)) 
  //    Serial.println("Sensores nao encontrados !"); 
  // // Mostra o endereco do sensor encontrado no barramento
  // Serial.print("Endereco sensor: ");
  // mostra_endereco_sensor(sensor1);
  dht.begin();
  delay(200);
  readValues();  

}


void readValues(){
  sensors_ds18b20.requestTemperatures();
  
  tempProb1 = sensors_ds18b20.getTempC(Probe01);
  tempProb2 = sensors_ds18b20.getTempC(Probe02);
  hum_dht11 = dht.readHumidity();
  temp_dht11 = dht.readTemperature();
  
  if ((tempProb1>100) || (tempProb1<0)){
      if (temp_dht11>0){
        tempProb1 = temp_dht11;
      }else{
        tempProb1 = 5.0;
      }
      
  }
  if ((tempProb2>100)  || (tempProb2<0)){
    Serial.println("pROBE 2");
       if (temp_dht11>0){
        tempProb2 = temp_dht11;
      }else{
        tempProb2 = 6.0;
      }
  }
  if (hum_dht11<0){
    hum_dht11 = 30.0;
  }
  Serial.println("=======");
    Serial.println(tempProb1);
    Serial.println(tempProb2);
    Serial.println(temp_dht11);
    Serial.println(hum_dht11); 
    Serial.println("=======");
  
  
}


void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16)
      Serial.println("0");
    Serial.print(deviceAddress[i], HEX);
  }
}