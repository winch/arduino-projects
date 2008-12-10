#include <OneWire.h>
#include "WProgram.h"
#include "temp.h"

#define TEMP_DATA 8

OneWire ds(TEMP_DATA);

void temp_init()
{
  //
}

void temp_convert()
{
  //start conversion
  ds.reset();
  ds.skip();
  ds.write(0x44);
  // delay(750) before conversion is finished
}

temp_value temp_read()
{
  byte high, low;
  temp_value temp;
  
  //read result
  ds.reset();
  ds.skip();
  ds.write(0xbe);
  
  low = ds.read();
  high = ds.read();

  temp.temp = low >> 1;
  temp.point = (low & 0x1) * 5;

  //check for negative temps
  if (!(high | 0x1))
    temp.temp *= -1;  
  
  return temp;
}
