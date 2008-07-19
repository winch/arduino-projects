
#include <Wire.h>
#include "nes.h"

// RTC
// SDA = analog 4
// SCL = analog 5
// address 104


void setup()
{
  Serial.begin(9600);
  
  nes_init();
}

void loop()
{
  //
}
