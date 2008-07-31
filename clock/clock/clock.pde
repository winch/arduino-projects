#include <Wire.h>
#include "nes.h"
#include "rtc.h"
#include "serial.h"
#include "segment.h"
#include "temp.h"

// RTC
// SDA = analog 4
// SCL = analog 5

struct rtc_time time;
long last_update;

void setup()
{
  Serial.begin(9600);
  
  nes_init();
  segment_init();
  temp_init();
  rtc_init(&time);
  
  last_update = millis();
}

void loop()
{
  serial_process(&time);
  
  if (millis() - last_update > 1000)
  {
    rtc_read(&time);
  
    int hour_ten, hour_unit, min_ten, min_unit;
    hour_ten = time.hour / 10;
    hour_unit = time.hour - 10 * hour_ten;
    min_ten = time.minute / 10;
    min_unit = time.minute - 10 * min_ten;
  
    segment_update(hour_ten, hour_unit, min_ten, min_unit);
    last_update = millis();
  }  
  //Serial.println(nes_read(), BIN);
  //Serial.println(temp_read());
  
}
