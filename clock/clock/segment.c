
#include "WConstants.h"

#define SEGMENT_LATCH 8
#define SEGMENT_CLOCK 9
#define SEGMENT_DATA 10

//characters
#define SEGMENT_POINT 0x20
#define SEGMENT_DASH 0x8

static byte segment_digits[] = {
  0xd7, // 0
  0x14, // 1
  0xcd, // 2
  0x5d, // 3
  0x1e, // 4
  0x5b, // 5
  0xdb, // 6
  0x15, // 7
  0xdf, // 8
  0x5f, // 9
};

void segment_init()
{
  pinMode(SEGMENT_LATCH, OUTPUT);
  digitalWrite(SEGMENT_LATCH, HIGH);
  pinMode(SEGMENT_CLOCK, OUTPUT);
  pinMode(SEGMENT_DATA, OUTPUT);
}

void segment_update(byte a, byte b, byte c, byte d)
{
  int digit;
  
  digitalWrite(SEGMENT_CLOCK, LOW);
  digitalWrite(SEGMENT_LATCH, LOW);
  delayMicroseconds(1);
  
  segment_write(segment_digits[d]);
  segment_write(segment_digits[c]);
  segment_write(segment_digits[b] | SEGMENT_POINT);
  segment_write(segment_digits[a]);
  
  digitalWrite(SEGMENT_CLOCK, LOW);
  digitalWrite(SEGMENT_LATCH, HIGH);
}

// write a byte 
void segment_write(byte value)
{
  int bit;
  for (bit = 0; bit < 8; bit++)
  {
    digitalWrite(SEGMENT_CLOCK, LOW);
    delayMicroseconds(1);
    digitalWrite(SEGMENT_DATA, value & 0x1);
    value >>= 1;
    delayMicroseconds(1);
    digitalWrite(SEGMENT_CLOCK, HIGH);
    delayMicroseconds(1);
  }
}
