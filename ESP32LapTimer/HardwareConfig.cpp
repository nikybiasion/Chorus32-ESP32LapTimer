/////define Pins//////
#include "HardwareConfig.h"

#include <Arduino.h>

uint8_t CS_PINS[MAX_NUM_RECEIVERS] = {CS1, CS2, CS3, CS4, CS5, CS6};

void InitHardwarePins() {

  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  for(int i = 0; i < MAX_NUM_RECEIVERS; i++) {
    pinMode(CS_PINS[i], OUTPUT);
    digitalWrite(CS_PINS[i], HIGH);
  }
  //pinMode(MISO, INPUT);
  pinMode(BEEPER, OUTPUT);
  digitalWrite(BEEPER, LOW);
}
