
#include "WProgram.h"
#include "rtc.h"

static void serial_set_time(rtc_time*);
static void serial_print_time(rtc_time*);

void serial_process(rtc_time* time)
{
  if (Serial.available())
  {
    int request = Serial.read();
    switch (request)
    {
      case 'p':
        //print info
        serial_print_time(time);
        break;
      case 's':
        //set time
        serial_set_time(time);
        rtc_write(time);
        Serial.print("set ");
        serial_print_time(time);
        break;
    }
  }
}

static void serial_set_time(rtc_time* time)
{
  // YYMMDDWHHMMSSa/p
  int i;
  byte data;
  //read the 13 byte time string
  for (i = 0; i < 14; i++)
  {
    //wait for data to become availible if required
    while (!Serial.available())
      delayMicroseconds(10);
      
    //read data and convert from ascii
    data = Serial.read() - '0';
    
    switch (i)
    {
      case 0:
        //year tens
        time->year = 2000 + data * 10;
        break;
      case 1:
        //year units
        time->year += data;
        break;
      case 2:
        //month tens
        time->month = data * 10;
        break;
      case 3:
        //month units
        time->month += data;
        break;
      case 4:
        //day tens
        time->day = data * 10;
        break;
      case 5:
        //day units
        time->day += data;
        break;
      case 6:
        //week day
        time->w_day = data;
        break;
      case 7:
        //hour tens
        time->hour = data * 10;
        break;
      case 8:
        //hour units
        time->hour += data;
        break;
      case 9:
        //minute tens
        time->minute = data * 10;
        break;
      case 10:
        //minute units
        time->minute += data;
        break;
      case 11:
        //second tens
        time->second = data * 10;
        break;
      case 12:
        //second units
        time->second += data;
        break;
      case 13:
        //am/pm
        //convert data back to ascii
        //read data and convert from ascii
        data += '0';
        time->period = data;
        break; 
    }
  }
}

static void serial_print_time(rtc_time* time)
{
  Serial.print(time->year, DEC);
  Serial.print("-");
  Serial.print(time->month, DEC);
  Serial.print("-");
  Serial.print(time->day, DEC);
  Serial.print(" ");
  Serial.print(time->w_day, DEC);
  Serial.print(" ");
  Serial.print(time->hour, DEC);
  Serial.print(":");
  Serial.print(time->minute, DEC);
  Serial.print(":");
  Serial.print(time->second, DEC);
  if (time->period == 'a')
    Serial.println(" am");
  else
    Serial.println(" pm");
}

