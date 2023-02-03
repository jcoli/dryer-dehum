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

void display_begin();
void display_init();
void display_splachscreen();
void display_page0();
void display_page1();
void display_after_screensaver();
void display_after_sleep();
void display_screensaver();
void display_sleep();
void display_start();
void display_pause();
void display_on();
void display_sleep_on();
void display_water();
void display_door();
void display_start_off();
void display_values();

// extern NexButton bOn;
extern NexHotspot bStart;

extern NexText txPorta;
extern NexText txReser;
extern NexText txRun;
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




void display_begin(){


}

void display_values(){
    // fTQuente.setValue(tempProb1*1);
    // fUmidade.setValue(hum_dht11*1);
    // fUmidade.setValue(10);
    // Serial.print("DHT: ");
    // Serial.print(hum_dht11);
    // Serial.print(" - ");
    // Serial.println(temp_dht11);

}

void display_init(){
  if (door_status){
        // txPorta.setText("Porta Fechada");
        txPorta.Set_background_color_bco(0x07F3);
        txPorta.Set_font_color_pco(0);
    }else{
        // txPorta.setText("Porta Aberta");
        txPorta.Set_background_color_bco(0xF0E3);
        txPorta.Set_font_color_pco(0x0000);
    }
    if (water_status){
        // txReser.setText("Reserv. OK");
        txReser.Set_background_color_bco(0x07F3);
        txReser.Set_font_color_pco(0);
    }else{
        // txReser.setText("Reserv. Cheio");
        txReser.Set_background_color_bco(0xF0E3);
        txReser.Set_font_color_pco(0x0000);
    }

}

void display_on(){
    page1.show();
    // Serial2.write("sleep=0");  //SLEEPING
    // Serial2.write(0xff);
    // Serial2.write(0xff);
    // Serial2.write(0xff);
    delay(200); 
    readValues();
    // fTQuente.setValue(tempProb1*1);
    // fUmidade.setValue(hum_dht11*1);
    
    door_status_func();
    water_status_func();
    int melody[] = { 1908, 2551, 1908, 2551, 1908, 2551, 1908, 2551};  // notes in the melody
    int noteDurations[] = { 4, 4, 4, 4, 4, 4, 8, 8 }; 
    for (int thisNote = 0; thisNote < 8; thisNote++) {   // ergodic all notes
        int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
        tone(BUZZER_PIN, melody[thisNote], noteDuration);   // let speaker sonds
        int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
        delay(pauseBetweenNotes);                          // delay for the while
        noTone(BUZZER_PIN);                                 // stop the tone playing:
    }
    Serial.println("display 0n");
    delay(2000);
    page0.show();
    if (door_status){
        // txPorta.setText("Porta Fechada");
        txPorta.Set_background_color_bco(0x07F3);
        txPorta.Set_font_color_pco(0);
    }else{
        // txPorta.setText("Porta Aberta");
        txPorta.Set_background_color_bco(0xF0E3);
        txPorta.Set_font_color_pco(0x0000);
    }
    if (water_status){
        // txReser.setText("Reserv. OK");
        txReser.Set_background_color_bco(0x07F3);
        txReser.Set_font_color_pco(0);
    }else{
        // txReser.setText("Reserv. Cheio");
        txReser.Set_background_color_bco(0xF0E3);
        txReser.Set_font_color_pco(0x0000);
    }
    va0.setValue(3);
    txRun.Set_background_color_bco(0x07F3);
    
}



void display_start(){
    Serial.println("display Start");
    txRun.Set_background_color_bco(0xF0E3);
    

}

void display_start_off(){
        
    door_status_func();
    water_status_func();
    // int melody[] = { 1908, 2551, 1908, 2551, 1908, 2551, 1908, 2551};  // notes in the melody
    // int noteDurations[] = { 4, 4, 4, 4, 4, 4, 4, 4 }; 
    // for (int thisNote = 0; thisNote < 8; thisNote++) {   // ergodic all notes
    //     int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
    //     tone(BUZZER_PIN, melody[thisNote], noteDuration);   // let speaker sonds
    //     int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
    //     delay(pauseBetweenNotes);                          // delay for the while
    //     noTone(BUZZER_PIN);                                 // stop the tone playing:
    // }
    
    if (door_status){
        // txPorta.setText("Porta Fechada");
        txPorta.Set_background_color_bco(0x07F3);
        txPorta.Set_font_color_pco(0);
    }else{
        // txPorta.setText("Porta Aberta");
        txPorta.Set_background_color_bco(0xF0E3);
        txPorta.Set_font_color_pco(0x0000);
    }
    if (water_status){
        // txReser.setText("Reserv. OK");
        txReser.Set_background_color_bco(0x07F3);
        txReser.Set_font_color_pco(0);
    }else{
        // txReser.setText("Reserv. Cheio");
        txReser.Set_background_color_bco(0xF0E3);
        txReser.Set_font_color_pco(0x0000);
    }
    va0.setValue(3);
    txRun.Set_background_color_bco(0x07F3);
    

}

void display_pause(){
    

}

void display_water(){
    if (water_status){
        // Serial.println("water status 4");
        // txReser.setText("Reserv. OK");
        txReser.Set_background_color_bco(0x07F3);
        txReser.Set_font_color_pco(0);
    }else{
        // Serial.println("water status 5");
        // txReser.setText("Reserv. Cheio");
        txReser.Set_background_color_bco(0xF0E3);
        txReser.Set_font_color_pco(0x0000);
    }
}

void display_door(){
    if (door_status){
        // txPorta.setText("Porta Fechada");
        txPorta.Set_background_color_bco(0x07F3);
        txPorta.Set_font_color_pco(0);
    }else{
        // txPorta.setText("Porta Aberta");
        txPorta.Set_background_color_bco(0xF0E3);
        txPorta.Set_font_color_pco(0x0000);
    }


}


void display_splachscreen(){
    page1.show();
    
}



void display_page0(){
    
}

void display_page1(){
    
}

void display_after_screensaver(){
    
}

void display_after_sleep(){
    if (sleep_status){
        Serial2.write("sleep=0");  //SLEEPING
        Serial2.write(0xff);
        Serial2.write(0xff);
        Serial2.write(0xff);
        delay(200);
        sleep_status=false;
    }    
    readValues();

    // fTQuente.setValue(tempProb1*1);
    // fUmidade.setValue(hum_dht11*1);
    va0.setValue(3);
    water_status_func();
    page0.show();
   if (door_status){
        // txPorta.setText("Porta Fechada");
        txPorta.Set_background_color_bco(0x07F3);
        txPorta.Set_font_color_pco(0);
    }else{
        // txPorta.setText("Porta Aberta");
        txPorta.Set_background_color_bco(0xF0E3);
        txPorta.Set_font_color_pco(0x0000);
    }
    if (water_status){
        // txReser.setText("Reserv. OK");
        txReser.Set_background_color_bco(0x07F3);
        txReser.Set_font_color_pco(0);
    }else{
        // txReser.setText("Reserv. Cheio");
        txReser.Set_background_color_bco(0xF0E3);
        txReser.Set_font_color_pco(0x0000);
    }
}

void display_screensaver(){
    page1.show();
    
}

void display_sleep_on(){
    page1.show();
    delay(1500);
    Serial2.write("sleep=1");  //SLEEPING
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
}

void display_sleep(){
    Serial2.write("sleep=1");  //SLEEPING
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
    
    
}



