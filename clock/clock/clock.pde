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
long time_update;
byte time_day;

void setup()
{
  Serial.begin(9600);

  nes_init();
  segment_init();
  temp_init();
  rtc_init(&time);
  lcd_init();

  time_update = millis();
  time_day = 0;
}

void loop()
{
  serial_process(&time);

  //update time
  if (millis() - time_update > 1000)
  {
    time_update = millis();
    rtc_read(&time);
    temp = temp_read();
    segment_print_time(time.hour, time.minute);
    lcd_print_time(0, &time, temp);
    if (time_day != time.day)
    {
      lcd_print_date(1, &time);
      time_day = time.day;
    }
  }

  //buttons
  byte button = nes_read();

  if (button & NES_START)
    segment_on();

  //update segment fade
  segment_fade();

}
