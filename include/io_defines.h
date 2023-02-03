/**
Version: 0a
Tecnocoli - 02/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
Mega2560 - Dryer
**/

#ifndef __IO_DEFINES_H__
#define __IO_DEFINES_H__

// Buttons
#define BT0 36  //ON - OFF
#define BT1 37  //Start - Pause
#define BT2 35  
#define BT3 34
#define BT4 33 // door open
#define BT5 32 // water limit

//DHT
#define DHT_PIN 2

//Buzzer
#define BUZZER_PIN 6 

//DS18B20 - OneWire
#define ONE_WIRE_BUS 3

//Leds
#define LED_PT 9 //VD 
#define LED_HT 8 //AM
#define LED_RUN 10 //AZ
#define LED_AL 11 //VM
#define LED_PW 12 //BR





// Displaymostra_endereco_se
// Digital Input 
#define INDOOR 22 //Door
#define INWATER 23 //Water
#define IN02 24 
#define IN03 25
#define IN04 26 
#define IN05 27
#define IN06 28 
#define IN07 29 //Power Source



// Digital Output
#define OUPS1 44 
#define OUPT1 45 //Desum 1
#define OUPT2 43 
#define OUHT1 46 //Heater 1
#define OUCL1 47 //Cooler 1
#define OUCL2 49 //Cooler 2 
#define OUCL3 48 //Cooler 3 //
#define OULI1 51 //Light 1
#define OULI2 50 //Light 2
#define OULI3 40 

//Peltier 2
//Power Source

#endif
