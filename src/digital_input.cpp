/**
Version: 0a
Tecnocoli - 02/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
Mega2560 - Dryer
**/
#include <Arduino.h>
#include <Nextion.h>

#include "io_defines.h"
#include "defines.h"
#include "digital_input.h"
#include "digital_output.h"
#include "analog_input.h"
#include "display.h"

void digital_input_begin();
void door_status_func();
void water_status_func();

extern NexHotspot bStart;

extern NexText txPorta;
extern NexText txReser;
// extern NexNumber fTQuente;
// extern NexNumber fUmidade;
extern NexPage page0;
extern NexPage page1;
extern NexVariable va0;

extern bool door_status;
extern bool water_status;
extern bool on_status;
extern bool start_init;
extern bool alarm_status;
extern bool start_status;
extern bool sleep_status;
extern bool screensaver_status;

extern float tempProb1;
extern float tempProb2;
extern float hum_dht11;
extern float temp_dht11;

extern unsigned long loopDelay;
extern unsigned long loopDelay_readValue;
extern unsigned long loopDelay_cycle;
extern unsigned long loopDelay_toSleep;
extern unsigned long loopDelay_toScreen;





void digital_input_begin(){
    pinMode(INDOOR, INPUT_PULLUP);
    pinMode(INWATER, INPUT_PULLUP);
    pinMode(IN02, INPUT_PULLUP);
    pinMode(IN03, INPUT_PULLUP);
    pinMode(IN04, INPUT_PULLUP);
    pinMode(IN05, INPUT_PULLUP);
    pinMode(IN06, INPUT_PULLUP);
    pinMode(IN07, INPUT_PULLUP);

}


void door_status_func(){
    // Serial.println("door status");
    if ((!digitalRead(INDOOR) != door_status) || (start_init)){
        if(!digitalRead(INDOOR)){
            // Serial.println("door status 1");
            door_status = true;
            if (water_status){
                alarm_status = false;
            }
            loopDelay_toSleep = millis();
            loopDelay_toScreen = millis();
            digitalWrite(OULI1, LOW);
            // digitalWrite(OULI3, LOW);
            display_door();
            
        }else if(door_status) {
            // Serial.println("door status 2");
            door_status = false;
            alarm_status = true;
            on_status = true;
            digitalWrite(OULI1, HIGH);
            // digitalWrite(OULI3, HIGH);
            // digitalWrite(LED_VD, HIGH);
            if (alarm_status){
                    digitalWrite(LED_AL, HIGH);
            }else{
                    digitalWrite(LED_AL, LOW);
            }
            if (sleep_status){
                display_after_sleep();
                loopDelay_toSleep = millis();
                loopDelay_toScreen = millis();     
            }else{
                 display_door();
            }    
            int melody1[] = { 2551, 3551};  // notes in the melody
            int noteDurations[] = { 8, 8}; 
            for (int thisNote = 0; thisNote < 2; thisNote++) {   
                int noteDuration = 1000 / noteDurations[thisNote]; 
                tone(BUZZER_PIN, melody1[thisNote], noteDuration); 
                int pauseBetweenNotes = noteDuration * 1.30;       
                delay(pauseBetweenNotes);                          
                noTone(BUZZER_PIN);          
            }
            screensaver_status = false;
            

        }else if(start_init){
            // Serial.println("door status 1");
            door_status = false;
            alarm_status = true;
            display_init();
        }
    }else if((!door_status) && (start_status)){
        // Serial.println("door status 2");
        int melody1[] = { 2551, 3551};  // notes in the melody
        int noteDurations[] = { 4, 4}; 
        for (int thisNote = 0; thisNote < 2; thisNote++) {   
            int noteDuration = 500 / noteDurations[thisNote]; 
            tone(BUZZER_PIN, melody1[thisNote], noteDuration); 
            int pauseBetweenNotes = noteDuration * 1.30;       
            delay(pauseBetweenNotes);                          
            noTone(BUZZER_PIN);          
        }
        
    }    
}

void water_status_func(){
     
    if ((!digitalRead(INWATER) != water_status)  || (start_init)){
        // Serial.println("water status");
        if(!digitalRead(INWATER)){
            // Serial.println("water status 1");
            water_status = true;
            if (door_status){
                alarm_status = false;
            }

        }else{
            // Serial.println("water status 2");
            alarm_status = true;
            water_status = false;
            int melody1[] = { 2650, 2400, 2650, 2400, 2650, 2400 };  // notes in the melody
            int noteDurations[] = { 8, 8, 8, 8, 8, 8}; 
            for (int thisNote = 0; thisNote < 6; thisNote++) {   
                int noteDuration = 1000 / noteDurations[thisNote]; 
                tone(BUZZER_PIN, melody1[thisNote], noteDuration); 
                int pauseBetweenNotes = noteDuration * 1.30;       
                delay(pauseBetweenNotes);                          
                noTone(BUZZER_PIN);          
            }
        }
        display_water();   
    }
}  
