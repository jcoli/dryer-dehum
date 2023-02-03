/**
Version: 0a
Tecnocoli - 02/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
Mega2560 - Dryer
**/
#include <Arduino.h>
#include <Nextion.h>
#include <Bounce2.h>
#include "io_defines.h"
#include "defines.h"
#include "digital_input.h"
#include "digital_output.h"
#include "analog_input.h"
#include "display.h"


void buttons_begin();
void check_button();
void callBackbuuton0();
void callBackbuuton1();
void callBackbuuton2();
void callBackbuuton3();
void callBackbuuton4();
void callBackbuuton5();

// extern NexButton bOn;
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


#define NUM_BUTTONS 4
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {BT0,BT1,BT2,BT3};
Bounce * buttons = new Bounce[NUM_BUTTONS];

void buttons_begin(){
    for (int i = 0; i < NUM_BUTTONS; i++) {
      buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
      buttons[i].interval(20);              // interval in ms
    }

}

void check_button(){
    for (int i = 0; i < NUM_BUTTONS; i++)  {
    buttons[i].update();
        if ( buttons[i].fell() ) {
            switch (i) {
                case 0:
                    Serial.println("button0");
                    callBackbuuton0();
                    break;
                case 1:
                    Serial.println("button1");
                    callBackbuuton1();
                    break;
                case 2:
                    Serial.println("button2");
                    callBackbuuton2();
                    break;
                case 3:
                    Serial.println("button3");
                    callBackbuuton3();
                    break;
                // case 4:
                //     Serial.println("button4");
                //     callBackbuuton4();
                //     break;
                // case 5:
                //     Serial.println("button5");
                //     callBackbuuton5();
                //     break;        
               
            }    
        }
    }   

}

void callBackbuuton0(){
        on_status = !on_status;
        if (on_status){
            display_on();
            
            if (alarm_status){
                    digitalWrite(LED_AL, HIGH);
            }else{
                    digitalWrite(LED_AL, LOW);
            }
            sleep_status=false;
            screensaver_status = false;
            loopDelay_toSleep = millis();
            loopDelay_toScreen = millis();
        }
        else{
            
        }
        // int melody[] = { 3200, 2200};  // notes in the melody
        int melody1[] = { 2551, 1908};  // notes in the melody
        int noteDurations[] = { 8, 8}; 
        for (int thisNote = 0; thisNote < 2; thisNote++) {   // ergodic all notes
                int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
                tone(BUZZER_PIN, melody1[thisNote], noteDuration);   // let speaker sonds
                int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
                delay(pauseBetweenNotes);                          // delay for the while
                noTone(BUZZER_PIN);                                 // stop the tone playing:
            }
    
}

void callBackbuuton1(){
    if ((on_status) && !(alarm_status)){
      start_status = !start_status;
      if (start_status){
        digitalWrite(LED_RUN, LOW);  
      }else{
        digitalWrite(LED_RUN, HIGH);
      }
      
      // int melody[] = { 3200, 2200};  // notes in the melody
      int melody1[] = { 2551, 1908};  // notes in the melody
      int noteDurations[] = { 8, 8}; 
      for (int thisNote = 0; thisNote < 2; thisNote++) {   // ergodic all notes
              int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
              tone(BUZZER_PIN, melody1[thisNote], noteDuration);   // let speaker sonds
              int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
              delay(pauseBetweenNotes);                          // delay for the while
              noTone(BUZZER_PIN);                                 // stop the tone playing:
      }
  }  


}

void callBackbuuton2(){
    Serial2.write("sleep=0");  //SLEEPING
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
    
}

void callBackbuuton3(){
    Serial2.write("sleep=1");  //SLEEPING
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);

    
}

void callBackbuuton4(){
    
    
}

void callBackbuuton5(){
    
}


