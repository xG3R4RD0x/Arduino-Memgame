#include <iostream>
#include "Button.h"
#include "LED.h"
#include "LEDGame.h"
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <random>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include "Display.h"
#include "MathQuizzer.h"
#include "Numpad.h"


LED LED1(PC3);
LED LED2(PC2);
LED LED3(A5);
LED LED4(A4);
LED TimerLED(A3);
LED GreenLED(A2);
LED RedLED(A1);
std::vector<LED> ledArray = { LED1, LED2, LED3, LED4 };
Button Button1(PC10);
Button Button2(A0);
Button Button3(PC12);
Button Button4(PC11);
Button startButton(PA13);
static uint32_t xorshift_state = 0xABCD1234;
int counterLED;
Display display;
MathQuizzer MathQuiz;
Numpad numpad;

LEDGame::LEDGame() {
}

void LEDGame::Ledtester(){
LED1.on();
LED2.on();
LED3.on();
LED4.on();
TimerLED.on();
GreenLED.on();
RedLED.on();
}


void LEDGame::start() {
  counterLED = 4;
  display.setup();
  display.scoreDisplay(999, counterLED - 4);
  TimerLED.on();
  bool gameTest = true;
  while (gameTest == true) {

    std::vector<int> Runde = initRound(counterLED);
    gameTest = playRound(Runde);

      if (gameTest == false) {
        MathQuiz.createQuiz();
      //if false MathQuiz is started
      //showQuiz of display / get quiz from mathQuiz
      //show input // get answer from mathQuiz
      std::cout << "failed";
      int ergebnis = MathQuiz.getResultado();
      bool isMathGame = true;
      const char* operation = LEDGame::stringToConstChar(MathQuiz.getOperationString());
      display.scoreDisplay(999, counterLED - 4);
      display.showMathgame(operation);
      delete[] operation;
      while(isMathGame){
         int typed = display.showInput(numpad.getNumber());
         if (typed == ergebnis){
           MathQuiz.setDifficulty(MathQuiz.getDifficulty()+1);
           isMathGame = false;
           gameTest = true;
           delay(300);
           display.checkmark();
           delay(300);
           display.blackScreen();
         }
         else{
           isMathGame = false;
           gameTest = false;
           delay(300);
           display.redX();
           delay(300);
           display.blackScreen();
         }

      }

    }



    gameTest ? counterLED++ : counterLED += 0;
    display.scoreDisplay(999, counterLED - 4);
  }
  display.gameOver();
};

//for button_loop we have to use it in a loop with a condition != 9

int LEDGame::button_loop() {

  int buttonPressed = 9;

  if (Button1.is_pressed() == true) {  // Si se presiona el botón
    LED1.on();
    delay(500);
    LED1.off();
    buttonPressed = 0;
    return buttonPressed;
  } else {
    LED1.off();
  }
  if (Button2.is_pressed() == true) {  // Si se presiona el botón
    LED2.on();
    delay(500);
    LED2.off();
    buttonPressed = 1;
    return buttonPressed;
  } else {
    LED2.off();
  }

  if (Button3.is_pressed() == true) {  // Si se presiona el botón
    LED3.on();
    delay(500);
    LED3.off();
    buttonPressed = 2;
    return buttonPressed;
  } else {
    LED3.off();
  }

  if (Button4.is_pressed() == true) {  // Si se presiona el botón
    LED4.on();
    delay(500);
    LED4.off();
    buttonPressed = 3;
    return buttonPressed;
  } else {
    LED4.off();
  }

  if (startButton.is_pressed() == true) {  // Si se presiona el botón
    GreenLED.on();
    RedLED.on();
    delay(500);
    GreenLED.off();
    RedLED.off();
    buttonPressed = 4;
    return buttonPressed;
  } else {
    GreenLED.off();
    RedLED.off();
  }


  return buttonPressed;
};

std::vector<int> LEDGame::generateSequence(int size) {

  std::vector<int> sequence(size);
  // std::random_device rd;
  // std::mt19937 gen(rd());
  // std::uniform_int_distribution<> dis(0, 3);

  for (int i = 0; i < size; ++i) {
    uint32_t genNum = xorshift32();

    sequence[i] = genNum;
  }

  return sequence;
};

int LEDGame::randomNum() {
  std::srand(time(nullptr));        // Seed the random number generator with the current time
  int randomNum = std::rand() % 4;  // Generate a random number between 0 and 3

  std::cout << "Random Number: " << randomNum << std::endl;
  return randomNum;
}

uint32_t LEDGame::xorshift32(void) {
  uint32_t x = xorshift_state;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  xorshift_state = x;
  x = x % 4;
  return x;
}

void LEDGame::turn_on_random_sequence(std::vector<int> sequence) {

  for (int i = 0; i < sequence.size(); i++) {
    ledArray[sequence[i]].on();
    delay(500);
    ledArray[sequence[i]].off();
    delay(250);
  };
};

//We get with initRound a vector with the generated sequence, in order for us to check the input

std::vector<int> LEDGame::initRound(int size) {

  std::vector<int> sequence = generateSequence(size);
  turn_on_random_sequence(sequence);
  return sequence;
};

// We check every input with the generated sequence

bool LEDGame::playRound(std::vector<int> LEDarray) {
  std::vector<int> sequenceToCheck = LEDarray;
  for (int i = 0; i < sequenceToCheck.size(); i++) {
    //we have to wait for an input

    //polling for buttons
    int button = 9;
    while (button == 9) {
      button = button_loop();
    }
    if (button == LEDarray[i]) {
      std::cout << "correct" << std::endl;
    } else {
      std::cout << "false" << std::endl;

      for (int j = 0; j < 5; j++) {
        RedLED.on();
        delay(100);
        RedLED.off();
        delay(100);
      }
      display.redX();
      delay(1000);
      display.blackScreen();

      return false;
    }
  }
  GreenLED.on();
  display.checkmark();
  delay(1000);
  display.blackScreen();
  GreenLED.off();
  return true;
}
const char* LEDGame::stringToConstChar(const String& str) {
  char* charArray = new char[str.length() + 1];
  str.toCharArray(charArray, str.length() + 1);
  return const_cast<const char*>(charArray);
}
