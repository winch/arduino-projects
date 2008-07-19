#include <Wire.h>
#include "nes.h"
#include "rtc.h"

// RTC
// SDA = analog 4
// SCL = analog 5

struct rtc_time time;

void setup()
{
  Serial.begin(9600);
  
  nes_init();
  rtc_init(&time);
}

void loop()
{
  byte b = nes_button_read();
  
  if (b & NES_START)
  {
    rtc_read(&time);
    Serial.print(time.year);
    Serial.print("-");
    Serial.print(time.month, DEC);
    Serial.print("-");
    Serial.print(time.day, DEC);
    Serial.print(" ");
    Serial.print(time.w_day, DEC);
    Serial.print(" ");
    Serial.print(time.hour, DEC);
    Serial.print(":");
    Serial.print(time.minute, DEC);
    Serial.print(":");
    Serial.println(time.second,DEC);
  }
  
  delay(1000);
}
