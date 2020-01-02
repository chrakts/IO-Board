#ifndef HX711ADAPTER_H_INCLUDED
#define HX711ADAPTER_H_INCLUDED


#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "myConstants.h"

#include "Serial.h"
#include "External.h"
#include "MyTimer.h"
#include "Communication.h"
#include "../xmegaClocks/xmegaClocks.h"
#include "ComReceiver.h"


void setup();
bool setOutputStatus(uint8_t bit, uint8_t status);
bool getInputStatus(uint8_t bit, uint8_t *status);
uint8_t reverseBits(uint8_t n);

#endif // HX711ADAPTER_H_INCLUDED
