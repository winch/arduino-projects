
#include "WConstants.h"

#define TEMP_DATA 8

static byte temp_reset();
static byte temp_read_byte();
static void temp_write_byte(byte);

void temp_init()
{
  pinMode(TEMP_DATA, INPUT);
  digitalWrite(TEMP_DATA, LOW);
}

int temp_read()
{
  if (!temp_reset())
    return -1;
  
  //skip rom
  temp_write_byte(0xcc);
  
  //convert t
  temp_write_byte(0x44);
  
  return 0;
}

static byte temp_read_byte()
{
  byte value = 0;
  return value;
}

static void temp_write_byte(byte value)
{
  int i;
  for (i = 0; i < 8; i++)
  {
    //value & 0x1
    //write bit
    value >>= 1;
  }
}

static byte temp_reset()
{
  pinMode(TEMP_DATA, OUTPUT);
  digitalWrite(TEMP_DATA, LOW);
  delayMicroseconds(500);
  pinMode(TEMP_DATA, INPUT);
  delayMicroseconds(60);
  if (digitalRead(TEMP_DATA) == LOW)
    return 1;
  else
    return 0;
}
