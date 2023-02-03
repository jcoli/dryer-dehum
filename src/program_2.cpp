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
#include "analog_input.h"
#include "display.h"
#include "program_0.h"

void program_2_begin();
void program_2_cycle();
void program_2_cycle_abort();
void program_2_cycle_close();

extern NexHotspot bStart;

extern NexText txPorta;
extern NexText txReser;
// extern NexNumber fTQuente;
// extern NexNumber fUmidade;
extern NexPage page0;
extern NexPage page1;
extern NexVariable va0;
extern NexVariable r0;
extern NexVariable r1;
extern NexVariable r2;
extern NexVariable r3;
extern NexPicture pbkg1;

extern bool door_status;
extern bool water_status;
extern bool on_status;
extern bool start_status;
extern bool alarm_status;
extern bool start_init;
extern bool sleep_status;
extern bool screensaver_status;
extern float tempProb1;
extern float tempProb2;
extern float hum_dht11;
extern float temp_dht11;
extern int prog_cycle;
extern bool start_cycle;


extern int temp_max_p;
extern unsigned long temp_p;
extern unsigned long time_0_p;
extern unsigned long time_1_p;
extern unsigned long time_2_p;
extern unsigned long time_3_p;
extern int hum_p;
extern float delta_1_hum;
extern float delta_hum;
extern float delta_1_temp;
extern float delta_2_temp;
extern float delta_3_temp;

extern unsigned long time_door_open;

extern unsigned long time_finish_p2;
extern unsigned long time_wait_hum_p2;


void program_2_begin(){
    // Serial.println("program_2_begin");
    if (start_cycle){
        // Serial.println("program_2_begin - start_cycle");
        temp_p = TEMP_P2;
        time_0_p = TIME_P2_0;
        time_1_p = TIME_P2_1;
        time_2_p = TIME_P2_2;
        time_3_p = TIME_P2_3;
        hum_p = HUM_P2;
        delta_hum = DELTA_HUM_P2;
        delta_1_hum = DELTA_1_HUM_P2;
        delta_1_temp = DELTA_1_TEMP_P2;
        delta_2_temp = DELTA_2_TEMP_P2;
        delta_3_temp = DELTA_3_TEMP_P2;
        
        time_door_open = TIME_P2_3;
        digitalWrite(OUPS1,HIGH);
        delay(300);
        digitalWrite(OUHT1, HIGH);
        delay(300);
        // //digitalWrite(OUHT2, HIGH);
        // delay(1000);
        digitalWrite(OUCL1, HIGH);
        delay(300);
        digitalWrite(OUPT1, HIGH);
        delay(300);
        digitalWrite(OULI2, HIGH);
        start_cycle = false;
    }


}

void program_2_cycle(){
    // Serial.println("program_0_cycle");
    readValues();

    //Humidity - Peltier -- cooler
    if(tempProb1>(temp_p)){ 
        // Serial.print("hum: ");
        // Serial.println(hum_dht11);
        if(hum_dht11<(hum_p*delta_1_hum)){
            // Serial.println("hum_dht11<hum_p");
            if ((millis() - time_wait_hum_p2) > TIME_P0_0){
                r1.setValue(0);
                r2.setValue(0);
                r3.setValue(0);
                r0.setValue(1);
                pbkg1.setPic(5);
                program_2_cycle_abort();
                prog_cycle = 0;
                start_cycle = true;
                display_start();
                program_0_begin();
                program_0_cycle();
            }
           
              
        }else if(hum_dht11>(hum_p*delta_hum)){
            // Serial.println("hum_dht11>(hum_p*delta_hum)");
              
            time_finish_p2 = millis();
            time_wait_hum_p2 = millis();
            digitalWrite(OUPT1, HIGH);
            digitalWrite(LED_PT, HIGH);
            digitalWrite(OUCL1, HIGH);
            
        }else if((hum_dht11>(hum_p)) && (hum_dht11<(hum_p*delta_hum))){
            // Serial.println("hum_dht11>=(hum_p");
                
            digitalWrite(OUPT1, HIGH);
            digitalWrite(LED_PT, HIGH);
            digitalWrite(OUCL1, HIGH);
            time_finish_p2 = millis();
            time_wait_hum_p2 = millis();
        }else{
            // Serial.println("else hum");
               
            digitalWrite(OUPT1, LOW);
            digitalWrite(LED_PT, LOW);
            digitalWrite(OUCL1, HIGH);
            time_finish_p2 = millis();
            time_wait_hum_p2 = millis();
        }
    }else{
        // Serial.println("else hum");
        time_finish_p2 = millis();
        time_wait_hum_p2 = millis();
    }    

    //Temperature - Heater
    if(tempProb1>(temp_p*delta_1_temp)){    
        // Serial.println("TempProb1>TEMP_P0*delta_1_temp)");
        digitalWrite(OUHT1, LOW);
        digitalWrite(LED_HT, LOW);
    
    }else if(tempProb1<(temp_p*delta_3_temp)){
        // Serial.println("else temp");
        digitalWrite(OUHT1,HIGH);
        digitalWrite(LED_HT, HIGH);
        // digitalWrite(OUHT2, LOW);
    }
    if (door_status){
        // Serial.println("!door_status");
        time_door_open = millis();
    }
    if ((millis()-time_door_open) > time_3_p){
        // Serial.println("(time_door_open)>millis()");
        program_2_cycle_abort();
    }
}

void program_2_cycle_abort(){
    digitalWrite(OUPS1,LOW);
    digitalWrite(OUPT1, LOW);
    digitalWrite(OUPT2, LOW);
    digitalWrite(OUHT1, LOW);
    digitalWrite(LED_HT, LOW);
    digitalWrite(LED_PT, LOW);
    digitalWrite(OUCL1, LOW);
    digitalWrite(OUCL2, LOW);
    digitalWrite(OUCL3, LOW);
    digitalWrite(OULI2, LOW);
    display_start_off();
}

void program_2_cycle_close(){
    digitalWrite(OUPS1,LOW);
    digitalWrite(OUPT1, LOW);
    digitalWrite(OUPT2, LOW);
    digitalWrite(OUHT1, LOW);
    digitalWrite(LED_HT, LOW);
    digitalWrite(LED_PT, LOW);
    digitalWrite(OUCL1, LOW);
    digitalWrite(OUCL2, LOW);
    digitalWrite(OUCL3, LOW);
    digitalWrite(OULI2, LOW);
    display_start_off();
}
