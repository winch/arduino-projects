
#include "WConstants.h"

#define NES_LATCH 6
#define NES_CLOCK 5
#define NES_DATA 4

void nes_init()
{
  pinMode(NES_LATCH, OUTPUT);
  pinMode(NES_CLOCK, OUTPUT);
  pinMode(NES_DATA, INPUT);
}

byte nes_button_read()
{
  int i;
  byte value = 0;

  //latch
  digitalWrite(NES_LATCH, HIGH);
  delayMicroseconds(1);
  digitalWrite(NES_LATCH, LOW);
  delayMicroseconds(1);
  
  //data
  for (i = 0; i < 8; i++)
  {
    value = (value << 1) + digitalRead(NES_DATA);  
    //clock
    digitalWrite(NES_CLOCK, HIGH);
    delayMicroseconds(1);
    digitalWrite(NES_CLOCK, LOW);
    delayMicroseconds(1);
  }
  
  return ~value;
}


