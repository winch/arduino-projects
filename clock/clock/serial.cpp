
#include "WProgram.h"
#include "rtc.h"

//struct rtc_time time;

void serial_process()
{
  if (Serial.available())
  {
    int request = Serial.read();
    switch (request)
    {
      case 'p':
        //ping
        Serial.println("pong, this is a clock.");
        break;
      case 't':
        //print time
        break;
    }
  }
}

