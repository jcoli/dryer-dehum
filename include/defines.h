/**
Version: 0a
Tecnocoli - 02/2022
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
Mega2560 - Dryer
**/

#ifndef __DEFINES_H__
#define __DEFINES_H__

//defines timers / loops 
#define LOOPDELAY_TIME 1000
#define LOOPDELAY_READVALUE_TIME 5000
#define LOOPDELAY_CYCLE_TIME 3000
#define LOOPDELAY_WAVE_TIME 30000
#define LOOPDELAY_TOSCREEN_TIME 30000
#define LOOPDELAY_TOSLEEP_TIME 10000
// #define LOOPDELAY_TOSCREEN_TIME 15000
// #define LOOPDELAY_TOSLEEP_TIME 15000


// defines cycles 

#define TEMP_MAX 60
#define TEMP_P0 39
#define TEMP_P1 39
#define TEMP_P2 39
#define TEMP_P3 39
#define TIME_P0_0 350000 //finish after hum
#define TIME_P0_1 350
#define TIME_P0_2 350
#define TIME_P0_3 120000 //door open
#define TIME_P1_0 48000
#define TIME_P1_1 480
#define TIME_P1_2 480
#define TIME_P1_3 120000 //door open
#define TIME_P2_0 60000
#define TIME_P2_1 600
#define TIME_P2_2 600
#define TIME_P2_3 120000 //door open
#define TIME_P3_0 60000
#define TIME_P3_1 600
#define TIME_P3_2 600
#define TIME_P3_3 120000 //door open
#define HUM_P0 30
#define HUM_P1 30
#define HUM_P2 30
#define HUM_P3 30
#define DELTA_HUM_P0 1.1
#define DELTA_HUM_P1 1.1
#define DELTA_HUM_P2 1.1
#define DELTA_HUM_P3 1.1
#define DELTA_1_HUM_P0 0.96
#define DELTA_1_HUM_P1 0.96
#define DELTA_1_HUM_P2 0.96
#define DELTA_1_HUM_P3 0.96
#define DELTA_1_TEMP_P0 1.01 // temp HH
#define DELTA_1_TEMP_P1 1.01 
#define DELTA_1_TEMP_P2 1.01 
#define DELTA_1_TEMP_P3 1.01
#define DELTA_2_TEMP_P0 1.01 // temp H
#define DELTA_2_TEMP_P1 1.01
#define DELTA_2_TEMP_P2 1.01
#define DELTA_2_TEMP_P3 1.01
#define DELTA_3_TEMP_P0 0.97 // temp L
#define DELTA_3_TEMP_P1 0.97
#define DELTA_3_TEMP_P2 0.97
#define DELTA_3_TEMP_P3 0.97




#endif
