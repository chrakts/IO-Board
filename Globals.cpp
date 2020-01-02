#define EXTERNALS_H_

#include "IO-Board.h"

const char *Node = "I1";


const char *fehler_text[]={"memory errors","parameter error","unknown job","no transmission","command not allowed","CRC error","no active sensor"};


char quelle_KNET[3]="E1";
uint8_t isBroadcast = false;


Communication cmulti(0,Node,1);

char Compilation_Date[] = __DATE__;
char Compilation_Time[] = __TIME__;


volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_START,RESTART_YES,50,0,LED_toggle}
};

double   MqttTime= 1111111111;
uint32_t secondsCounter = 1545264000;

char SecurityLevel = 0;

uint8_t outputPins[4] = {0b00011000,0b00100100,0b01000010,0b10000001};

