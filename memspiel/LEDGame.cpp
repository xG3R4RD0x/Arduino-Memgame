#include <ostream>
#include "Button.h"
#include "LED.h"
#include "LEDGame.h"
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <random>
#include <iostream>



LED LED1(PC3);
LED LED2(PC2);
LED LED3(A5);
LED LED4(A4);
LED TimerLED(A3);
LED GreenLED(A2);
LED RedLED(A1);
std::vector<LED> ledArray = {LED1, LED2, LED3, LED4};
Button Button1(PC10);
Button Button2(A0);
Button Button3(PC12);
Button Button4(PC11);
Button startButton(PA13);


LEDGame::LEDGame() {
}

void LEDGame::start() {
  // LED1.on();
  // LED2.on();
  // LED3.on();
  // LED4.on();
   TimerLED.on();
  // GreenLED.on();
  // RedLED.on();
  //std::vector<int> sequence= generateSequence(4);

 // std::cout <<  << std::endl;

};

int LEDGame::button_loop(){

  int buttonPressed= 9;

if (Button1.is_pressed() == true) {  // Si se presiona el botón
    LED1.on();
    delay(500);
    LED1.off();
    buttonPressed = 0;
    return buttonPressed;
    }else{ 
    LED1.off();
    }
if (Button2.is_pressed() == true) {  // Si se presiona el botón
    LED2.on();
    delay(500);
    LED2.off();
    buttonPressed = 1;
    return buttonPressed;
    }else{ 
    LED2.off();
    }

if (Button3.is_pressed() == true) {  // Si se presiona el botón
    LED3.on();
    delay(500);
    LED3.off();
    buttonPressed = 2;
    return buttonPressed;
    }else{ 
    LED3.off();
    }
  
if (Button4.is_pressed() == true) {  // Si se presiona el botón
    LED4.on();
    delay(500);
    LED4.off();
    buttonPressed = 3;
    return buttonPressed;
    }else{ 
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
    }else{ 
    GreenLED.off();
    RedLED.off();
    }


  return 0;
};

std::vector<int> LEDGame::generateSequence(int size) {
  std::vector<int> sequence(size);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 3);

  for (int i = 0; i < size; ++i) {
    sequence[i] = dis(gen);
  }

  return sequence;
};

void LEDGame::turn_on_random_sequence(std::vector<int> sequence) {

  for (int i = 0; i < sequence.size(); i++) {
    ledArray[sequence[i]].on();
    delay(500);
    ledArray[sequence[i]].off();
  };

};

std::vector<int> LEDGame::initRound(int size){

  std::vector<int> sequence = generateSequence(size);
  turn_on_random_sequence(sequence);
  return sequence;
};

    bool LEDGame::playRound(std::vector<int> LEDarray){
      std::vector<int> sequenceToCheck = LEDarray;
      int pressed;
      for (int i=0; i < sequenceToCheck.size();i++){
          pressed = button_loop();
          if(pressed = LEDarray[i]){
            std::cout << "correct";
          }
          else{
            std::cout << "false";
            return false;
          }

      }
      return true;


    }



