#include <Wire.h>
#include "nes.h"
#include "rtc.h"
#include "serial.h"
#include "segment.h"

// RTC
// SDA = analog 4
// SCL = analog 5

struct rtc_time time;

int pos = 0;

void setup()
{
  Serial.begin(9600);
  
  nes_init();
  segment_init();
  rtc_init(&time);
  
}

void loop()
{
  serial_process();
  
  segment_update(pos);
  pos++;
  
  if (pos > 8)
    pos = 0;
  
  delay(2000);
  
}
