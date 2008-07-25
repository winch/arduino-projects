
#include <Wire.h>
#include "WConstants.h"
#include "rtc.h"

//address 104

void rtc_init(rtc_time *time)
{
  Wire.begin();
  time->year = 2000;
  time->month = 0;
  time->day = 0;
  time->second = 0;
  time->minute = 0;
  time->hour = 0;
  time->w_day = 0;
}

// read time into rtc_time struct
void rtc_read(rtc_time *time)
{
  int address = 0;
  Wire.beginTransmission(104);
  Wire.send(address);
  Wire.endTransmission();
  Wire.requestFrom(104, 7);
  while(Wire.available())
  {
    byte b = Wire.receive();
    switch (address)
    {
      case 0:
        //seconds
        time->second = ((b & 0x70) >> 4) * 10;
        time->second += b & 0x0f;
        break;
      case 1:
        //minutes
        time->minute = (b >> 4) * 10;
        time->minute += b & 0x0f;
        break;
      case 2:
        //hours
        time->hour = ((b & 0x30) >> 4) * 10;
        time->hour += b & 0x0f;
        break;
      case 3:
        //week day
        time->w_day = b;
        break;
      case 4:
        //day
        time->day = (b >> 4) * 10;
        time->day += b & 0x0f;
        break;
      case 5:
        //month
        time->month = (b >> 4) * 10;
        time->month += b & 0x0f;
        break;
      case 6:
        //year
        time->year = 2000;
        time->year += (b >> 4) * 10;
        time->year += b & 0x0f;
        break;
    }
    address ++;
  }
}

// write the time in rtc_time struct to rtc
void rtc_write(rtc_time *time)
{
  Wire.beginTransmission(104);
  Wire.send((byte) 6);
  Wire.send(8);
  Wire.endTransmission();
}