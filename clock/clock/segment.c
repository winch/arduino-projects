
#include "WConstants.h"

#define SEGMENT_ENABLE 9
#define SEGMENT_LATCH 10
//clock and data line are shared with nes controller
#define SEGMENT_CLOCK 12
#define SEGMENT_DATA 13

#define FADE_DELAY 20
#define ON_DURATION 4000

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

static byte status;
static byte fade;
static byte fade_diff;
static long last_update;

static void segment_write_byte(byte);
static void segment_write(byte, byte, byte, byte);

void segment_init()
{
  pinMode(SEGMENT_LATCH, OUTPUT);
  digitalWrite(SEGMENT_LATCH, HIGH);
  pinMode(SEGMENT_CLOCK, OUTPUT);
  pinMode(SEGMENT_ENABLE, OUTPUT);
  analogWrite(SEGMENT_ENABLE, 255);
  status = 0;
  last_update = millis();
}

void segment_on()
{
  if (status == 0)
  {
    //turn on
    status = 1;
    fade = 255;
    fade_diff = -3;
    last_update = millis();
  }
}

void segment_fade()
{
  if (status == 0)
    return;
    
  if (fade_diff == 0)
  {
    //wait for on duration
    if (millis() - last_update > ON_DURATION)
    {
      fade_diff = 3;
      last_update = millis();
    }
  }
  else
  {
    if (millis() - last_update > FADE_DELAY)
    {
      fade += fade_diff;
      analogWrite(SEGMENT_ENABLE, fade);
    
      if (fade == 0)
        fade_diff = 0;
    
      if (fade == 255)
        status = 0;
      last_update = millis();
    }
  }
}

//write time to display in hh.mm format
void segment_print_time(byte hour, byte minute)
{
  byte hour_ten, hour_unit, minute_ten, minute_unit;
  byte a, b, c, d;
  hour_ten = hour / 10;
  hour_unit = hour - hour_ten * 10;
  
  minute_ten = minute / 10;
  minute_unit = minute - minute_ten * 10;
  
  // leave leading zero blank
  if (hour_ten == 0)
    a = 0;
  else
    a = segment_digits[hour_ten];
  b = segment_digits[hour_unit] | SEGMENT_POINT;
  c = segment_digits[minute_ten];
  d = segment_digits[minute_unit];
  
  segment_write(a, b, c, d);
}

//write byte values to display
static void segment_write(byte a, byte b, byte c, byte d)
{
  int digit;
  
  pinMode(SEGMENT_DATA, OUTPUT);
  
  digitalWrite(SEGMENT_CLOCK, LOW);
  digitalWrite(SEGMENT_LATCH, LOW);
  delayMicroseconds(1);
  
  segment_write_byte(d);
  segment_write_byte(c);
  segment_write_byte(b);
  segment_write_byte(a);
  
  digitalWrite(SEGMENT_CLOCK, LOW);
  digitalWrite(SEGMENT_LATCH, HIGH);
}

// write a byte 
static void segment_write_byte(byte value)
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
