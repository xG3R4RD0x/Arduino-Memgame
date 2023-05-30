#include <Keypad.h>
#include "Numpad.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {  
  {'1', '3', '2', 'A'},
  {'4', '6', '5', 'B'},
  {'7', '9', '8', 'C'},
  {'*', '#', '0', 'D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad 
byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
  
Numpad::Numpad(){};

int Numpad::setup(){
// Start the serial connection
 // Serial.begin(9600);
}

char Numpad::getNumber(){
  while(true){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
    return customKey;
    }
  }
};

// void loop(){
//   char customKey = customKeypad.getKey();
  
//   if (customKey){
//     Serial.println(customKey);
//   }

