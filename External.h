#ifndef EXTERNAL_H_INCLUDED
#define EXTERNAL_H_INCLUDED

#include "Serial.h"
#include "MyTimer.h"
#include "myConstants.h"
#include "Communication.h"
#include "../communication/CRC_Calc.h"

extern char const *Node;
extern char quelle_KNET[3];

extern uint8_t isBroadcast;

extern const char *fehler_text[];



extern volatile TIMER MyTimers[MYTIMER_NUM];
extern char Compilation_Date[];
extern char Compilation_Time[];


extern Communication cmulti;
extern double MqttTime;
extern uint32_t secondsCounter;
extern char SecurityLevel;

extern CRC_Calc crcGlobal;


extern uint8_t outputPins[];
#endif // EXTERNAL_H_INCLUDED
