#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED {
  public:
    LED(int pin){
      _pin = pin; //PIN
pinMode(_pin, OUTPUT); //LED as OUTPUT

    };
    void on(){
      digitalWrite(_pin, HIGH);
    };
    void off(){
      digitalWrite(_pin, LOW);
    };
  private:
    int _pin;
};

#endif
