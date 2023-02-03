/**
Version: 0a
Tecnocoli - 02/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
Mega2560 - Dryer
**/
#include <Arduino.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Nextion.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "io_defines.h"
#include "defines.h" 
#include "buttons.h"
#include "digital_input.h"
#include "digital_output.h"
#include "analog_input.h"
#include "defines.h"
#include "display.h"
#include "program_0.h"
#include "program_1.h"
#include "program_2.h"
#include "program_3.h"

void hotspot1PopCallback(void *ptr);
void bStartPopCallback(void *ptr);
void program_cycle();
void choiceProgramCallBack(void *ptr);
void program_start();
void program_run();
void program_cycle_off();

NexPage page0 = NexPage(0, 0, "page0");
NexPage page1 = NexPage(1, 0, "page1");

NexHotspot hotspot1 = NexHotspot(1, 2, "hotspot1");

NexPicture pbkg1 = NexPicture(0,1, "pbkg1");
NexHotspot choice0 = NexHotspot(0, 2, "choice0");
NexVariable va0 = NexVariable(0, 3, "va0");
NexVariable va1 = NexVariable(0, 4, "va2");
NexVariable va2 = NexVariable(0, 5, "va2");

NexVariable r0 = NexVariable(0, 7, "r0");
NexVariable r1 = NexVariable(0, 8, "r1");
NexVariable r2 = NexVariable(0, 9, "r2");
NexVariable r3 = NexVariable(0, 10, "r3");

NexText txReser = NexText(0, 11, "txReser");
NexText txPorta = NexText(0, 12, "txPorta");

NexHotspot bStart = NexHotspot(0, 28, "bStart");
NexWaveform wave = NexWaveform(0, 29, "wave");
NexText txRun = NexText(0, 30, "txRun");
// NexNumber fTQuente = NexNumber(0, 19, "fTQuente");
// NexNumber fUmidade = NexNumber(0, 16, "fUmidade");






bool door_status = false;
bool water_status = false;
bool on_status = true;
bool start_status = false; 
bool alarm_status = false;
bool start_init = true;
bool sleep_status = false;
bool screensaver_status = false;
float tempProb1;
float tempProb2;
float hum_dht11;
float temp_dht11;

// program cycles
int prog_cycle = 0;
bool start_cycle = false;
unsigned long temp_max_p = TEMP_MAX;
unsigned long temp_p;
unsigned long time_0_p;
unsigned long time_1_p;
unsigned long time_2_p;
unsigned long time_3_p;
int hum_p;
float delta_hum;
float delta_1_hum;
float delta_1_temp;
float delta_2_temp;
float delta_3_temp;

unsigned long loopDelay = millis();
unsigned long loopDelay_readValue = millis();
unsigned long loopDelay_cycle = millis();
unsigned long loopDelay_toSleep = millis();
unsigned long loopDelay_toScreen = millis();
unsigned long loopDelay_wave = millis();

unsigned long time_door_open = millis();

unsigned long time_finish_p0 = millis();
unsigned long time_finish_p1 = millis();
unsigned long time_finish_p2 = millis();
unsigned long time_finish_p3 = millis();

unsigned long time_wait_hum_p0 = millis();
unsigned long time_wait_hum_p1 = millis();
unsigned long time_wait_hum_p2 = millis();
unsigned long time_wait_hum_p3 = millis();

NexTouch *nex_listen_list[] = {
    &hotspot1,
    &bStart,
    &r0,
    &r1,
    &r2,
    &r3,
    &choice0,
    NULL};

void setup()
{

  Serial.begin(115200);
  Serial.println("setup 1");
  nexInit();
  display_splachscreen();
  delay(2500); 
  // va0.setValue(3);

  Serial.println("setup 2");

  hotspot1.attachPush(hotspot1PopCallback, &hotspot1);
  bStart.attachPush(bStartPopCallback, &bStart);
  choice0.attachPush(choiceProgramCallBack, &choice0);

  buttons_begin();
  digital_input_begin();
  digital_output_begin();
  analog_input_begin();

  Serial.println("setup 3");

  pinMode(LED_PW, OUTPUT);
  pinMode(LED_AL, OUTPUT);
  pinMode(LED_RUN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_RUN, HIGH);

  door_status_func();
  water_status_func();

  if (alarm_status)
  {
    digitalWrite(LED_AL, LOW);
  }
  else
  {
    digitalWrite(LED_AL, HIGH);
  }

  
  
 
  start_init = false;
  display_on();
  Serial.println("setup finished");
  digitalWrite(LED_PW, LOW);
}


