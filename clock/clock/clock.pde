#include <Wire.h>
#include "nes.h"
#include "rtc.h"
#include "serial.h"
#include "segment.h"

// RTC
// SDA = analog 4
// SCL = analog 5

struct rtc_time time;

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
  
  rtc_read(&time);
  
  int hour_ten, hour_unit, min_ten, min_unit;
  hour_ten = time.hour / 10;
  hour_unit = time.hour - 10 * hour_ten;
  min_ten = time.minute / 10;
  min_unit = time.minute - 10 * min_ten;
  
  segment_update(hour_ten, hour_unit, min_ten, min_unit);
  
  delay(60000);
  
}
