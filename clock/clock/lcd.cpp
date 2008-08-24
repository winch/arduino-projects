#include <LCD4Bit.h>
#include <stdio.h>
#include "WConstants.h"
#include "rtc.h"

#define LINES 2
#define LINE_WIDTH 16

static LCD4Bit lcd = LCD4Bit(LINES);
static char lcd_line[LINE_WIDTH + 1];
static char blank_line[] = "                ";

void lcd_print(byte, char);

void lcd_init()
{
  lcd.init();
  lcd.clear();
}

// writes msg to required line
void lcd_print(byte line, char *msg)
{
  byte i;
  lcd.cursorTo(line + 1, 0);
  lcd.printIn(msg);
}

void lcd_print_time(byte line, rtc_time *time)
{
  snprintf(lcd_line, LINE_WIDTH, "%.2d:%.2d:%.2d%s%s", time->hour, time->minute, time->second, rtc_period[time->period], blank_line);
  lcd_print(line, lcd_line);
}

void lcd_print_date(byte line, rtc_time *time)
{
  snprintf(lcd_line, LINE_WIDTH, "%s %.2d-%.2d-%d%s", rtc_days[time->w_day], time->day, time->month, time->year, blank_line);
  lcd_print(line, lcd_line);
}
