#include <OneWire.h>
#include <LCD4Bit.h>
#include <Wire.h>
#include "nes.h"
#include "rtc.h"
#include "serial.h"
#include "segment.h"
#include "temp.h"
#include "lcd.h"

struct rtc_time time;
struct temp_value temp;
byte temp_cycle; //convert or read temp?
long time_update;
#define TIME_DELAY 1000
long nes_update;
#define NES_DELAY 30
byte time_day;


void setup()
{
  Serial.begin(9600);

  nes_init();
  segment_init();
  temp_init();
  rtc_init(&time);
  lcd_init();

  temp_cycle = 0;
  temp.temp = 0;
  temp.point = 0;
  time_update = millis();
  time_day = 0;
  nes_update = time_update;
}

void loop()
{
  serial_process(&time);

  //update time
  if (millis() - time_update > TIME_DELAY)
  {
    time_update = millis();
    rtc_read(&time);
    if (temp_cycle == 0)
    {
      temp_convert();
      temp_cycle = 1;
    }
    else
    {
      temp = temp_read();
      temp_cycle = 0;
    }
    segment_print_time(time.hour, time.minute);
    lcd_print_time(0, &time, temp);
    if (time_day != time.day)
    {
      lcd_print_date(1, &time);
      time_day = time.day;
    }
  }

  //buttons
  if (millis() - nes_update > NES_DELAY)
  {
    byte button = nes_read();

    if (button & NES_START)
      segment_on();
      
    nes_update = millis();
  }

  //update segment fade
  segment_fade();

}
