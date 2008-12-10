
#ifndef _TEMP_H
#define _TEMP_H

struct temp_value
{
  int temp;
  byte point;
};

void temp_init();
void temp_convert();
temp_value temp_read();

#endif