void loop()
{
  nexLoop(nex_listen_list);

  check_button();
  if (millis() - loopDelay > LOOPDELAY_TIME)
  {
    // Serial.println("LOOPDELAY_TIME");
    loopDelay = millis();
    door_status_func();
    water_status_func();
    if (alarm_status)
    {
      digitalWrite(LED_AL, LOW);
    }
    else
    {
      digitalWrite(LED_AL, HIGH);
    }
  }

  if (millis() - loopDelay_readValue > LOOPDELAY_READVALUE_TIME)
  {
    // Serial.println("LOOPDELAY_READVALUE_TIME");
    loopDelay = millis();
    loopDelay_readValue = millis();
    readValues();
    
    display_values();
  }

  if (millis() - loopDelay_wave > LOOPDELAY_WAVE_TIME)
  {

    wave.addValue(0, tempProb1);
    wave.addValue(1, hum_dht11);
    // wave.addValue(2, 3);
    // wave.addValue(3, 4);
    loopDelay_wave = millis();
    // Serial.println("LOOPDELAY_WAVE_TIME");
  }

  if (millis() - loopDelay_cycle > LOOPDELAY_CYCLE_TIME)
  {
    // Serial.println("LOOPDELAY_CYCLE_TIME");
    loopDelay_cycle = millis();
    program_cycle();
  }

  if ((millis() - loopDelay_toScreen) > LOOPDELAY_TOSCREEN_TIME)
  {
    loopDelay_toScreen = millis();
    if ((!water_status) && (!start_status)){
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
    
  }

  if ((millis() - loopDelay_toSleep) > LOOPDELAY_TOSLEEP_TIME)
  {
    loopDelay_toSleep = millis();
    if ((!door_status) && (!start_status)){
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
}

void program_cycle()
{
  if ((!start_cycle) && (start_status))
  {
    uint32_t c0;
    r0.getValue(&c0);
    uint32_t c1;
    r1.getValue(&c1);
    uint32_t c2;
    r2.getValue(&c2);
    uint32_t c3;
    r3.getValue(&c3);
    if (c0 == 1)
    {
      prog_cycle = 0;
    }
    else if (c1 == 1)
    {
      prog_cycle = 1;
    }
    else if (c2 == 1)
    {
      prog_cycle = 2;
    }
    else if (c3 == 1)
    {
      prog_cycle = 3;
    }
    else
    {
      prog_cycle = 5;
    }
    // Serial.print("program_cycle: ");
    // Serial.println(prog_cycle);
  }

  if ((!start_cycle) && (!alarm_status) && (start_status))
  {
    program_run();
  }
  if ((start_cycle) && (!alarm_status))
  {
    loopDelay_cycle = millis();
    program_start();
    loopDelay_cycle = millis();
  }
}

void program_cycle_off()
{
  switch (prog_cycle)
  {
  case 0:
    Serial.println("program 0");
    program_0_cycle_abort();
    break;
  case 1:
    Serial.println("program 1");
    program_1_cycle_abort();
    break;
  case 2:
    Serial.println("program 2");
    program_2_cycle_abort();
    break;
  case 3:
    Serial.println("program 3");
    program_3_cycle_abort();
    break;
  }
}

void program_start()
{
  switch (prog_cycle)
  {
  case 0:
    Serial.println("program 0");
    program_0_begin();
    break;
  case 1:
    Serial.println("program 1");
    program_1_begin();
    break;
  case 2:
    Serial.println("program 2");
    program_2_begin();
    break;
  case 3:
    Serial.println("program 3");
    program_3_begin();
    break;
  }
}

void program_run()
{
  switch (prog_cycle)
  {
  case 0:
    // Serial.println("program 0");
    program_0_cycle();
    break;
  case 1:
    // Serial.println("program 1");
    program_1_cycle();
    break;
  case 2:
    // Serial.println("program 2");
    program_2_cycle();
    break;
  case 3:
    // Serial.println("program 3");
    program_3_cycle();
    break;
  }
}

void hotspot1PopCallback(void *ptr)
{
  // Serial.println("hotspot1");
  on_status = true;
  // digitalWrite(LED_VD, HIGH);
  if (alarm_status)
  {
    digitalWrite(LED_AL, HIGH);
  }
  else
  {
    digitalWrite(LED_AL, LOW);
  }
  display_after_sleep();
  int melody1[] = {2551, 3551}; // notes in the melody
  int noteDurations[] = {8, 8};
  for (int thisNote = 0; thisNote < 2; thisNote++)
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody1[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
  screensaver_status = false;
  loopDelay_toSleep = millis();
  loopDelay_toScreen = millis();
}

void bStartPopCallback(void *ptr)
{
  Serial.println("bStart");
  uint32_t c0;
  r0.getValue(&c0);
  
  Serial.println(c0);
  uint32_t c1;
  r1.getValue(&c1);
  Serial.println(c1);
  uint32_t c2;
  r2.getValue(&c2);
  Serial.println(c2);
  uint32_t c3;
  r3.getValue(&c3);
  Serial.println(c3);
  if (c0 == 1)
  {
    prog_cycle = 0;
  }
  else if (c1 == 1)
  {
    prog_cycle = 1;
  }
  else if (c2 == 1)
  {
    prog_cycle = 2;
  }
  else if (c3 == 1)
  {
    prog_cycle = 3;
  }
  else
  {
    prog_cycle = 5;
  }
  // if ((on_status) && (!alarm_status) && (!start_cycle)){
  if ((on_status) && (!alarm_status))
    
  {
    Serial.println("on status");
    if (!start_status)
    {
      
      start_status = true;
      Serial.println("start status");
      Serial.println(prog_cycle);
      display_start();
      digitalWrite(LED_RUN, LOW);
      // digitalWrite(OULI2, LOW);
      start_cycle = true;
      va2.setValue(3);
      int melody1[] = {2551, 1908}; // notes in the melody
      int noteDurations[] = {12, 4};
      for (int thisNote = 0; thisNote < 2; thisNote++)
      {                                                    // ergodic all notes
        int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
        tone(BUZZER_PIN, melody1[thisNote], noteDuration); // let speaker sonds
        int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
        delay(pauseBetweenNotes);                          // delay for the while
        noTone(BUZZER_PIN);                                // stop the tone playing:
      }
    }
    else 
    {
      start_status = false;
      // Serial.println("off status");
      program_cycle_off();
      display_start_off();
      digitalWrite(LED_RUN, HIGH);
      // digitalWrite(OULI2, HIGH);
      va2.setValue(0);
      int melody1[] = {1908, 2551}; // notes in the melody
      int noteDurations[] = {12, 4};
      for (int thisNote = 0; thisNote < 2; thisNote++)
      {                                                    // ergodic all notes
        int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
        tone(BUZZER_PIN, melody1[thisNote], noteDuration); // let speaker sonds
        int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
        delay(pauseBetweenNotes);                          // delay for the while
        noTone(BUZZER_PIN);                                // stop the tone playing:
      }
    }
  }
  else if (alarm_status) 
  {
    if (on_status){
      start_status = false;
      // Serial.println("off status");
      program_cycle_off();
      display_start_off();
      digitalWrite(LED_RUN, HIGH);
      // digitalWrite(OULI2, HIGH);
      va2.setValue(0);
      int melody1[] = {1908, 2551}; // notes in the melody
      int noteDurations[] = {12, 4};
      for (int thisNote = 0; thisNote < 2; thisNote++)
      {                                                    // ergodic all notes
        int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
        tone(BUZZER_PIN, melody1[thisNote], noteDuration); // let speaker sonds
        int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
        delay(pauseBetweenNotes);                          // delay for the while
        noTone(BUZZER_PIN);                                // stop the tone playing:
      }

    }else{
      // Serial.println("off status");
      int melody1[] = {2000, 2551, 2000, 2551, 2000, 2551}; // notes in the melody
      int noteDurations[] = {8, 8, 8, 8, 8, 8};
      for (int thisNote = 0; thisNote < 6; thisNote++)
      {                                                    // ergodic all notes
        int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
        tone(BUZZER_PIN, melody1[thisNote], noteDuration); // let speaker sonds
        int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
        delay(pauseBetweenNotes);                          // delay for the while
        noTone(BUZZER_PIN);
      }
    }
  }

  loopDelay_toSleep = millis();
  loopDelay_toScreen = millis();
}

void choiceProgramCallBack(void *ptr)
{
  // Serial.println("bchoice");
  // uint32_t x;
  // r0.getValue(&x);
  // Serial.println(x);
  loopDelay_toSleep = millis();
  loopDelay_toScreen = millis();
}
