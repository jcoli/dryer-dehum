/**
Version: 0a
Tecnocoli - 02/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
Mega2560 - Dryer
**/
#include <Arduino.h>
#include "io_defines.h"
#include "defines.h"

void digital_output_begin();


void digital_output_begin(){
    pinMode(OUPS1, OUTPUT);
    pinMode(OUPT1, OUTPUT);
    pinMode(OUPT2, OUTPUT);
    pinMode(OUHT1, OUTPUT);
    pinMode(OULI3, OUTPUT);
    pinMode(OUCL1, OUTPUT);
    pinMode(OUCL2, OUTPUT);
    pinMode(OUCL3, OUTPUT);
    pinMode(OULI1, OUTPUT);
    pinMode(OULI2, OUTPUT);
    digitalWrite(OUPS1, LOW);
    digitalWrite(OUPT1, LOW);
    digitalWrite(OUPT2, LOW);
    digitalWrite(OUHT1, LOW);
    digitalWrite(OUCL1, LOW);
    digitalWrite(OUCL2, LOW);
    digitalWrite(OUCL3, LOW);
    digitalWrite(OULI1, LOW);
    digitalWrite(OULI2, LOW);
    digitalWrite(OULI3, LOW);
    //
    // digitalWrite(OUPS1, HIGH);
    // digitalWrite(OUPT1, HIGH);
    // // // digitalWrite(OUPT2, HIGH);
    //  digitalWrite(OUHT1, HIGH);
    // digitalWrite(OUCL1, HIGH);
    // // digitalWrite(OUCL2, HIGH);
    // digitalWrite(OUCL3, HIGH);
    // digitalWrite(OULI1, HIGH);
    // digitalWrite(OULI2, HIGH);
    // digitalWrite(OULI3, HIGH);
    // delay(500000);
    
 
}