
#include "WConstants.h"

#define SEGMENT_LATCH 8
#define SEGMENT_CLOCK 9
#define SEGMENT_DATA 10

void segment_init()
{
  pinMode(SEGMENT_LATCH, OUTPUT);
  digitalWrite(SEGMENT_LATCH, HIGH);
  pinMode(SEGMENT_CLOCK, OUTPUT);
  pinMode(SEGMENT_DATA, OUTPUT);
}

void segment_update(int pos)
{
  int b, s;
  digitalWrite(SEGMENT_CLOCK, LOW);
  digitalWrite(SEGMENT_LATCH, LOW);
  delayMicroseconds(1);
  
  for (s = 0; s < 4; s++)
  {
    for (b = 0; b < 8; b++)
    {
      digitalWrite(SEGMENT_CLOCK, LOW);
      delayMicroseconds(1);
      if (b <= pos)
        digitalWrite(SEGMENT_DATA, HIGH);
      else
        digitalWrite(SEGMENT_DATA, LOW);
      delayMicroseconds(1);
      digitalWrite(SEGMENT_CLOCK, HIGH);
      delayMicroseconds(1);
      
    }
  }
  
  digitalWrite(SEGMENT_CLOCK, LOW);
  digitalWrite(SEGMENT_LATCH, HIGH);
}
