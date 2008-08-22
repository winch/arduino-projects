#include <Wire.h>
#include "nes.h"
#include "rtc.h"
#include "serial.h"
#include "segment.h"
#include "temp.h"

struct rtc_time time;
long time_update;

void setup()
{
  Serial.begin(9600);
  
  nes_init();
  segment_init();
  temp_init();
  rtc_init(&time);
  
  time_update = millis();
}

void loop()
{
  serial_process(&time);
  
  //update time
  if (millis() - time_update > 1000)
  {
    rtc_read(&time);
    segment_print_time(time.hour, time.minute);
    time_update = millis();
  }
  
  //buttons
  byte button = nes_read();
  
  if (button & NES_START)
    segment_on();
  
  //update segment fade
  segment_fade();
  
}
