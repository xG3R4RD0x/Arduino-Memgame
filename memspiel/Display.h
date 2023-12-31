#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

class Display{

public:
      Display();
      int setup();
      void scoreDisplay(int highscore, int score);
      void showMathProblem();
      void redX();
      void checkmark();
      void countdown();
      int showInput(char input);
      void showMathgame(const char* mathgame);
      void deleteInput();
      void blackScreen();
      void gameOver();
};
#endif