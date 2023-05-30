#ifndef NUMPAD_H
#define NUMPAD_H

#include <Keypad.h>

class Numpad{
  public:
  Numpad();
  int setup();
  char getNumber();
};
#endif
