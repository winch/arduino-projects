
#include <Wire.h>
#include "WProgram.h"
//#include "WConstants.h"
#include "rtc.h"

// address 104
// SDA = analog 4
// SCL = analog 5

char rtc_days[][4] = {
  "Sun",
  "Mon",
  "Tue",
  "Wed",
  "Thu",
  "Fri",
  "Sat",
};

char rtc_period[][3] = {
  "am",
  "pm"  
};

static byte rtc_byte_to_bcd(byte value);

void rtc_init(rtc_time *time)
{
  Wire.begin();
  time->year = 2000;
  time->month = 0;
  time->day = 0;
  time->second = 0;
  time->minute = 0;
  time->hour = 0;
  time->period = 0;
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
        time->hour = ((b & 0x10) >> 4) * 10;
        time->hour += b & 0x0f;
        //period high = pm
        time->period = b & 0x20;
        break;
      case 3:
        //week day
        time->w_day = b - 1;
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
  byte data;
  Wire.beginTransmission(104);
  Wire.send((byte) 0);
  //seconds
  data = rtc_byte_to_bcd(time->second);
  data &= 0x7f; //clear clock halt bit
  Wire.send(data);
  //minutes
  Wire.send(rtc_byte_to_bcd(time->minute));
  //hours
  data = rtc_byte_to_bcd(time->hour);
  if (time->period == 0)
    data &= 0xdf; //clear am/pm bit to am
  else
    data |= 0x20; //set am/pm bit to pm
  data |= 0x40; //set 12h bit
  Wire.send(data);
  //w_day
  Wire.send(rtc_byte_to_bcd(time->w_day + 1));
  //day
  Wire.send(rtc_byte_to_bcd(time->day));
  //month
  Wire.send(rtc_byte_to_bcd(time->month));
  //year
  Wire.send(rtc_byte_to_bcd(time->year - 2000));
  Wire.endTransmission();
}

static byte rtc_byte_to_bcd(byte value)
{
  byte bcd;
  bcd = (value / 10) << 4;
  bcd |= (value - (value / 10) * 10) & 0xf;
  return bcd;
}
