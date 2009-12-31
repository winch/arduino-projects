
#ifndef _NES_H
#define _NES_H

//buttons
#define NES_A 0x80
#define NES_B 0x40
#define NES_SELECT 0x20
#define NES_START 0x10
#define NES_UP 0x8
#define NES_DOWN 0x4
#define NES_LEFT 0x2
#define NES_RIGHT 0x1

extern "C"
{

  void nes_init();
  byte nes_read();

}

#endif

