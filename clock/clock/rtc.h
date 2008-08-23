
#ifndef _RTC_H
#define _RTC_H

struct rtc_time
{
  byte second;
  byte minute;
  byte hour;
  byte period;
  byte w_day;
  byte day;
  byte month;
  int year;
};

extern char rtc_days[][4];
extern char rtc_period[][3];

void rtc_init(rtc_time*);

void rtc_read(rtc_time*);

void rtc_write(rtc_time*);

#endif



