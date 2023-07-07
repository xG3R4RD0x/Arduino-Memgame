#ifndef LEDGAME_H
#define LEDGAME_H
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <random>

class LEDGame{
  public:
    LEDGame();
    void start();
    void game_over();
    std::vector<int> generateSequence(int size);
    void turn_on_random_sequence(std::vector<int> rdmnSequence);
    int button_loop();
    std::vector<int> initRound(int size);
    bool playRound(std::vector<int> LEDarray);
    void Ledtester();
  private:
    int randomNum();
    uint32_t xorshift32();
    const char* stringToConstChar(const String& str);

};

#endif