
#ifndef _RTC_H
#define _RTC_H

struct rtc_time
{
  byte second;
  byte minute;
  byte hour;
  byte w_day;
  byte day;
  byte month;
  int year;
};

void rtc_init(rtc_time*);

void rtc_read(rtc_time*);

#endif



